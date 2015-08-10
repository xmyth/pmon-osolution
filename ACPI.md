#summary 关于ACPI的总入口
# ACPI reference Page #
在这里我们存放一些ACPI相关的信息，作为我们STR实现的参考。在coreboot中有些主板支持了ACPI功能（可能只是部分支持），我大概看了一下，觉得 epia-m (via) 和 a8v-e\_se (asus) 值得我们参考一下。

## Tips ##

  * [HowToGetDSDTTable](HowToGetDSDTTable.md)
  * [acpi in a8v-e\_se](ACPI_in_coreboot.md)
  * [ACPI\_TABLE\_SAMPLE](ACPI_TABLE_SAMPLE.md)
  * AcpiTool
  * [issues with S3 resume](Video.md)

## 分析 ##

  * [epia-m中ACPI实现简单分析](AcpiInepia.md)
  * [To Disk 流程分析](Suspend.md)

## Useful Website ##
  * [ACPI spec](http://www.acpi.info)
  * [coreboot (LinuxBios) project](http://coreboot.org)
  * [BIOS ACPI TABLE](http://blog.chinaunix.net/u/7356/showart_370384.html)
  * [linux acpi](http://wiki.zh-kernel.org/project/linux-acpi)
  * [Kernel Summit 2005: The power management summit](http://lwn.net/Articles/144193/)
  * [Suspend and hibernation status report](http://lwn.net/Articles/243404/)
  * [swsusp status report](http://lkml.org/lkml/2006/7/25/105)
  * [Software-based sleep control](http://www.patentgenius.com/patent/6446213.html)
## Issue ##
  * [VGA\_Restore](VGA_Restore.md)