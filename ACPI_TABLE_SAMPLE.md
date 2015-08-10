#summary some acpi table sample

这些ACPI表是从一台PC（SB为686B）上dump出来的，机器上的一些信息如下:
```
$ more interrupts 
           CPU0       
  0:    1624920    XT-PIC-XT        timer
  1:       9880    XT-PIC-XT        i8042
  2:          0    XT-PIC-XT        cascade
  3:          1    XT-PIC-XT        acpi
  5:     979115    XT-PIC-XT        uhci_hcd:usb1, uhci_hcd:usb2, uhci_hcd:usb4, nvidia
  7:         51    XT-PIC-XT        ehci_hcd:usb5
  8:          3    XT-PIC-XT        rtc
 10:      54908    XT-PIC-XT        eth1
 11:       5601    XT-PIC-XT        uhci_hcd:usb3, VIA686A
 12:          4    XT-PIC-XT        i8042
 14:      55800    XT-PIC-XT        ide0
 15:      95234    XT-PIC-XT        ide1
NMI:          0 
LOC:          0 
ERR:          0
MIS:          0
$ more iomem 
00000000-0009fbff : System RAM
  00000000-00000000 : Crash kernel
0009fc00-0009ffff : reserved
000a0000-000bffff : Video RAM area
000c0000-000cc3ff : Video ROM
000d0000-000d3fff : pnp 00:00
000f0000-000fffff : System ROM
00100000-2ffeffff : System RAM
  00100000-002f7e85 : Kernel code
  002f7e86-003dce83 : Kernel data
2fff0000-2fff2fff : ACPI Non-volatile Storage
2fff3000-2fffffff : ACPI Tables
40000000-4000ffff : 0000:00:0d.0
d0000000-d7ffffff : PCI Bus #01
  d0000000-d7ffffff : 0000:01:00.0
d8000000-dbffffff : 0000:00:00.0
dc000000-ddffffff : PCI Bus #01
  dc000000-dcffffff : 0000:01:00.0
    dc000000-dcffffff : nvidia
  dd000000-dd00ffff : 0000:01:00.0
df000000-df0000ff : 0000:00:0d.0
  df000000-df0000ff : 8139too
df001000-df0010ff : 0000:00:0a.2
  df001000-df0010ff : ehci_hcd
ffff0000-ffffffff : reserved

$ more ioports 
0000-001f : dma1
0020-0021 : pic1
0040-0043 : timer0
0050-0053 : timer1
0060-006f : keyboard
0070-0077 : rtc
0080-008f : dma page reg
00a0-00a1 : pic2
00c0-00df : dma2
00f0-00ff : fpu
0170-0177 : 0000:00:07.1
  0170-0177 : ide1
01f0-01f7 : 0000:00:07.1
  01f0-01f7 : ide0
0376-0376 : 0000:00:07.1
  0376-0376 : ide1
03c0-03df : vga+
03f6-03f6 : 0000:00:07.1
  03f6-03f6 : ide0
03f8-03ff : serial
0cf8-0cff : PCI conf1
4000-4003 : ACPI PM1a_EVT_BLK
4008-400b : ACPI PM_TMR
4020-4023 : ACPI GPE0_BLK
40f0-40f1 : ACPI PM1a_CNT_BLK
5000-500f : 0000:00:07.4
  5000-5007 : vt596_smbus
6000-607f : 0000:00:07.4
  6000-607f : via686a
c000-c00f : 0000:00:07.1
  c000-c007 : ide0
  c008-c00f : ide1
c400-c41f : 0000:00:07.2
  c400-c41f : uhci_hcd
c800-c81f : 0000:00:07.3
  c800-c81f : uhci_hcd
cc00-ccff : 0000:00:07.5
  cc00-ccff : VIA686A
d000-d003 : 0000:00:07.5
  d000-d003 : VIA686A
d400-d403 : 0000:00:07.5
  d400-d403 : VIA686A
d800-d81f : 0000:00:0a.0
  d800-d81f : uhci_hcd
dc00-dc1f : 0000:00:0a.1
  dc00-dc1f : uhci_hcd
e000-e0ff : 0000:00:0d.0
  e000-e0ff : 8139too

$ dmesg |grep ACPI
[    0.000000]  BIOS-e820: 000000002fff0000 - 000000002fff3000 (ACPI NVS)
[    0.000000]  BIOS-e820: 000000002fff3000 - 0000000030000000 (ACPI data)
[    0.000000] ACPI: RSDP signature @ 0xC00F78C0 checksum 0
[    0.000000] ACPI: RSDP 000F78C0, 0014 (r0 VIA694)
[    0.000000] ACPI: RSDT 2FFF3000, 0028 (r1 VIA694 MSI ACPI 42302E31 AWRD        0)
[    0.000000] ACPI: FACP 2FFF3040, 0074 (r1 VIA694 MSI ACPI 42302E31 AWRD        0)
[    0.000000] ACPI: DSDT 2FFF30C0, 27BE (r1 VIA694 AWRDACPI     1000 MSFT  100000C)
[    0.000000] ACPI: FACS 2FFF0000, 0040
[    0.000000] ACPI: PM-Timer IO Port: 0x4008
[   40.810240] ACPI: Core revision 20070126
[   40.810405] ACPI: Looking for DSDT in initramfs... error, file /DSDT.aml not found.
[   40.811916] ACPI: setting ELCR to 0008 (from 0ca8)
[   40.814911] ACPI: bus type pci registered
[   40.852651] ACPI: EC: Look up EC in DSDT
[   40.856347] ACPI: Interpreter enabled
[   40.856353] ACPI: (supports S0 S1 S4 S5)
[   40.856378] ACPI: Using PIC for interrupt routing
[   40.860743] ACPI: PCI Root Bridge [PCI0] (0000:00)
[   40.861498] ACPI: PCI Interrupt Routing Table [\_SB_.PCI0._PRT]
[   40.878315] ACPI: PCI Interrupt Link [LNKA] (IRQs 1 3 4 *5 6 7 10 11 12 14 15)
[   40.878513] ACPI: PCI Interrupt Link [LNKB] (IRQs 1 3 4 5 6 *7 10 11 12 14 15)
[   40.878713] ACPI: PCI Interrupt Link [LNKC] (IRQs 1 3 4 5 6 7 *10 11 12 14 15)
[   40.878907] ACPI: PCI Interrupt Link [LNKD] (IRQs 1 3 4 5 6 7 10 *11 12 14 15)
[   40.879053] pnp: PnP ACPI init
[   40.879076] ACPI: bus type pnp registered
[   40.881505] pnp: PnP ACPI: found 9 devices
[   40.881509] ACPI: ACPI bus type pnp unregistered
[   40.881517] PnPBIOS: Disabled by ACPI PNP
[   40.881618] PCI: Using ACPI for IRQ routing
[   46.906562] ACPI: PCI Interrupt Link [LNKA] enabled at IRQ 5
[   46.906577] ACPI: PCI Interrupt 0000:00:07.2[D] -> Link [LNKA] -> GSI 5 (level, low) -> IRQ 5
[   47.009151] ACPI: PCI Interrupt 0000:00:07.3[D] -> Link [LNKA] -> GSI 5 (level, low) -> IRQ 5
[   47.113694] ACPI: PCI Interrupt Link [LNKD] enabled at IRQ 11
[   47.113711] ACPI: PCI Interrupt 0000:00:0a.0[A] -> Link [LNKD] -> GSI 11 (level, low) -> IRQ 11
[   47.216890] ACPI: PCI Interrupt 0000:00:0a.1[B] -> Link [LNKA] -> GSI 5 (level, low) -> IRQ 5
[   47.321609] ACPI: PCI Interrupt Link [LNKB] enabled at IRQ 7
[   47.321625] ACPI: PCI Interrupt 0000:00:0a.2[C] -> Link [LNKB] -> GSI 7 (level, low) -> IRQ 7
[   47.469779] ACPI: PCI Interrupt Link [LNKC] enabled at IRQ 10
[   47.469796] ACPI: PCI Interrupt 0000:00:0d.0[A] -> Link [LNKC] -> GSI 10 (level, low) -> IRQ 10
[   59.262943] ACPI: PCI Interrupt 0000:01:00.0[A] -> Link [LNKA] -> GSI 5 (level, low) -> IRQ 5
[   60.030878] ACPI: PCI Interrupt 0000:00:07.5[C] -> Link [LNKD] -> GSI 11 (level, low) -> IRQ 11
[   64.485029] ACPI: Power Button (FF) [PWRF]
[   64.542439] ACPI: Power Button (CM) [PWRB]
[   64.570451] ACPI: Sleep Button (CM) [SLPB]
```

