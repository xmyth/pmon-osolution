_from coreboot wiki_

The DSDT describes the interrupt routing and power management capabilities of devices, and is what Linux uses for interrupt routing if it can. It can be created using the following approximate steps:

  1. Under Award Bios, 'cat /proc/acpi/dsdt > dsdt'
  1. Decompile dsdt with Intel's iasl - 'iasl -d dsdt'
  1. Compile to C table with Intel's iasl - 'iasl -tc dsdt.dsl'