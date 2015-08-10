# Introduction #

在这个文档里简单分析一下acpi在epia-m （supported in coreboot-v2)

# Details #

在epia-m的主板上，ACPI的实现比较简单，应该只是实现了最小功能，在coreboot的代码中跟ACPI相关的只是创建了ACPI的几个表，大概的函数调用如下：

```
[boot/hardwaremain.c] hardwaremain() ->
    [arch/arch/i386/boot/tables.c] write_tables() -> 
        [mainboard/via/epia-m/acpi_table.c] write_acpi_tables()
```

hardwaremain()这个函数是系统做完基本的初始化后（cpu，cache，memory controller），将代码拷贝到RAM后的一个主要入口，基本上和pmon的进入c代码的入口一样。 在这个函数很短，贴在下面：
```
void hardwaremain(int boot_complete)
{
        struct lb_memory *lb_mem;

        post_code(0x80);

        /* displayinit MUST PRECEDE ALL PRINTK! */
        console_init();

        post_code(0x39);

        printk_notice("coreboot-%s%s %s %s...\n",
                      coreboot_version, coreboot_extra_version, coreboot_build,
                      (boot_complete)?"rebooting":"booting");

        post_code(0x40);

        /* If we have already booted attempt a hard reboot */
        if (boot_complete) {
                hard_reset();
        }

        /* FIXME: Is there a better way to handle this? */
        init_timer();

        /* Find the devices we don't have hard coded knowledge about. */
        dev_enumerate();
        post_code(0x66);
        /* Now compute and assign the bus resources. */
        dev_configure();
        post_code(0x88);
        /* Now actually enable devices on the bus */
        dev_enable();
        /* And of course initialize devices on the bus */
        dev_initialize();
        post_code(0x89);

        /* Now that we have collected all of our information
         * write our configuration tables.
         */
        lb_mem = write_tables();

#if CONFIG_FS_PAYLOAD == 1
        filo(lb_mem);
#else
        elfboot(lb_mem);
#endif
}
```

可以看到，做完所有的硬件配置后调用了write\_tables(), 在write\_tables里面主要写了pirq\_routing和ACPI表，下面看一下write\_acpi\_tables():
```
unsigned long write_acpi_tables(unsigned long start)
{
        unsigned long current;
        acpi_rsdp_t *rsdp;
        acpi_rsdt_t *rsdt;
        acpi_hpet_t *hpet;
        acpi_madt_t *madt;
        acpi_fadt_t *fadt;
        acpi_facs_t *facs;
        acpi_header_t *dsdt;

        /* Align ACPI tables to 16byte */
        start   = ( start + 0x0f ) & -0x10;
        current = start;

        printk_info("ACPI: Writing ACPI tables at %lx...\n", start);

        /* We need at least an RSDP and an RSDT Table */
        rsdp = (acpi_rsdp_t *) current;
        current += sizeof(acpi_rsdp_t);
        rsdt = (acpi_rsdt_t *) current;
        current += sizeof(acpi_rsdt_t);

        /* clear all table memory */
        memset((void *)start, 0, current - start);

        acpi_write_rsdp(rsdp, rsdt);
        acpi_write_rsdt(rsdt);

        /*
         * We explicitly add these tables later on:
         */
        printk_debug("ACPI:     * FACS\n");
        facs = (acpi_facs_t *) current;
        current += sizeof(acpi_facs_t);
        acpi_create_facs(facs);

        dsdt = (acpi_header_t *)current;
        current += ((acpi_header_t *)AmlCode)->length;
        memcpy((void *)dsdt,(void *)AmlCode, ((acpi_header_t *)AmlCode)->length);
        dsdt->checksum = 0; // don't trust intel iasl compiler to get this right
        dsdt->checksum = acpi_checksum(dsdt,dsdt->length);
        printk_debug("ACPI:     * DSDT @ %08x Length %x\n",dsdt,dsdt->length);
        printk_debug("ACPI:     * FADT\n");

        fadt = (acpi_fadt_t *) current;
        current += sizeof(acpi_fadt_t);

        acpi_create_fadt(fadt,facs,dsdt);
        acpi_add_table(rsdt,fadt);

        printk_info("ACPI: done.\n");
        return current;
}
```
这里先写了RSDT和RSDP，然后添加了FADT, FACS, DSDT。

从这里看来基本的ACPI的实现在BIOS这里，主要是要把这些表填好。