# DSDT #
```
/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20061109
 *
 * Disassembly of dsdt.aml, Wed Mar 19 23:13:05 2008
 *
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x000027BE (10174)
 *     Revision         0x01
 *     OEM ID           "VIA694"
 *     OEM Table ID     "AWRDACPI"
 *     OEM Revision     0x00001000 (4096)
 *     Creator ID       "MSFT"
 *     Creator Revision 0x0100000C (16777228)
 */
DefinitionBlock ("dsdt.aml", "DSDT", 1, "VIA694", "AWRDACPI", 0x00001000)
{
    Scope (\_PR)
    {
        Processor (\_PR.CPU0, 0x00, 0x00000000, 0x00) {}
    }

    OperationRegion (CM72, SystemIO, 0x72, 0x02)
    Field (CM72, ByteAcc, NoLock, Preserve)
    {
        CI72,   8, 
        CO73,   8
    }

    IndexField (CI72, CO73, ByteAcc, NoLock, Preserve)
    {
                Offset (0x43), 
        SUSF,   8
    }

    Name (STAT, 0x00)
    Name (\_S0, Package (0x04)
    {
        Zero, 
        Zero, 
        Zero, 
        Zero
    })
    Name (\_S1, Package (0x04)
    {
        0x04, 
        0x04, 
        0x04, 
        0x04
    })
    And (SUSF, 0x01, STAT)
    Name (\_S4, Package (0x04)
    {
        0x02, 
        0x02, 
        0x02, 
        0x02
    })
    Name (\_S5, Package (0x04)
    {
        0x02, 
        0x02, 
        0x02, 
        0x02
    })
    OperationRegion (\DEBG, SystemIO, 0x80, 0x01)
    Field (\DEBG, ByteAcc, NoLock, Preserve)
    {
        DBG1,   8
    }

    OperationRegion (EXTM, SystemMemory, 0x000FF830, 0x10)
    Field (EXTM, WordAcc, NoLock, Preserve)
    {
        ROM1,   16, 
        RMS1,   16, 
        ROM2,   16, 
        RMS2,   16, 
        ROM3,   16, 
        RMS3,   16, 
        AMEM,   32
    }

    OperationRegion (\GPST, SystemIO, 0x4020, 0x04)
    Field (\GPST, ByteAcc, NoLock, Preserve)
    {
        GS00,   1, 
        GS01,   1, 
        GS02,   1, 
        GS03,   1, 
        GS04,   1, 
        GS05,   1, 
        GS06,   1, 
        GS07,   1, 
        GS08,   1, 
        GS09,   1, 
        GS0A,   1, 
        GS0B,   1, 
        GS0C,   1, 
                Offset (0x02), 
        GE00,   1, 
        GE01,   1, 
        GE02,   1, 
        GE03,   1, 
        GE04,   1, 
        GE05,   1, 
        GE06,   1, 
        GE07,   1, 
        GE08,   1, 
        GE09,   1, 
        GE0A,   1, 
        GE0B,   1, 
        GE0C,   1, 
                Offset (0x04)
    }

    OperationRegion (ELCR, SystemIO, 0x04D0, 0x02)
    Field (ELCR, ByteAcc, NoLock, Preserve)
    {
        ELC1,   8, 
        ELC2,   8
    }

    OperationRegion (\STUS, SystemIO, 0x4030, 0x01)
    Field (\STUS, ByteAcc, NoLock, Preserve)
    {
        G_ST,   8
    }

    OperationRegion (\WIRQ, SystemIO, 0x402A, 0x01)
    Field (\WIRQ, ByteAcc, NoLock, Preserve)
    {
        IRQR,   8
    }

    OperationRegion (\SMIC, SystemIO, 0x402F, 0x01)
    Field (\SMIC, ByteAcc, NoLock, Preserve)
    {
        SCP,    8
    }

    OperationRegion (GPOB, SystemIO, 0x404C, 0x04)
    Field (GPOB, ByteAcc, NoLock, Preserve)
    {
        GP00,   1, 
        GP01,   1, 
        GP02,   1, 
        GP03,   1, 
        GP04,   1, 
        GP05,   1, 
        GP06,   1, 
        GP07,   1, 
        GP08,   1, 
        GP09,   1, 
        GP10,   1, 
        GP11,   1, 
        GP12,   1, 
        GP13,   1, 
        GP14,   1, 
        GP15,   1, 
        GP16,   1, 
        GP17,   1, 
        GP18,   1, 
        GP19,   1, 
        GP20,   1, 
        GP21,   1, 
        GP22,   1, 
        GP23,   1, 
        GP24,   1, 
        GP25,   1, 
        GP26,   1, 
        GP27,   1, 
        GP28,   1, 
        GP29,   1, 
        GP30,   1, 
        GPXX,   1
    }

    Name (OSFL, 0x01)
    Method (STRC, 2, NotSerialized)
    {
        If (LNotEqual (SizeOf (Arg0), SizeOf (Arg1)))
        {
            Return (0x00)
        }

        Add (SizeOf (Arg0), 0x01, Local0)
        Name (BUF0, Buffer (Local0) {})
        Name (BUF1, Buffer (Local0) {})
        Store (Arg0, BUF0)
        Store (Arg1, BUF1)
        While (Local0)
        {
            Decrement (Local0)
            If (LNotEqual (DerefOf (Index (BUF0, Local0)), DerefOf (Index (
                BUF1, Local0))))
            {
                Return (Zero)
            }
        }

        Return (One)
    }

    OperationRegion (RTCM, SystemIO, 0x72, 0x02)
    Field (RTCM, ByteAcc, NoLock, Preserve)
    {
        CMIN,   8, 
        CMDA,   8
    }

    OperationRegion (\GRAM, SystemMemory, 0x0400, 0x0100)
    Field (\GRAM, ByteAcc, NoLock, Preserve)
    {
                Offset (0x10), 
        FLG0,   8, 
                Offset (0xBA), 
        SFLG,   8
    }

    OperationRegion (INFO, SystemMemory, 0x000FF840, 0x01)
    Field (INFO, ByteAcc, NoLock, Preserve)
    {
        KBDI,   1, 
        RTCW,   1, 
        PS2F,   1, 
        IRFL,   2, 
        DISE,   1, 
        SSHU,   1
    }

    OperationRegion (BEEP, SystemIO, 0x61, 0x01)
    Field (BEEP, ByteAcc, NoLock, Preserve)
    {
        S1B,    8
    }

    OperationRegion (CONT, SystemIO, 0x40, 0x04)
    Field (CONT, ByteAcc, NoLock, Preserve)
    {
        CNT0,   8, 
        CNT1,   8, 
        CNT2,   8, 
        CTRL,   8
    }

    Method (SPKR, 1, NotSerialized)
    {
        Store (S1B, Local0)
        Store (0xB6, CTRL)
        Store (0x55, CNT2)
        Store (0x03, CNT2)
        Store (Arg0, Local2)
        While (LGreater (Local2, 0x00))
        {
            Or (S1B, 0x03, S1B)
            Store (0x5FFF, Local3)
            While (LGreater (Local3, 0x00))
            {
                Decrement (Local3)
            }

            And (S1B, 0xFC, S1B)
            Store (0x0EFF, Local3)
            While (LGreater (Local3, 0x00))
            {
                Decrement (Local3)
            }

            Decrement (Local2)
        }

        Store (Local0, S1B)
    }

    IndexField (CMIN, CMDA, ByteAcc, NoLock, Preserve)
    {
                Offset (0x4C), 
        DLED,   1, 
        BLED,   1
    }

    Scope (\)
    {
        Name (PICF, 0x00)
        Method (PPIC, 1, NotSerialized)
        {
            Store (Arg0, PICF)
        }
    }

    Method (\_PTS, 1, NotSerialized)
    {
        Or (Arg0, 0xF0, Local0)
        Store (Local0, DBG1)
        If (LNotEqual (Arg0, 0x05))
        {
            If (LEqual (BLED, One))
            {
                And (PWC1, 0xFC, PWC1)
                Or (PWC1, 0x01, PWC1)
            }

            If (LEqual (DLED, One))
            {
                Store (Zero, GP00)
            }
        }

        Or (Arg0, 0x50, Local1)
        Store (Local1, SCP)
        If (LEqual (Arg0, 0x01))
        {
            And (GAR1, 0xFD, GAR1)
            And (GAR2, 0x02, Local0)
            Or (Local0, GAR1, GAR1)
            Store (G_ST, Local1)
            While (LNotEqual (Local1, 0x00))
            {
                Store (Local1, G_ST)
                Store (G_ST, Local1)
            }

            Or (IRQR, 0x80, IRQR)
        }

        If (LEqual (Arg0, 0x05))
        {
            Store (Zero, GE00)
            Store (Zero, GP00)
        }
    }

    Method (\_WAK, 1, NotSerialized)
    {
        Store (0xFF, DBG1)
        While (LNotEqual (GS00, Zero))
        {
            Store (One, GS00)
        }

        If (LEqual (BLED, One))
        {
            And (PWC1, 0xFC, PWC1)
        }

        If (LEqual (DLED, One))
        {
            Store (One, GP00)
        }

        Notify (\_SB.PCI0.UAR1, 0x00)
        Notify (\_SB.PCI0.UAR2, 0x00)
        Notify (\_SB.PCI0.LPT1, 0x00)
        Notify (\_SB.PCI0.ECP1, 0x00)
        If (LEqual (RTCW, 0x00))
        {
            Notify (\_SB.PWRB, 0x02)
        }
    }

    Scope (\_SI)
    {
        Method (_MSG, 1, NotSerialized)
        {
            Store (Local0, Local0)
        }

        Method (_SST, 1, NotSerialized)
        {
            If (LEqual (Arg0, 0x03)) {}
            If (LEqual (Arg0, 0x01)) {}
            If (LEqual (Arg0, Zero)) {}
            Store (Local0, Local0)
        }
    }

    Scope (\_GPE)
    {
        Method (_L05, 0, NotSerialized)
        {
            Notify (\_SB.PCI0, 0x02)
        }

        Method (_L09, 0, NotSerialized)
        {
            Noop
        }

        Method (_L08, 0, NotSerialized)
        {
            Noop
        }

        Method (_L00, 0, NotSerialized)
        {
            Notify (\_SB.SLPB, 0x80)
        }
    }

    Scope (\_SB)
    {
        Device (PWRB)
        {
            Name (_HID, EisaId ("PNP0C0C"))
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0B)
            }
        }

        Device (SLPB)
        {
            Name (_HID, EisaId ("PNP0C0E"))
            Method (_STA, 0, NotSerialized)
            {
                Return (0x0B)
            }

            Name (_PRW, Package (0x02)
            {
                0x00, 
                0x05
            })
        }

        Device (MEM)
        {
            Name (_HID, EisaId ("PNP0C01"))
            Method (_CRS, 0, NotSerialized)
            {
                Name (BUF0, ResourceTemplate ()
                {
                    Memory32Fixed (ReadWrite,
                        0x000F0000,         // Address Base
                        0x00004000,         // Address Length
                        _Y01)
                    Memory32Fixed (ReadWrite,
                        0x000F4000,         // Address Base
                        0x00004000,         // Address Length
                        _Y02)
                    Memory32Fixed (ReadWrite,
                        0x000F8000,         // Address Base
                        0x00004000,         // Address Length
                        _Y03)
                    Memory32Fixed (ReadWrite,
                        0x000FC000,         // Address Base
                        0x00004000,         // Address Length
                        _Y04)
                    Memory32Fixed (ReadWrite,
                        0x00000000,         // Address Base
                        0x00010000,         // Address Length
                        _Y00)
                    Memory32Fixed (ReadWrite,
                        0xFFFF0000,         // Address Base
                        0x00010000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0x00000000,         // Address Base
                        0x000A0000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0x00100000,         // Address Base
                        0x00000000,         // Address Length
                        _Y05)
                    Memory32Fixed (ReadWrite,
                        0xFEC00000,         // Address Base
                        0x00001000,         // Address Length
                        )
                    Memory32Fixed (ReadWrite,
                        0xFEE00000,         // Address Base
                        0x00001000,         // Address Length
                        )
                })
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y00._BAS, ACMM)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y01._BAS, RMA1)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y01._LEN, RSS1)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y02._BAS, RMA2)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y02._LEN, RSS2)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y03._BAS, RMA3)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y03._LEN, RSS3)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y04._BAS, RMA4)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y04._LEN, RSS4)
                CreateDWordField (BUF0, \_SB.MEM._CRS._Y05._LEN, EXTM)
                Subtract (AMEM, 0x00100000, EXTM)
                If (LNotEqual (ROM1, Zero))
                {
                    Store (RMA1, RMA2)
                    ShiftLeft (ROM1, 0x08, Local0)
                    Store (Local0, RMA1)
                    ShiftLeft (RMS1, 0x08, Local0)
                    Store (Local0, RSS1)
                    Store (0x8000, RSS2)
                }

                If (LNotEqual (ROM2, Zero))
                {
                    Store (RMA2, RMA3)
                    ShiftLeft (ROM2, 0x08, Local0)
                    Store (Local0, RMA2)
                    ShiftLeft (RMS2, 0x08, Local0)
                    Store (Local0, RSS2)
                    Store (0xC000, RSS3)
                }

                If (LNotEqual (ROM3, Zero))
                {
                    Store (RMA3, RMA4)
                    ShiftLeft (ROM3, 0x08, Local0)
                    Store (Local0, RMA3)
                    ShiftLeft (RMS3, 0x08, Local0)
                    Store (Local0, RSS3)
                    Store (0x00010000, RSS4)
                }

                Store (AMEM, ACMM)
                Return (BUF0)
            }
        }

        Device (PCI0)
        {
            Name (_HID, EisaId ("PNP0A03"))
            Name (_ADR, 0x00)
            Name (SS3D, 0x02)
            OperationRegion (GART, PCI_Config, 0x80, 0x01)
            Scope (\)
            {
                Field (\_SB.PCI0.GART, ByteAcc, NoLock, Preserve)
                {
                    GAR1,   8
                }
            }

            OperationRegion (GARA, PCI_Config, 0x88, 0x01)
            Scope (\)
            {
                Field (\_SB.PCI0.GARA, ByteAcc, NoLock, Preserve)
                {
                    GAR2,   8
                }
            }

            Method (_STA, 0, NotSerialized)
            {
                Return (0x0F)
            }

            Method (_CRS, 0, NotSerialized)
            {
                Name (BUF0, ResourceTemplate ()
                {
                    WordBusNumber (ResourceConsumer, MinNotFixed, MaxNotFixed, PosDecode,
                        0x0000,             // Granularity
                        0x0000,             // Range Minimum
                        0x00FF,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x0100,             // Length
                        ,, )
                    IO (Decode16,
                        0x0CF8,             // Range Minimum
                        0x0CF8,             // Range Maximum
                        0x01,               // Alignment
                        0x08,               // Length
                        )
                    WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                        0x0000,             // Granularity
                        0x0000,             // Range Minimum
                        0x0CF7,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x0CF8,             // Length
                        ,, , TypeStatic)
                    WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                        0x0000,             // Granularity
                        0x0D00,             // Range Minimum
                        0x3FFF,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x3300,             // Length
                        ,, , TypeStatic)
                    IO (Decode16,
                        0x4000,             // Range Minimum
                        0x4000,             // Range Maximum
                        0x01,               // Alignment
                        0x80,               // Length
                        )
                    IO (Decode16,
                        0x4080,             // Range Minimum
                        0x4080,             // Range Maximum
                        0x01,               // Alignment
                        0x80,               // Length
                        )
                    WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                        0x0000,             // Granularity
                        0x4100,             // Range Minimum
                        0x4FFF,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x0EFF,             // Length
                        ,, , TypeStatic)
                    IO (Decode16,
                        0x5000,             // Range Minimum
                        0x5000,             // Range Maximum
                        0x01,               // Alignment
                        0x10,               // Length
                        )
                    WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                        0x0000,             // Granularity
                        0x5010,             // Range Minimum
                        0x5FFF,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x0FEF,             // Length
                        ,, , TypeStatic)
                    IO (Decode16,
                        0x6000,             // Range Minimum
                        0x6000,             // Range Maximum
                        0x01,               // Alignment
                        0x80,               // Length
                        )
                    WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
                        0x0000,             // Granularity
                        0x6080,             // Range Minimum
                        0xFFFF,             // Range Maximum
                        0x0000,             // Translation Offset
                        0x9F7F,             // Length
                        ,, , TypeStatic)
                    DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                        0x00000000,         // Granularity
                        0x000A0000,         // Range Minimum
                        0x000BFFFF,         // Range Maximum
                        0x00000000,         // Translation Offset
                        0x00020000,         // Length
                        ,, , AddressRangeMemory, TypeStatic)
                    DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                        0x00000000,         // Granularity
                        0x000C0000,         // Range Minimum
                        0x000DFFFF,         // Range Maximum
                        0x00000000,         // Translation Offset
                        0x00020000,         // Length
                        ,, , AddressRangeMemory, TypeStatic)
                    DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
                        0x00000000,         // Granularity
                        0x00100000,         // Range Minimum
                        0xFFEFFFFF,         // Range Maximum
                        0x00000000,         // Translation Offset
                        0xFFF00000,         // Length
                        ,, _Y06, AddressRangeMemory, TypeStatic)
                })
                CreateDWordField (BUF0, \_SB.PCI0._CRS._Y06._MIN, TCMM)
                CreateDWordField (BUF0, \_SB.PCI0._CRS._Y06._LEN, TOMM)
                Add (AMEM, 0x00010000, TCMM)
                Subtract (0xFFF00000, TCMM, TOMM)
                Return (BUF0)
            }

            Name (PICM, Package (0x24)
            {
                Package (0x04)
                {
                    0x0008FFFF, 
                    0x00, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0008FFFF, 
                    0x01, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0008FFFF, 
                    0x02, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0008FFFF, 
                    0x03, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x00, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x01, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x02, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x03, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x00, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x01, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x02, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x03, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x00, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x01, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x02, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x03, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x00, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x01, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x02, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x03, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x00, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x01, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x02, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x03, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x00, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x01, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x02, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x03, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x00, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x01, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x02, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x03, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x00, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x01, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x02, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x03, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }
            })
            Name (APIC, Package (0x24)
            {
                Package (0x04)
                {
                    0x0008FFFF, 
                    0x00, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0008FFFF, 
                    0x01, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0008FFFF, 
                    0x02, 
                    0x00, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x0008FFFF, 
                    0x03, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x00, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x01, 
                    0x00, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x02, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0009FFFF, 
                    0x03, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x00, 
                    0x00, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x01, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x02, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x000AFFFF, 
                    0x03, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x00, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x01, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x02, 
                    0x00, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x000CFFFF, 
                    0x03, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x00, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x01, 
                    0x00, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x02, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x000DFFFF, 
                    0x03, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x00, 
                    0x00, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x01, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x02, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x000EFFFF, 
                    0x03, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x00, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x01, 
                    0x00, 
                    0x13
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x02, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x000FFFFF, 
                    0x03, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x00, 
                    \_SB.PCI0.LNKA, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x01, 
                    \_SB.PCI0.LNKB, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x02, 
                    \_SB.PCI0.LNKC, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0007FFFF, 
                    0x03, 
                    \_SB.PCI0.LNKD, 
                    0x00
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x00, 
                    0x00, 
                    0x10
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x01, 
                    0x00, 
                    0x11
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x02, 
                    0x00, 
                    0x12
                }, 

                Package (0x04)
                {
                    0x0001FFFF, 
                    0x03, 
                    0x00, 
                    0x13
                }
            })
            Method (_PRT, 0, NotSerialized)
            {
                If (LNot (PICF))
                {
                    Return (PICM)
                }
                Else
                {
                    Return (APIC)
                }
            }

            Device (VT86)
            {
                Name (_ADR, 0x00070000)
                OperationRegion (PIRQ, PCI_Config, 0x55, 0x03)
                Scope (\)
                {
                    Field (\_SB.PCI0.VT86.PIRQ, ByteAcc, NoLock, Preserve)
                    {
                        PIRA,   8, 
                        PIBC,   8, 
                        PIRD,   8
                    }
                }
            }

            Device (USB0)
            {
                Name (_ADR, 0x00070002)
                Name (_PRW, Package (0x02)
                {
                    0x09, 
                    0x05
                })
                Name (SS3D, 0x02)
            }

            Device (USB1)
            {
                Name (_ADR, 0x00070003)
                Name (_PRW, Package (0x02)
                {
                    0x09, 
                    0x01
                })
                Name (SS3D, 0x02)
            }

            Device (VTAC)
            {
                Name (_ADR, 0x00070004)
                OperationRegion (PWC, PCI_Config, 0x54, 0x01)
                Scope (\)
                {
                    Field (\_SB.PCI0.VTAC.PWC, ByteAcc, NoLock, Preserve)
                    {
                        PWC1,   8
                    }
                }
            }

            Device (AUDI)
            {
                Name (_ADR, 0x00070005)
            }

            Device (MODM)
            {
                Name (_ADR, 0x00070006)
                Name (_PRW, Package (0x02)
                {
                    0x0D, 
                    0x04
                })
            }

            Device (PIB)
            {
                Name (_ADR, 0x00070000)
                OperationRegion (SB70, PCI_Config, 0x00, 0x88)
                Field (SB70, ByteAcc, NoLock, Preserve)
                {
                            Offset (0x48), 
                        ,   2, 
                    EUSB,   1, 
                            Offset (0x49), 
                            Offset (0x50), 
                    FLDA,   2, 
                    LPDA,   2, 
                            Offset (0x51), 
                    FLIR,   4, 
                    LPIR,   4, 
                    U1IR,   4, 
                    U2IR,   4, 
                            Offset (0x55), 
                        ,   4, 
                    PIA,    4, 
                    PIB,    4, 
                    PIC,    4, 
                        ,   4, 
                    PID,    4, 
                            Offset (0x85), 
                    EP3C,   1, 
                    EN3C,   1, 
                            Offset (0x86)
                }
            }

            Device (LNKA)
            {
                Name (_HID, EisaId ("PNP0C0F"))
                Name (_UID, 0x01)
                Method (_STA, 0, NotSerialized)
                {
                    And (PIRA, 0xF0, Local0)
                    If (LEqual (Local0, 0x00))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)
                {
                    Name (BUFB, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, )
                            {1,3,4,5,6,7,10,11,12,14,15}
                    })
                    Return (BUFB)
                }

                Method (_DIS, 0, NotSerialized)
                {
                    And (PIRA, 0x0F, PIRA)
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUFB, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, _Y07)
                            {}
                    })
                    CreateByteField (BUFB, \_SB.PCI0.LNKA._CRS._Y07._INT, IRB1)
                    CreateByteField (BUFB, 0x02, IRB2)
                    Store (0x00, Local3)
                    Store (0x00, Local4)
                    And (PIRA, 0xF0, Local1)
                    ShiftRight (Local1, 0x04, Local1)
                    If (LNotEqual (Local1, 0x00))
                    {
                        If (LGreater (Local1, 0x07))
                        {
                            Subtract (Local1, 0x08, Local2)
                            ShiftLeft (One, Local2, Local4)
                        }
                        Else
                        {
                            If (LGreater (Local1, 0x00))
                            {
                                ShiftLeft (One, Local1, Local3)
                            }
                        }

                        Store (Local3, IRB1)
                        Store (Local4, IRB2)
                    }

                    Return (BUFB)
                }

                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x01, IRB1)
                    CreateByteField (Arg0, 0x02, IRB2)
                    ShiftLeft (IRB2, 0x08, Local0)
                    Or (Local0, IRB1, Local0)
                    Store (0x00, Local1)
                    ShiftRight (Local0, 0x01, Local0)
                    While (LGreater (Local0, 0x00))
                    {
                        Increment (Local1)
                        ShiftRight (Local0, 0x01, Local0)
                    }

                    And (PIRA, 0x0F, PIRA)
                    ShiftLeft (Local1, 0x04, Local1)
                    Or (PIRA, Local1, PIRA)
                }
            }

            Device (LNKB)
            {
                Name (_HID, EisaId ("PNP0C0F"))
                Name (_UID, 0x02)
                Method (_STA, 0, NotSerialized)
                {
                    And (PIBC, 0x0F, Local0)
                    If (LEqual (Local0, 0x00))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)
                {
                    Name (BUFA, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, )
                            {1,3,4,5,6,7,10,11,12,14,15}
                    })
                    Return (BUFA)
                }

                Method (_DIS, 0, NotSerialized)
                {
                    And (PIBC, 0xF0, PIBC)
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUFA, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, _Y08)
                            {}
                    })
                    CreateByteField (BUFA, \_SB.PCI0.LNKB._CRS._Y08._INT, IRA1)
                    CreateByteField (BUFA, 0x02, IRA2)
                    Store (0x00, Local3)
                    Store (0x00, Local4)
                    And (PIBC, 0x0F, Local1)
                    If (LNotEqual (Local1, 0x00))
                    {
                        If (LGreater (Local1, 0x07))
                        {
                            Subtract (Local1, 0x08, Local2)
                            ShiftLeft (One, Local2, Local4)
                        }
                        Else
                        {
                            If (LGreater (Local1, 0x00))
                            {
                                ShiftLeft (One, Local1, Local3)
                            }
                        }

                        Store (Local3, IRA1)
                        Store (Local4, IRA2)
                    }

                    Return (BUFA)
                }

                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x01, IRA1)
                    CreateByteField (Arg0, 0x02, IRA2)
                    ShiftLeft (IRA2, 0x08, Local0)
                    Or (Local0, IRA1, Local0)
                    Store (0x00, Local1)
                    ShiftRight (Local0, 0x01, Local0)
                    While (LGreater (Local0, 0x00))
                    {
                        Increment (Local1)
                        ShiftRight (Local0, 0x01, Local0)
                    }

                    And (PIBC, 0xF0, PIBC)
                    Or (PIBC, Local1, PIBC)
                }
            }

            Device (LNKC)
            {
                Name (_HID, EisaId ("PNP0C0F"))
                Name (_UID, 0x03)
                Method (_STA, 0, NotSerialized)
                {
                    And (PIBC, 0xF0, Local0)
                    If (LEqual (Local0, 0x00))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)
                {
                    Name (BUFC, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, )
                            {1,3,4,5,6,7,10,11,12,14,15}
                    })
                    Return (BUFC)
                }

                Method (_DIS, 0, NotSerialized)
                {
                    And (PIBC, 0x0F, PIBC)
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUFC, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, _Y09)
                            {}
                    })
                    CreateByteField (BUFC, \_SB.PCI0.LNKC._CRS._Y09._INT, IRC1)
                    CreateByteField (BUFC, 0x02, IRC2)
                    Store (0x00, Local3)
                    Store (0x00, Local4)
                    And (PIBC, 0xF0, Local1)
                    ShiftRight (Local1, 0x04, Local1)
                    If (LNotEqual (Local1, 0x00))
                    {
                        If (LGreater (Local1, 0x07))
                        {
                            Subtract (Local1, 0x08, Local2)
                            ShiftLeft (One, Local2, Local4)
                        }
                        Else
                        {
                            If (LGreater (Local1, 0x00))
                            {
                                ShiftLeft (One, Local1, Local3)
                            }
                        }

                        Store (Local3, IRC1)
                        Store (Local4, IRC2)
                    }

                    Return (BUFC)
                }

                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x01, IRC1)
                    CreateByteField (Arg0, 0x02, IRC2)
                    ShiftLeft (IRC2, 0x08, Local0)
                    Or (Local0, IRC1, Local0)
                    Store (0x00, Local1)
                    ShiftRight (Local0, 0x01, Local0)
                    While (LGreater (Local0, 0x00))
                    {
                        Increment (Local1)
                        ShiftRight (Local0, 0x01, Local0)
                    }

                    And (PIBC, 0x0F, PIBC)
                    ShiftLeft (Local1, 0x04, Local1)
                    Or (PIBC, Local1, PIBC)
                }
            }

            Device (LNKD)
            {
                Name (_HID, EisaId ("PNP0C0F"))
                Name (_UID, 0x04)
                Method (_STA, 0, NotSerialized)
                {
                    And (PIRD, 0xF0, Local0)
                    If (LEqual (Local0, 0x00))
                    {
                        Return (0x09)
                    }
                    Else
                    {
                        Return (0x0B)
                    }
                }

                Method (_PRS, 0, NotSerialized)
                {
                    Name (BUFD, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, )
                            {1,3,4,5,6,7,10,11,12,14,15}
                    })
                    Return (BUFD)
                }

                Method (_DIS, 0, NotSerialized)
                {
                    And (PIRD, 0x0F, PIRD)
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUFD, ResourceTemplate ()
                    {
                        IRQ (Level, ActiveLow, Shared, _Y0A)
                            {}
                    })
                    CreateByteField (BUFD, \_SB.PCI0.LNKD._CRS._Y0A._INT, IRD1)
                    CreateByteField (BUFD, 0x02, IRD2)
                    Store (0x00, Local3)
                    Store (0x00, Local4)
                    And (PIRD, 0xF0, Local1)
                    ShiftRight (Local1, 0x04, Local1)
                    If (LNotEqual (Local1, 0x00))
                    {
                        If (LGreater (Local1, 0x07))
                        {
                            Subtract (Local1, 0x08, Local2)
                            ShiftLeft (One, Local2, Local4)
                        }
                        Else
                        {
                            If (LGreater (Local1, 0x00))
                            {
                                ShiftLeft (One, Local1, Local3)
                            }
                        }

                        Store (Local3, IRD1)
                        Store (Local4, IRD2)
                    }

                    Return (BUFD)
                }

                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x01, IRD1)
                    CreateByteField (Arg0, 0x02, IRD2)
                    ShiftLeft (IRD2, 0x08, Local0)
                    Or (Local0, IRD1, Local0)
                    Store (0x00, Local1)
                    ShiftRight (Local0, 0x01, Local0)
                    While (LGreater (Local0, 0x00))
                    {
                        Increment (Local1)
                        ShiftRight (Local0, 0x01, Local0)
                    }

                    And (PIRD, 0x0F, PIRD)
                    ShiftLeft (Local1, 0x04, Local1)
                    Or (PIRD, Local1, PIRD)
                }
            }

            Method (\_SB.PCI0._INI, 0, NotSerialized)
            {
                If (STRC (\_OS, "Microsoft Windows")) {}
                Else
                {
                    If (STRC (\_OS, "Microsoft Windows NT"))
                    {
                        Store (0x00, OSFL)
                    }
                    Else
                    {
                        Store (0x02, OSFL)
                    }
                }
            }

            Device (SYSR)
            {
                Name (_HID, EisaId ("PNP0C02"))
                Name (_UID, 0x01)
                Name (_CRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x0010,             // Range Minimum
                        0x0010,             // Range Maximum
                        0x01,               // Alignment
                        0x10,               // Length
                        )
                    IO (Decode16,
                        0x0022,             // Range Minimum
                        0x0022,             // Range Maximum
                        0x01,               // Alignment
                        0x1E,               // Length
                        )
                    IO (Decode16,
                        0x0044,             // Range Minimum
                        0x0044,             // Range Maximum
                        0x01,               // Alignment
                        0x1C,               // Length
                        )
                    IO (Decode16,
                        0x0062,             // Range Minimum
                        0x0062,             // Range Maximum
                        0x01,               // Alignment
                        0x02,               // Length
                        )
                    IO (Decode16,
                        0x0065,             // Range Minimum
                        0x0065,             // Range Maximum
                        0x01,               // Alignment
                        0x0B,               // Length
                        )
                    IO (Decode16,
                        0x0074,             // Range Minimum
                        0x0074,             // Range Maximum
                        0x01,               // Alignment
                        0x0C,               // Length
                        )
                    IO (Decode16,
                        0x0091,             // Range Minimum
                        0x0091,             // Range Maximum
                        0x01,               // Alignment
                        0x03,               // Length
                        )
                    IO (Decode16,
                        0x00A2,             // Range Minimum
                        0x00A2,             // Range Maximum
                        0x01,               // Alignment
                        0x1E,               // Length
                        )
                    IO (Decode16,
                        0x00E0,             // Range Minimum
                        0x00E0,             // Range Maximum
                        0x01,               // Alignment
                        0x10,               // Length
                        )
                    IO (Decode16,
                        0x04D0,             // Range Minimum
                        0x04D0,             // Range Maximum
                        0x01,               // Alignment
                        0x02,               // Length
                        )
                })
            }

            Device (PIC)
            {
                Name (_HID, EisaId ("PNP0000"))
                Name (_CRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x0020,             // Range Minimum
                        0x0020,             // Range Maximum
                        0x01,               // Alignment
                        0x02,               // Length
                        )
                    IO (Decode16,
                        0x00A0,             // Range Minimum
                        0x00A0,             // Range Maximum
                        0x01,               // Alignment
                        0x02,               // Length
                        )
                    IRQNoFlags ()
                        {2}
                })
            }

            Device (DMA1)
            {
                Name (_HID, EisaId ("PNP0200"))
                Name (_CRS, ResourceTemplate ()
                {
                    DMA (Compatibility, BusMaster, Transfer8, )
                        {4}
                    IO (Decode16,
                        0x0000,             // Range Minimum
                        0x0000,             // Range Maximum
                        0x01,               // Alignment
                        0x10,               // Length
                        )
                    IO (Decode16,
                        0x0080,             // Range Minimum
                        0x0080,             // Range Maximum
                        0x01,               // Alignment
                        0x11,               // Length
                        )
                    IO (Decode16,
                        0x0094,             // Range Minimum
                        0x0094,             // Range Maximum
                        0x01,               // Alignment
                        0x0C,               // Length
                        )
                    IO (Decode16,
                        0x00C0,             // Range Minimum
                        0x00C0,             // Range Maximum
                        0x01,               // Alignment
                        0x20,               // Length
                        )
                })
            }

            Device (TMR)
            {
                Name (_HID, EisaId ("PNP0100"))
                Name (_CRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x0040,             // Range Minimum
                        0x0040,             // Range Maximum
                        0x01,               // Alignment
                        0x04,               // Length
                        )
                    IRQNoFlags ()
                        {0}
                })
            }

            Device (RTC)
            {
                Name (_HID, EisaId ("PNP0B00"))
                Name (_CRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x0070,             // Range Minimum
                        0x0070,             // Range Maximum
                        0x04,               // Alignment
                        0x04,               // Length
                        )
                    IRQNoFlags ()
                        {8}
                })
            }

            Device (SPKR)
            {
                Name (_HID, EisaId ("PNP0800"))
                Name (_CRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x0061,             // Range Minimum
                        0x0061,             // Range Maximum
                        0x01,               // Alignment
                        0x01,               // Length
                        )
                })
            }

            Device (COPR)
            {
                Name (_HID, EisaId ("PNP0C04"))
                Name (_CRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x00F0,             // Range Minimum
                        0x00F0,             // Range Maximum
                        0x01,               // Alignment
                        0x10,               // Length
                        )
                    IRQNoFlags ()
                        {13}
                })
            }

            OperationRegion (SPIO, SystemIO, 0x03F0, 0x02)
            Field (SPIO, ByteAcc, NoLock, Preserve)
            {
                INDX,   8, 
                DATA,   8
            }

            IndexField (INDX, DATA, ByteAcc, NoLock, Preserve)
            {
                        Offset (0xE0), 
                CRC0,   8, 
                CRC1,   8, 
                CRC2,   8, 
                CRC3,   8, 
                CRC4,   8, 
                CRC5,   8, 
                CRC6,   8, 
                CRC7,   8, 
                CRC8,   8, 
                CRC9,   8, 
                CRCA,   8, 
                CRCB,   8, 
                CRCC,   8, 
                CRCD,   8, 
                CRCE,   8, 
                CRCF,   8, 
                CRD0,   8, 
                CRD1,   8, 
                CRD2,   8, 
                CRD3,   8, 
                CRD4,   8, 
                CRD5,   8, 
                CRD6,   8, 
                CRD7,   8, 
                CRD8,   8
            }

            Method (ENFG, 0, NotSerialized)
            {
                Store (One, \_SB.PCI0.PIB.EN3C)
            }

            Method (EXFG, 0, NotSerialized)
            {
                Store (Zero, \_SB.PCI0.PIB.EN3C)
            }

            Device (FDC0)
            {
                Name (_HID, EisaId ("PNP0700"))
                Method (_STA, 0, NotSerialized)
                {
                    If (LNotEqual (\_SB.PCI0.PIB.EP3C, One))
                    {
                        Return (0x00)
                    }
                    Else
                    {
                        ENFG ()
                        Store (CRC2, Local0)
                        And (Local0, 0x10, Local0)
                        If (LNotEqual (Local0, 0x00))
                        {
                            EXFG ()
                            Return (0x0F)
                        }
                        Else
                        {
                            Store (CRC3, Local1)
                            If (LNotEqual (Local1, 0x00))
                            {
                                EXFG ()
                                Return (0x0D)
                            }
                            Else
                            {
                                EXFG ()
                                Return (0x00)
                            }
                        }
                    }
                }

                Method (_DIS, 0, NotSerialized)
                {
                    ENFG ()
                    Store (CRC2, Local0)
                    And (Local0, 0xEF, Local0)
                    Store (Local0, CRC2)
                    EXFG ()
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUFF, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x03F0,             // Range Minimum
                            0x03F0,             // Range Maximum
                            0x08,               // Alignment
                            0x06,               // Length
                            )
                        IO (Decode16,
                            0x03F7,             // Range Minimum
                            0x03F7,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IRQNoFlags ()
                            {6}
                        DMA (Compatibility, BusMaster, Transfer8, )
                            {2}
                    })
                    Return (BUFF)
                }

                Name (_PRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x03F0,             // Range Minimum
                        0x03F0,             // Range Maximum
                        0x08,               // Alignment
                        0x06,               // Length
                        )
                    IO (Decode16,
                        0x03F7,             // Range Minimum
                        0x03F7,             // Range Maximum
                        0x01,               // Alignment
                        0x01,               // Length
                        )
                    IRQNoFlags ()
                        {6}
                    DMA (Compatibility, BusMaster, Transfer8, )
                        {2}
                })
                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x02, IOLO)
                    CreateByteField (Arg0, 0x03, IOHI)
                    CreateWordField (Arg0, 0x11, IRQ0)
                    CreateByteField (Arg0, 0x14, DMA0)
                    ENFG ()
                    Store (CRC2, Local0)
                    And (Local0, 0xEF, Local1)
                    Store (Local1, CRC2)
                    Store (IOLO, Local0)
                    ShiftRight (Local0, 0x02, Local0)
                    And (Local0, 0xFC, Local0)
                    Store (IOHI, Local1)
                    ShiftLeft (Local1, 0x06, Local1)
                    Or (Local0, Local1, Local0)
                    Store (Local0, CRC3)
                    FindSetRightBit (IRQ0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.FLIR)
                    FindSetRightBit (DMA0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.FLDA)
                    Store (CRC2, Local0)
                    Or (Local0, 0x10, Local1)
                    Store (Local1, CRC2)
                    EXFG ()
                }
            }

            Device (UAR1)
            {
                Name (_HID, EisaId ("PNP0501"))
                Name (_UID, 0x01)
                Method (_STA, 0, NotSerialized)
                {
                    If (LNotEqual (\_SB.PCI0.PIB.EP3C, One))
                    {
                        Return (0x00)
                    }
                    Else
                    {
                        ENFG ()
                        Store (CRC2, Local0)
                        And (Local0, 0x04, Local0)
                        If (LNotEqual (Local0, 0x00))
                        {
                            EXFG ()
                            Return (0x0F)
                        }
                        Else
                        {
                            Store (CRC7, Local1)
                            If (LNotEqual (Local1, 0x00))
                            {
                                EXFG ()
                                Return (0x0D)
                            }
                            Else
                            {
                                EXFG ()
                                Return (0x00)
                            }
                        }
                    }
                }

                Method (_DIS, 0, NotSerialized)
                {
                    ENFG ()
                    And (CRC2, 0xFB, CRC2)
                    EXFG ()
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BFU1, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x03F8,             // Range Minimum
                            0x03F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            _Y0B)
                        IRQNoFlags (_Y0C)
                            {4}
                    })
                    CreateWordField (BFU1, \_SB.PCI0.UAR1._CRS._Y0B._MIN, IMIN)
                    CreateWordField (BFU1, \_SB.PCI0.UAR1._CRS._Y0B._MAX, IMAX)
                    CreateWordField (BFU1, \_SB.PCI0.UAR1._CRS._Y0C._INT, IRQ0)
                    ENFG ()
                    Store (CRC7, Local0)
                    Store (Local0, Local1)
                    And (Local1, 0xC0, Local1)
                    ShiftLeft (Local1, 0x02, Local1)
                    And (Local0, 0x3F, Local0)
                    ShiftLeft (Local0, 0x02, Local0)
                    Or (Local0, Local1, Local0)
                    Store (Local0, IMIN)
                    Store (Local0, IMAX)
                    EXFG ()
                    Store (\_SB.PCI0.PIB.U1IR, Local0)
                    Store (0x01, Local1)
                    ShiftLeft (Local1, Local0, IRQ0)
                    Return (BFU1)
                }

                Name (_PRS, ResourceTemplate ()
                {
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x03F8,             // Range Minimum
                            0x03F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {4}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x02F8,             // Range Minimum
                            0x02F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {3}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x03E8,             // Range Minimum
                            0x03E8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {4}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x02E8,             // Range Minimum
                            0x02E8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {3}
                    }
                    EndDependentFn ()
                })
                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x02, IOLO)
                    CreateByteField (Arg0, 0x03, IOHI)
                    CreateWordField (Arg0, 0x09, IRQ0)
                    ENFG ()
                    Store (CRC2, Local0)
                    And (Local0, 0xFB, Local1)
                    Store (Local1, CRC2)
                    Store (IOLO, Local0)
                    ShiftRight (Local0, 0x02, Local0)
                    And (Local0, 0xFE, Local0)
                    Store (IOHI, Local1)
                    ShiftLeft (Local1, 0x06, Local1)
                    Or (Local0, Local1, Local0)
                    Store (Local0, CRC7)
                    FindSetRightBit (IRQ0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.U1IR)
                    Store (CRC2, Local0)
                    Or (Local0, 0x04, Local1)
                    Store (Local1, CRC2)
                    EXFG ()
                }
            }

            Device (UAR2)
            {
                Name (_HID, EisaId ("PNP0501"))
                Name (_UID, 0x02)
                Method (_STA, 0, NotSerialized)
                {
                    If (LNotEqual (\_SB.PCI0.PIB.EP3C, One))
                    {
                        Return (0x00)
                    }
                    Else
                    {
                        ENFG ()
                        Store (CRCE, Local0)
                        And (Local0, 0x38, Local0)
                        If (LNotEqual (Local0, 0x08))
                        {
                            Store (CRC2, Local1)
                            And (Local1, 0x08, Local1)
                            If (LNotEqual (Local1, 0x00))
                            {
                                EXFG ()
                                Return (0x0F)
                            }
                            Else
                            {
                                Store (CRC8, Local1)
                                If (LNotEqual (Local1, 0x00))
                                {
                                    EXFG ()
                                    Return (0x0D)
                                }
                                Else
                                {
                                    EXFG ()
                                    Return (0x00)
                                }
                            }
                        }
                        Else
                        {
                            EXFG ()
                            Return (0x00)
                        }
                    }
                }

                Method (_DIS, 0, NotSerialized)
                {
                    ENFG ()
                    And (CRC2, 0xF7, CRC2)
                    EXFG ()
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BFU2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x02F8,             // Range Minimum
                            0x02F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            _Y0D)
                        IRQNoFlags (_Y0E)
                            {3}
                    })
                    CreateWordField (BFU2, \_SB.PCI0.UAR2._CRS._Y0D._MIN, IMIN)
                    CreateWordField (BFU2, \_SB.PCI0.UAR2._CRS._Y0D._MAX, IMAX)
                    CreateWordField (BFU2, \_SB.PCI0.UAR2._CRS._Y0E._INT, IRQ0)
                    ENFG ()
                    Store (CRC8, Local0)
                    Store (Local0, Local1)
                    And (Local1, 0xC0, Local1)
                    ShiftLeft (Local1, 0x02, Local1)
                    And (Local0, 0x3F, Local0)
                    ShiftLeft (Local0, 0x02, Local0)
                    Or (Local0, Local1, Local0)
                    Store (Local0, IMIN)
                    Store (Local0, IMAX)
                    EXFG ()
                    Store (\_SB.PCI0.PIB.U2IR, Local0)
                    Store (0x01, Local1)
                    ShiftLeft (Local1, Local0, IRQ0)
                    Return (BFU2)
                }

                Name (_PRS, ResourceTemplate ()
                {
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x03F8,             // Range Minimum
                            0x03F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {4}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x02F8,             // Range Minimum
                            0x02F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {3}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x03E8,             // Range Minimum
                            0x03E8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {4}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x02E8,             // Range Minimum
                            0x02E8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {3}
                    }
                    EndDependentFn ()
                })
                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x02, IOLO)
                    CreateByteField (Arg0, 0x03, IOHI)
                    CreateWordField (Arg0, 0x09, IRQ0)
                    ENFG ()
                    Store (CRC2, Local0)
                    And (Local0, 0xF7, Local1)
                    Store (Local1, CRC2)
                    Store (IOLO, Local0)
                    ShiftRight (Local0, 0x02, Local0)
                    And (Local0, 0xFE, Local0)
                    Store (IOHI, Local1)
                    ShiftLeft (Local1, 0x06, Local1)
                    Or (Local0, Local1, Local0)
                    Store (Local0, CRC8)
                    FindSetRightBit (IRQ0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.U2IR)
                    Store (CRC2, Local0)
                    Or (Local0, 0x08, Local1)
                    Store (Local1, CRC2)
                    EXFG ()
                }
            }

            Device (IRDA)
            {
                Name (_HID, EisaId ("PNP0510"))
                Method (_STA, 0, NotSerialized)
                {
                    If (LNotEqual (\_SB.PCI0.PIB.EP3C, One))
                    {
                        Return (0x00)
                    }

                    ENFG ()
                    Store (CRCE, Local0)
                    And (Local0, 0x38, Local0)
                    If (LEqual (Local0, 0x08))
                    {
                        And (CRC2, 0x08, Local1)
                        If (LNotEqual (Local1, 0x00))
                        {
                            EXFG ()
                            Return (0x0F)
                        }
                        Else
                        {
                            EXFG ()
                            Return (0x0D)
                        }
                    }
                    Else
                    {
                        EXFG ()
                        Return (0x00)
                    }
                }

                Method (_DIS, 0, NotSerialized)
                {
                    If (LEqual (DISE, 0x01))
                    {
                        ENFG ()
                        And (CRC2, 0xF7, CRC2)
                        EXFG ()
                    }

                    Store (Local0, Local0)
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BFU2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x02F8,             // Range Minimum
                            0x02F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            _Y0F)
                        IRQNoFlags (_Y10)
                            {3}
                    })
                    CreateWordField (BFU2, \_SB.PCI0.IRDA._CRS._Y0F._MIN, IMIN)
                    CreateWordField (BFU2, \_SB.PCI0.IRDA._CRS._Y0F._MAX, IMAX)
                    CreateWordField (BFU2, \_SB.PCI0.IRDA._CRS._Y10._INT, IRQ0)
                    ENFG ()
                    Store (CRC8, Local0)
                    Store (Local0, Local1)
                    And (Local1, 0xC0, Local1)
                    ShiftLeft (Local1, 0x02, Local1)
                    And (Local0, 0x3F, Local0)
                    ShiftLeft (Local0, 0x02, Local0)
                    Or (Local0, Local1, Local0)
                    Store (Local0, IMIN)
                    Store (Local0, IMAX)
                    EXFG ()
                    Store (\_SB.PCI0.PIB.U2IR, Local0)
                    Store (0x01, Local1)
                    ShiftLeft (Local1, Local0, IRQ0)
                    Return (BFU2)
                }

                Name (_PRS, ResourceTemplate ()
                {
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x03F8,             // Range Minimum
                            0x03F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {4}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x02F8,             // Range Minimum
                            0x02F8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {3}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x03E8,             // Range Minimum
                            0x03E8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {4}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x02E8,             // Range Minimum
                            0x02E8,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {3}
                    }
                    EndDependentFn ()
                })
                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x02, IOLO)
                    CreateByteField (Arg0, 0x03, IOHI)
                    CreateWordField (Arg0, 0x09, IRQ0)
                    ENFG ()
                    Store (CRC2, Local0)
                    And (Local0, 0xF7, Local1)
                    Store (Local1, CRC2)
                    Store (IOLO, Local0)
                    ShiftRight (Local0, 0x02, Local0)
                    And (Local0, 0xFE, Local0)
                    Store (IOHI, Local1)
                    ShiftLeft (Local1, 0x06, Local1)
                    Or (Local0, Local1, Local0)
                    Store (Local0, CRC8)
                    FindSetRightBit (IRQ0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.U2IR)
                    Store (CRC2, Local0)
                    Or (Local0, 0x08, Local1)
                    Store (Local1, CRC2)
                    EXFG ()
                }
            }

            Device (LPT1)
            {
                Name (PIOM, Buffer (0x01)
                {
                    0x00
                })
                CreateByteField (PIOM, 0x00, LPTM)
                Name (_HID, EisaId ("PNP0400"))
                Method (_STA, 0, NotSerialized)
                {
                    If (LNotEqual (\_SB.PCI0.PIB.EP3C, One))
                    {
                        Return (0x00)
                    }
                    Else
                    {
                        ENFG ()
                        Store (CRC2, Local0)
                        And (Local0, 0x03, Local0)
                        If (LEqual (Local0, 0x01))
                        {
                            EXFG ()
                            Return (0x00)
                        }

                        If (LEqual (Local0, 0x03))
                        {
                            Store (CRC6, Local1)
                            If (LNotEqual (Local1, 0x00))
                            {
                                EXFG ()
                                Return (0x0D)
                            }
                            Else
                            {
                                EXFG ()
                                Return (0x00)
                            }
                        }
                        Else
                        {
                            Store (Local0, LPTM)
                            EXFG ()
                            Return (0x0F)
                        }
                    }
                }

                Method (_DIS, 0, NotSerialized)
                {
                    ENFG ()
                    Or (CRC2, 0x03, CRC2)
                    EXFG ()
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUFL, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0378,             // Range Minimum
                            0x0378,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            _Y11)
                        IRQNoFlags (_Y12)
                            {7}
                    })
                    CreateWordField (BUFL, \_SB.PCI0.LPT1._CRS._Y11._MIN, IMIN)
                    CreateWordField (BUFL, \_SB.PCI0.LPT1._CRS._Y11._MAX, IMAX)
                    CreateByteField (BUFL, \_SB.PCI0.LPT1._CRS._Y11._ALN, LALN)
                    CreateByteField (BUFL, \_SB.PCI0.LPT1._CRS._Y11._LEN, LLEN)
                    CreateWordField (BUFL, \_SB.PCI0.LPT1._CRS._Y12._INT, IRQ0)
                    ENFG ()
                    Store (CRC6, Local0)
                    EXFG ()
                    Store (Local0, Local1)
                    And (Local1, 0xC0, Local1)
                    ShiftLeft (Local1, 0x02, Local1)
                    ShiftLeft (Local0, 0x02, Local0)
                    Or (Local0, Local1, Local0)
                    Store (Local0, IMIN)
                    Store (Local0, IMAX)
                    If (LEqual (IMIN, 0x03BC))
                    {
                        Store (0x04, LALN)
                        Store (0x04, LLEN)
                    }
                    Else
                    {
                        Store (0x08, LALN)
                        Store (0x08, LLEN)
                    }

                    Store (\_SB.PCI0.PIB.LPIR, Local0)
                    Store (0x01, Local1)
                    ShiftLeft (Local1, Local0, IRQ0)
                    Return (BUFL)
                }

                Name (_PRS, ResourceTemplate ()
                {
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x0378,             // Range Minimum
                            0x0378,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {7}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x0278,             // Range Minimum
                            0x0278,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IRQNoFlags ()
                            {5}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x03BC,             // Range Minimum
                            0x03BC,             // Range Maximum
                            0x04,               // Alignment
                            0x04,               // Length
                            )
                        IRQNoFlags ()
                            {7}
                    }
                    EndDependentFn ()
                })
                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x02, IOLO)
                    CreateByteField (Arg0, 0x03, IOHI)
                    CreateWordField (Arg0, 0x09, IRQ0)
                    ENFG ()
                    Store (CRC2, Local0)
                    Or (Local0, 0x03, Local0)
                    Store (Local0, CRC2)
                    Store (IOLO, Local0)
                    ShiftRight (Local0, 0x02, Local0)
                    Store (IOHI, Local1)
                    ShiftLeft (Local1, 0x06, Local1)
                    Or (Local0, Local1, Local0)
                    Store (Local0, CRC6)
                    FindSetRightBit (IRQ0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.LPIR)
                    Store (CRC2, Local0)
                    And (Local0, 0xFC, Local0)
                    Store (LPTM, Local1)
                    Or (Local0, Local1, Local1)
                    Store (Local1, CRC2)
                    EXFG ()
                }
            }

            Device (ECP1)
            {
                Name (_HID, EisaId ("PNP0401"))
                Method (_STA, 0, NotSerialized)
                {
                    If (LNotEqual (\_SB.PCI0.PIB.EP3C, One))
                    {
                        Return (0x00)
                    }

                    ENFG ()
                    Store (CRC2, Local0)
                    And (Local0, 0x03, Local0)
                    If (LOr (LEqual (Local0, 0x00), LEqual (Local0, 0x02)))
                    {
                        EXFG ()
                        Return (0x00)
                    }

                    If (LEqual (Local0, 0x01))
                    {
                        EXFG ()
                        Return (0x0F)
                    }

                    If (LEqual (Local0, 0x03))
                    {
                        If (LNotEqual (\_SB.PCI0.PIB.LPDA, 0x00))
                        {
                            EXFG ()
                            Return (0x0D)
                        }
                        Else
                        {
                            EXFG ()
                            Return (0x00)
                        }
                    }
                }

                Method (_DIS, 0, NotSerialized)
                {
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUFE, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0378,             // Range Minimum
                            0x0378,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            _Y13)
                        IO (Decode16,
                            0x0778,             // Range Minimum
                            0x0778,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            _Y14)
                        IRQNoFlags (_Y15)
                            {7}
                        DMA (Compatibility, NotBusMaster, Transfer8, _Y16)
                            {3}
                    })
                    CreateWordField (BUFE, \_SB.PCI0.ECP1._CRS._Y13._MIN, IMI1)
                    CreateWordField (BUFE, \_SB.PCI0.ECP1._CRS._Y13._MAX, IMA1)
                    CreateByteField (BUFE, \_SB.PCI0.ECP1._CRS._Y13._ALN, ALN1)
                    CreateByteField (BUFE, \_SB.PCI0.ECP1._CRS._Y13._LEN, LEN1)
                    CreateWordField (BUFE, \_SB.PCI0.ECP1._CRS._Y14._MIN, IMI2)
                    CreateWordField (BUFE, \_SB.PCI0.ECP1._CRS._Y14._MAX, IMA2)
                    CreateByteField (BUFE, \_SB.PCI0.ECP1._CRS._Y14._ALN, ALN2)
                    CreateByteField (BUFE, \_SB.PCI0.ECP1._CRS._Y14._LEN, LEN2)
                    CreateWordField (BUFE, \_SB.PCI0.ECP1._CRS._Y15._INT, IRQ0)
                    CreateByteField (BUFE, \_SB.PCI0.ECP1._CRS._Y16._DMA, DMA0)
                    ENFG ()
                    Store (CRC6, Local0)
                    EXFG ()
                    Store (Local0, Local1)
                    And (Local1, 0xC0, Local1)
                    ShiftLeft (Local1, 0x02, Local1)
                    ShiftLeft (Local0, 0x02, Local0)
                    Or (Local0, Local1, Local0)
                    Store (Local0, IMI1)
                    Store (Local0, IMA1)
                    Add (Local0, 0x0400, Local0)
                    Store (Local0, IMI2)
                    Store (Local0, IMA2)
                    If (LEqual (IMI1, 0x03BC))
                    {
                        Store (0x04, ALN1)
                        Store (0x04, LEN1)
                        Store (0x04, ALN2)
                        Store (0x04, LEN2)
                    }
                    Else
                    {
                        Store (0x08, ALN1)
                        Store (0x08, LEN1)
                        Store (0x04, ALN2)
                        Store (0x04, LEN2)
                    }

                    Store (\_SB.PCI0.PIB.LPIR, Local0)
                    Store (0x01, Local1)
                    ShiftLeft (Local1, Local0, IRQ0)
                    Store (\_SB.PCI0.PIB.LPDA, Local0)
                    And (Local0, 0x03, Local0)
                    Store (0x01, Local1)
                    ShiftLeft (Local1, Local0, DMA0)
                    Return (BUFE)
                }

                Name (_PRS, ResourceTemplate ()
                {
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x0378,             // Range Minimum
                            0x0378,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IO (Decode16,
                            0x0778,             // Range Minimum
                            0x0778,             // Range Maximum
                            0x04,               // Alignment
                            0x04,               // Length
                            )
                        IRQNoFlags ()
                            {7}
                        DMA (Compatibility, NotBusMaster, Transfer8, )
                            {1,3}
                    }
                    StartDependentFnNoPri ()
                    {
                        IO (Decode16,
                            0x0278,             // Range Minimum
                            0x0278,             // Range Maximum
                            0x08,               // Alignment
                            0x08,               // Length
                            )
                        IO (Decode16,
                            0x0678,             // Range Minimum
                            0x0678,             // Range Maximum
                            0x04,               // Alignment
                            0x04,               // Length
                            )
                        IRQNoFlags ()
                            {5}
                        DMA (Compatibility, NotBusMaster, Transfer8, )
                            {1,3}
                    }
                    EndDependentFn ()
                })
                Method (_SRS, 1, NotSerialized)
                {
                    CreateByteField (Arg0, 0x02, IOLO)
                    CreateByteField (Arg0, 0x03, IOHI)
                    CreateWordField (Arg0, 0x11, IRQ0)
                    CreateByteField (Arg0, 0x14, DMA0)
                    ENFG ()
                    Store (CRC2, Local0)
                    Or (Local0, 0x03, Local0)
                    Store (Local0, CRC2)
                    Store (IOLO, Local0)
                    ShiftRight (Local0, 0x02, Local0)
                    Store (IOHI, Local1)
                    ShiftLeft (Local1, 0x06, Local1)
                    Or (Local0, Local1, Local0)
                    Store (Local0, CRC6)
                    FindSetRightBit (IRQ0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.LPIR)
                    FindSetRightBit (DMA0, Local0)
                    If (LGreater (Local0, 0x00))
                    {
                        Decrement (Local0)
                    }

                    Store (Local0, \_SB.PCI0.PIB.LPDA)
                    Store (CRC2, Local0)
                    And (Local0, 0xFC, Local0)
                    Or (Local0, 0x01, Local0)
                    Store (Local0, CRC2)
                    EXFG ()
                }
            }

            Device (PS2M)
            {
                Name (_HID, EisaId ("PNP0F13"))
                Method (_STA, 0, NotSerialized)
                {
                    If (LEqual (PS2F, 0x00))
                    {
                        Return (0x0F)
                    }
                    Else
                    {
                        Return (0x00)
                    }
                }

                Method (_CRS, 0, NotSerialized)
                {
                    Name (BUF1, ResourceTemplate ()
                    {
                        IRQNoFlags ()
                            {12}
                    })
                    Name (BUF2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0060,             // Range Minimum
                            0x0060,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IO (Decode16,
                            0x0064,             // Range Minimum
                            0x0064,             // Range Maximum
                            0x01,               // Alignment
                            0x01,               // Length
                            )
                        IRQNoFlags ()
                            {12}
                    })
                    If (LEqual (KBDI, 0x01))
                    {
                        Return (BUF2)
                    }
                    Else
                    {
                        Return (BUF1)
                    }
                }
            }

            Device (PS2K)
            {
                Name (_HID, EisaId ("PNP0303"))
                Method (_STA, 0, NotSerialized)
                {
                    If (LEqual (KBDI, 0x01))
                    {
                        Return (0x00)
                    }
                    Else
                    {
                        Return (0x0F)
                    }
                }

                Name (_CRS, ResourceTemplate ()
                {
                    IO (Decode16,
                        0x0060,             // Range Minimum
                        0x0060,             // Range Maximum
                        0x01,               // Alignment
                        0x01,               // Length
                        )
                    IO (Decode16,
                        0x0064,             // Range Minimum
                        0x0064,             // Range Maximum
                        0x01,               // Alignment
                        0x01,               // Length
                        )
                    IRQNoFlags ()
                        {1}
                })
            }

            Method (_PRW, 0, NotSerialized)
            {
                And (SUSF, 0x01, STAT)
                If (STAT)
                {
                    Return (Package (0x02)
                    {
                        0x05, 
                        0x03
                    })
                }
                Else
                {
                    Return (Package (0x02)
                    {
                        0x05, 
                        0x01
                    })
                }
            }

            Method (\_SB.PCI0.UAR1._PRW, 0, NotSerialized)
            {
                If (OSFL)
                {
                    Return (Package (0x02)
                    {
                        0x08, 
                        0x04
                    })
                }
                Else
                {
                    If (STAT)
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x03
                        })
                    }
                    Else
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x01
                        })
                    }
                }
            }

            Method (\_SB.PCI0.UAR2._PRW, 0, NotSerialized)
            {
                If (OSFL)
                {
                    Return (Package (0x02)
                    {
                        0x08, 
                        0x04
                    })
                }
                Else
                {
                    If (STAT)
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x03
                        })
                    }
                    Else
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x01
                        })
                    }
                }
            }

            Method (\_SB.PCI0.LPT1._PRW, 0, NotSerialized)
            {
                If (OSFL)
                {
                    Return (Package (0x02)
                    {
                        0x08, 
                        0x04
                    })
                }
                Else
                {
                    If (STAT)
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x03
                        })
                    }
                    Else
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x01
                        })
                    }
                }
            }

            Method (\_SB.PCI0.ECP1._PRW, 0, NotSerialized)
            {
                If (OSFL)
                {
                    Return (Package (0x02)
                    {
                        0x08, 
                        0x04
                    })
                }
                Else
                {
                    If (STAT)
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x03
                        })
                    }
                    Else
                    {
                        Return (Package (0x02)
                        {
                            0x08, 
                            0x01
                        })
                    }
                }
            }
        }
    }
}

```
# FACS #
```
/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20061109
 *
 * Disassembly of facs.aml, Wed Mar 19 23:13:21 2008
 *
 * ACPI Data Table [FACS]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 000  4]                    Signature : "FACS"
[004h 004  4]                       Length : 00000040
[008h 008  4]           Hardware Signature : 00000000
[00Ch 012  4]   Firmware Waking Vector(32) : 00000000
[010h 016  4]                  Global Lock : 00000000
[014h 020  4]        Flags (decoded below) : 00000000
                    S4BIOS Support Present : 0
[018h 024  8]   Firmware Waking Vector(64) : 0000000000000000
[020h 032  1]                      Version : 00

Raw Table Data

  0000: 46 41 43 53 40 00 00 00 00 00 00 00 00 00 00 00  FACS@...........
  0010: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................

```
# FACP #
```
/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20061109
 *
 * Disassembly of facp.aml, Wed Mar 19 23:13:13 2008
 *
 * ACPI Data Table [FACP]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 000  4]                    Signature : "FACP"    /* Fixed ACPI Description Table */
[004h 004  4]                 Table Length : 00000074
[008h 008  1]                     Revision : 01
[009h 009  1]                     Checksum : 70
[00Ah 010  6]                       Oem ID : "VIA694"
[010h 016  8]                 Oem Table ID : "MSI ACPI"
[018h 024  4]                 Oem Revision : 42302E31
[01Ch 028  4]              Asl Compiler ID : "AWRD"
[020h 032  4]        Asl Compiler Revision : 00000000

[024h 036  4]                 FACS Address : 2FFF0000
[028h 040  4]                 DSDT Address : 2FFF30C0
[02Ch 044  1]                        Model : 00
[02Dh 045  1]                   PM Profile : 00
[02Eh 046  2]                SCI Interrupt : 0003
[030h 048  4]             SMI Command Port : 0000402F
[034h 052  1]            ACPI Enable Value : A1
[035h 053  1]           ACPI Disable Value : A0
[036h 054  1]               S4BIOS Command : 00
[037h 055  1]              P-State Control : 00
[038h 056  4]     PM1A Event Block Address : 00004000
[03Ch 060  4]     PM1B Event Block Address : 00000000
[040h 064  4]   PM1A Control Block Address : 000040F0
[044h 068  4]   PM1B Control Block Address : 00000000
[048h 072  4]    PM2 Control Block Address : 00000000
[04Ch 076  4]       PM Timer Block Address : 00004008
[050h 080  4]           GPE0 Block Address : 00004020
[054h 084  4]           GPE1 Block Address : 00000000
[058h 088  1]       PM1 Event Block Length : 04
[059h 089  1]     PM1 Control Block Length : 02
[05Ah 090  1]     PM2 Control Block Length : 00
[05Bh 091  1]        PM Timer Block Length : 04
[05Ch 092  1]            GPE0 Block Length : 04
[05Dh 093  1]            GPE1 Block Length : 00
[05Eh 094  1]             GPE1 Base Offset : 00
[05Fh 095  1]                 _CST Support : 00
[060h 096  2]                   C2 Latency : 005A
[062h 098  2]                   C3 Latency : 0384
[064h 100  2]               CPU Cache Size : 0000
[066h 102  2]           Cache Flush Stride : 0000
[068h 104  1]            Duty Cycle Offset : 00
[069h 105  1]             Duty Cycle Width : 01
[06Ah 106  1]          RTC Day Alarm Index : 7D
[06Bh 107  1]        RTC Month Alarm Index : 7E
[06Ch 108  1]            RTC Century Index : 32
[06Dh 109  2]      Boot Architecture Flags : 0000
[06Fh 111  1]                     Reserved : 00
[070h 112  4]        Flags (decoded below) : 00000025
                     WBINVD is operational : 1
                WBINVD does not invalidate : 0
                       All CPUs support C1 : 1
                     C2 works on MP system : 0
                   Power button is generic : 0
                   Sleep button is generic : 1
                      RTC wakeup not fixed : 0
                RTC wakeup/S4 not possible : 0
                           32-bit PM Timer : 0
                         Docking Supported : 0

Raw Table Data

  0000: 46 41 43 50 74 00 00 00 01 70 56 49 41 36 39 34  FACPt....pVIA694
  0010: 4D 53 49 20 41 43 50 49 31 2E 30 42 41 57 52 44  MSI ACPI1.0BAWRD
  0020: 00 00 00 00 00 00 FF 2F C0 30 FF 2F 00 00 03 00  ......./.0./....
  0030: 2F 40 00 00 A1 A0 00 00 00 40 00 00 00 00 00 00  /@.......@......
  0040: F0 40 00 00 00 00 00 00 00 00 00 00 08 40 00 00  .@...........@..
  0050: 20 40 00 00 00 00 00 00 04 02 00 04 04 00 00 00   @..............
  0060: 5A 00 84 03 00 00 00 00 00 01 7D 7E 32 00 00 00  Z.........}~2...
  0070: 25 00 00 00                                      %...
```

