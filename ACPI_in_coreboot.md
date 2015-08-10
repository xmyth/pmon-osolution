_from coreboot wiki_

## ACPI setup HOWTO ##

Please have a look to files in the src/mainboard/asus/a8v-e\_se. Check also the [http://acpi.info ](.md)
which contains the specification.

### Setup hardware ###

Setup the PMIO base address to some known address, and setup the desired ACPI IRQ (usually IRQ9).
Sometimes it is called SCI interrupt.

### Fill FADT ###

Now you will need to create an ACPI table which describes the I/O port location for kernel ACPI implementation. This is the FACP table. You will need to create the fadt.c file and fill in
the IO port values plus IRQ:

```
fadt->sci_int = 9;
fadt->pm1a_evt_blk = VT8237R_ACPI_IO_BASE;
fadt->pm1b_evt_blk = 0x0;
fadt->pm1a_cnt_blk = VT8237R_ACPI_IO_BASE + 0x4;
fadt->pm1b_cnt_blk = 0x0;
fadt->pm2_cnt_blk = 0x0;
fadt->pm_tmr_blk = VT8237R_ACPI_IO_BASE + 0x8;
fadt->gpe0_blk = VT8237R_ACPI_IO_BASE + 0x20;
fadt->gpe1_blk = 0x0;
```

In this example the ACPI IRQ is 9, and the PM1A event block start at VT8237R\_ACPI\_IO\_BASE. You
may obtain some values from cat /proc/ioport if running with proprietary BIOS. Not all blocks
are necessary usually only PM1A PMTMR and GPE0 are used. Please note that this table has the IO port
information stored twice using different formats. Please consult the ACPI specification for details,
mostly could be used what are the defaults in the fadt.c

### Fill DSDT ###

The DSDT table contains a bytecode that is executed by driver in the kernel. This table stores also
ACPI routing information in _PRT methods. You may add those_PRT methods later.

Very generic DSDT table would look like in similar way how it is ASUS A8V-E (dsdt.asl).

```
        Scope (\_PR)
        {
                Processor (\_PR.CPU0, 0x00, 0x000000, 0x00) {}
                Processor (\_PR.CPU1, 0x01, 0x000000, 0x00) {}
        }
```

This is here for compatibility. More interesting is:
```

        /* For now only define 2 power states:
         *  - S0 which is fully on
         *  - S5 which is soft off
         * any others would involve declaring the wake up methods
         */
        Name (\_S0, Package () {0x00, 0x00, 0x00, 0x00 })
        Name (\_S5, Package () {0x02, 0x02, 0x00, 0x00 })
```

This defines the SLP\_TYP fields in PM1A register. In my case I need to store 010 to perform soft off.
And 000 to wakeup. Modify it to fit your chipset needs. Rest of the files is quite generic, except the _PRT methods which define the routing._

```
     Package (0x04) { 0x000BFFFF, 0x00, 0x00, 0x10 }, //slot 0xB
     Package (0x04) { 0x000BFFFF, 0x01, 0x00, 0x11 },
     Package (0x04) { 0x000BFFFF, 0x02, 0x00, 0x12 },
     Package (0x04) { 0x000BFFFF, 0x03, 0x00, 0x13 },
```

This defines the slot 0xB (all functions FFFF) routing as follows :
```
INTA -> IRQ16
INTB -> IRQ17
INTC -> IRQ18
INTD -> IRQ19
```

You may also just state just one state/function:
```
Package (0x04) { 0x000F0001, 0x00, 0x00, 0x14 }, //0xf NAtive IDE IRQ 20
```

This means 0:0f.1 INTA is routed to IRQ20.

Please note that the 0x10, 0x11 are called GSI (global system interrupt). All your interrupts routed through first APIC will start with 0x00, second APIC will perhaps start at IRQ24 etc etc...
This example has no support for legacy PIC routing. For PIC routing you would need  to alter rest of the fields in the _PRT package and also crete PIRQA-PIRQD special devices._

Rest of the file contains just some legacy devices to make certain OS instatallers happy.
Don't forget to install iasl compiler and also adjust the coreboot buildsystem to build binary DSDT
for you.

### Other tables ###

Rest of the ACPI tables is located at acpi\_tables.c. I will describe briefly all methods:

#### acpi\_fill\_mcfg ####

If your platform supports MMCONFIG (memory mapped PCI configuration registers) just modify the
function with correct base address.

#### acpi\_fill\_madt ####

This describes the ACPI IRQ information, as well as IRQ override. The gsi\_base used in the code
is base for second APIC. Provide APIC bases and IDs. Usually there are two IRQ overrides. IRQ0 override means that IRQ0 is not connected to pin 0 on APIC but to another, most likely pin 2. Second IRQ override is for ACPI IRQ. This overrides the 'level' of the interrupt to 'active low'.  The rest of the table is filled with NMI entries for the processor.

#### write\_acpi\_tables ####

This is the main function which constructs the tables. Functions described above are callbacks from the
"construct" functions called here. You may ommit the HPET and MCFG tables.