# RSDT #
```
/*
 * Intel ACPI Component Architecture
 * AML Disassembler version 20061109
 *
 * Disassembly of rsdt.aml, Wed Mar 19 23:13:26 2008
 *
 * ACPI Data Table [RSDT]
 *
 * Format: [HexOffset DecimalOffset ByteLength]  FieldName : FieldValue
 */

[000h 000  4]                    Signature : "RSDT"    /* Root System Description Table */
[004h 004  4]                 Table Length : 00000028
[008h 008  1]                     Revision : 01
[009h 009  1]                     Checksum : 54
[00Ah 010  6]                       Oem ID : "VIA694"
[010h 016  8]                 Oem Table ID : "MSI ACPI"
[018h 024  4]                 Oem Revision : 42302E31
[01Ch 028  4]              Asl Compiler ID : "AWRD"
[020h 032  4]        Asl Compiler Revision : 00000000

[024h 036  4]       ACPI Table Address   0 : 2FFF3040

Raw Table Data

  0000: 52 53 44 54 28 00 00 00 01 54 56 49 41 36 39 34  RSDT(....TVIA694
  0010: 4D 53 49 20 41 43 50 49 31 2E 30 42 41 57 52 44  MSI ACPI1.0BAWRD
  0020: 00 00 00 00 40 30 FF 2F                          ....@0./

```