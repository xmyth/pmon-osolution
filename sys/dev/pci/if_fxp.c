/*	$OpenBSD: if_fxp.c,v 1.25 2000/03/30 02:49:35 jason Exp $	*/
/*	$NetBSD: if_fxp.c,v 1.2 1997/06/05 02:01:55 thorpej Exp $	*/

/*
 * Copyright (c) 1995, David Greenman
 * All rights reserved.
 *
 * Modifications to support NetBSD:
 * Copyright (c) 1997 Jason R. Thorpe.  All rights reserved.
 *
 * Modifications to support MIPS Arch:
 * Copyright (c) 1999 Opsycon AB (www.opsycon.se). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	Id: if_fxp.c,v 1.55 1998/08/04 08:53:12 dg Exp
 */

/*
 * Intel EtherExpress Pro/100B PCI Fast Ethernet driver
 */

#include "bpfilter.h"

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/malloc.h>
#include <sys/kernel.h>
#include <sys/socket.h>
#include <sys/syslog.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_media.h>
#include <net/if_types.h>

#ifdef INET
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#endif

#ifdef IPX
#include <netipx/ipx.h>
#include <netipx/ipx_if.h>
#endif

#ifdef NS
#include <netns/ns.h>
#include <netns/ns_if.h>
#endif

#if NBPFILTER > 0
#include <net/bpf.h>
#include <net/bpfdesc.h>
#endif

#if defined(__NetBSD__) || defined(__OpenBSD__)

#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/device.h>

#if defined(__NetBSD__)
#include <net/if_ether.h>
#include <netinet/if_inarp.h>
#endif

#if defined(__OpenBSD__)
#include <netinet/if_ether.h>
#endif

#include <vm/vm.h>

#include <machine/cpu.h>
#include <machine/bus.h>
#include <machine/intr.h>

#include <dev/mii/miivar.h>

#include <dev/pci/pcivar.h>
#include <dev/pci/pcireg.h>
#include <dev/pci/pcidevs.h>

#include <dev/pci/if_fxpreg.h>
#include <dev/pci/if_fxpvar.h>

#ifdef __alpha__		/* XXX */
/* XXX XXX NEED REAL DMA MAPPING SUPPORT XXX XXX */
#undef vtophys
#define	vtophys(va)	alpha_XXX_dmamap((vm_offset_t)(va))
#endif /* __alpha__ */

#else /* __FreeBSD__ */

#include <sys/sockio.h>

#include <netinet/if_ether.h>

#include <vm/vm.h>		/* for vtophys */
#include <vm/vm_param.h>	/* for vtophys */
#include <vm/pmap.h>		/* for vtophys */
#include <machine/clock.h>	/* for DELAY */

#include <pci/pcivar.h>
#include <pci/if_fxpreg.h>
#include <pci/if_fxpvar.h>

#endif /* __NetBSD__ || __OpenBSD__ */

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/*
 * NOTE!  On the Alpha, we have an alignment constraint.  The
 * card DMAs the packet immediately following the RFA.  However,
 * the first thing in the packet is a 14-byte Ethernet header.
 * This means that the packet is misaligned.  To compensate,
 * we actually offset the RFA 2 bytes into the cluster.  This
 * aligns the packet after the Ethernet header at a 32-bit
 * boundary.  HOWEVER!  This means that the RFA is misaligned!
 */

#ifdef BADPCIBRIDGE
#define BADPCIBRIDGE
#define	RFA_ALIGNMENT_FUDGE	4
#else
#define	RFA_ALIGNMENT_FUDGE	2
#endif

int fxp_debug = 0;

/*
 * Inline function to copy a 16-bit aligned 32-bit quantity.
 */
static __inline void fxp_lwcopy __P((volatile u_int32_t *,
	volatile u_int32_t *));
static __inline void
fxp_lwcopy(src, dst)
	volatile u_int32_t *src, *dst;
{
	volatile u_int16_t *a = (u_int16_t *)src;
	volatile u_int16_t *b = (u_int16_t *)dst;

	b[0] = a[0];
	b[1] = a[1];
}

/*
 * Template for default configuration parameters.
 * See struct fxp_cb_config for the bit definitions.
 */
static u_char fxp_cb_config_template[] = {
#if BYTE_ORDER == BIG_ENDIAN
	0x0, 0x0,		/* cb_status */
	0x2, 0x80,		/* cb_command */
	0xff, 0xff, 0xff, 0xff,	/* link_addr */
	0x16,	/*  0 */
	0x08,	/*  1 */
	0x0,	/*  2 */
	0x0,	/*  3 */
	0x0,	/*  4 */
	0x8,	/*  5 */ /* XXX! */
	0xb2,	/*  6 */
	0x3,	/*  7 */
	0x1,	/*  8 */
	0x0,	/*  9 */
	0x2e,	/* 10 */
	0x0,	/* 11 */
	0x60,	/* 12 */
	0x0,	/* 13 */
	0xf2,	/* 14 */
	0x48,	/* 15 */
	0x0,	/* 16 */
	0x40,	/* 17 */
	0xf3,	/* 18 */
	0x0,	/* 19 */
	0x3f,	/* 20 */
	0x5	/* 21 */
#else
	0x0, 0x0,		/* cb_status */
	0x2, 0x80,		/* cb_command */
	0xff, 0xff, 0xff, 0xff,	/* link_addr */
	0x16,	/*  0 */
	0x8,	/*  1 */
	0x0,	/*  2 */
	0x0,	/*  3 */
	0x0,	/*  4 */
	0x80,	/*  5 */
	0xb2,	/*  6 */
	0x3,	/*  7 */
	0x1,	/*  8 */
	0x0,	/*  9 */
	0x2e,	/* 10 */
	0x0,	/* 11 */
	0x60,	/* 12 */
	0x0,	/* 13 */
	0xf2,	/* 14 */
	0x48,	/* 15 */
	0x0,	/* 16 */
	0x40,	/* 17 */
	0xf3,	/* 18 */
	0x0,	/* 19 */
	0x3f,	/* 20 */
	0x5	/* 21 */
#endif
};

/* Supported media types. */
struct fxp_supported_media {
	const int	fsm_phy;	/* PHY type */
	const int	*fsm_media;	/* the media array */
	const int	fsm_nmedia;	/* the number of supported media */
	const int	fsm_defmedia;	/* default media for this PHY */
};

static int fxp_mediachange	__P((struct ifnet *));
static void fxp_mediastatus	__P((struct ifnet *, struct ifmediareq *));
static inline void fxp_scb_wait	__P((struct fxp_softc *));
FXP_INTR_TYPE fxp_intr	__P((void *));
static void fxp_start		__P((struct ifnet *));
static int fxp_ioctl		__P((struct ifnet *,
				    FXP_IOCTLCMD_TYPE, caddr_t));
static int fxp_init		__P((void *));
static void fxp_stop		__P((struct fxp_softc *, int));
static void fxp_watchdog	__P((struct ifnet *));
static int fxp_add_rfabuf	__P((struct fxp_softc *, struct mbuf *));
static int fxp_mdi_read		__P((struct device *, int, int));
static void fxp_mdi_write	__P((struct device *, int, int, int));
static void fxp_autosize_eeprom	__P((struct fxp_softc *));
static void fxp_statchg		__P((struct device *));
void fxp_read_eeprom	__P((struct fxp_softc *, u_int16_t *,
				    int, int));
void fxp_write_eeprom	__P((struct fxp_softc *, u_int16_t *,
				    int, int));
static int fxp_attach_common	__P((struct fxp_softc *, u_int8_t *));

void fxp_stats_update		__P((void *));
#ifdef USE_FXP_MCAST
void fxp_mc_setup	__P((struct fxp_softc *));
#endif

/*
 * Set initial transmit threshold at 64 (512 bytes). This is
 * increased by 64 (512 bytes) at a time, to maximum of 192
 * (1536 bytes), if an underrun occurs.
 */
static int tx_threshold = 64;

/*
 * Number of transmit control blocks. This determines the number
 * of transmit buffers that can be chained in the CB list.
 * This must be a power of two.
 */
#define FXP_NTXCB	16

/*
 * Number of completed TX commands at which point an interrupt
 * will be generated to garbage collect the attached buffers.
 * Must be at least one less than FXP_NTXCB, and should be
 * enough less so that the transmitter doesn't becomes idle
 * during the buffer rundown (which would reduce performance).
 */
#define FXP_CXINT_THRESH 12

/*
 * TxCB list index mask. This is used to do list wrap-around.
 */
#define FXP_TXCB_MASK	(FXP_NTXCB - 1)

/*
 * Number of receive frame area buffers. These are large so chose
 * wisely.
 */
#define FXP_NRFABUFS	16

/*
 * Maximum number of seconds that the receiver can be idle before we
 * assume it's dead and attempt to reset it by reprogramming the
 * multicast filter. This is part of a work-around for a bug in the
 * NIC. See fxp_stats_update().
 */
#define FXP_MAX_RX_IDLE	15

/*
 * IPU: Maximum number of status reads before giving up in fxp_init
 * because of "bus congestion".
 */
#ifndef FXP_MAX_STATUS_READS
#define FXP_MAX_STATUS_READS 500
#endif

/*
 * IPU: Delay timer before trying to call fxp_init again
 * after a "bus congestion" failure.
 */
#ifndef FXP_DELAY_BEFORE_REINIT
#define FXP_DELAY_BEFORE_REINIT 2
#endif

/*
 * Wait for the previous command to be accepted (but not necessarily
 * completed).
 */
static inline void
fxp_scb_wait(sc)
	struct fxp_softc *sc;
{
	int i = 10000;


	while (CSR_READ_1(sc, FXP_CSR_SCB_COMMAND) && --i) DELAY(2);
}

/*************************************************************
 * Operating system-specific autoconfiguration glue
 *************************************************************/

#if defined(__BROKEN_INDIRECT_CONFIG) || defined(__OpenBSD__)
static int fxp_match __P((struct device *, void *, void *));
#else
static int fxp_match __P((struct device *, struct cfdata *, void *));
#endif
static void fxp_attach __P((struct device *, struct device *, void *));

static void	fxp_shutdown __P((void *));
void	fxp_power __P((int, void *));

/* Compensate for lack of a generic ether_ioctl() */
static int	fxp_ether_ioctl __P((struct ifnet *,
				    FXP_IOCTLCMD_TYPE, caddr_t));
#define	ether_ioctl	fxp_ether_ioctl

struct cfattach fxp_ca = {
	sizeof(struct fxp_softc), fxp_match, fxp_attach
};

struct cfdriver fxp_cd = {
	NULL, "fxp", DV_IFNET
};

/*
 * Check if a device is an 82557.
 */
static int
fxp_match(parent, match, aux)
	struct device *parent;
#if defined(__BROKEN_INDIRECT_CONFIG) || defined(__OpenBSD__)
	void *match;
#else
	struct cfdata *match;
#endif
	void *aux;
{
	struct pci_attach_args *pa = aux;

	if (PCI_VENDOR(pa->pa_id) != PCI_VENDOR_INTEL)
		return (0);

	switch (PCI_PRODUCT(pa->pa_id)) {
	case PCI_PRODUCT_INTEL_82557:
	case PCI_PRODUCT_INTEL_82559:
	case PCI_PRODUCT_INTEL_82559ER:
		return (1);
	}

	return (0);
}

static void
fxp_attach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	struct fxp_softc *sc = (struct fxp_softc *)self;
	struct pci_attach_args *pa = aux;
/*	struct pci_attach_args *pa = (void *)0x800785d0;*/
	pci_chipset_tag_t pc = pa->pa_pc;
	pci_intr_handle_t ih;
	const char *intrstr = NULL;
	u_int8_t enaddr[6];
	struct ifnet *ifp;
#ifdef __OpenBSD__
	bus_space_tag_t iot = pa->pa_iot;
	bus_addr_t iobase;
	bus_size_t iosize;
#endif

#ifndef __OpenBSD__
	/*
	 * Map control/status registers.
	 */
	if (pci_mapreg_map(pa, FXP_PCI_MMBA, PCI_MAPREG_TYPE_MEM, 0,
	    &sc->sc_st, &sc->sc_sh, NULL, NULL)) {
		printf(": can't map registers\n");
		return;
	}
#else
	if (pci_io_find(pc, pa->pa_tag, FXP_PCI_IOBA, &iobase, &iosize)) {
		printf(": can't find i/o space\n");
		return;
	}

	if (bus_space_map(iot, iobase, iosize, 0, &sc->sc_sh)) {
		printf(": can't map i/o space\n");
		return;
	}
	sc->sc_st = iot;
	sc->sc_pc = pc;
#endif
	/*
	 * Allocate our interrupt.
	 */
	if (pci_intr_map(pc, pa->pa_intrtag, pa->pa_intrpin,
	    pa->pa_intrline, &ih)) {
		printf(": couldn't map interrupt\n");
		return;
	}
	
	intrstr = pci_intr_string(pc, ih);
#ifdef __OpenBSD__
	sc->sc_ih = pci_intr_establish(pc, ih, IPL_NET, fxp_intr, sc,
	    self->dv_xname);
#else
	sc->sc_ih = pci_intr_establish(pc, ih, IPL_NET, fxp_intr, sc);
#endif
	
	if (sc->sc_ih == NULL) {
		printf(": couldn't establish interrupt");
		if (intrstr != NULL)
			printf(" at %s", intrstr);
		printf("\n");
		return;
	}
	
	/* Do generic parts of attach. */
	if (fxp_attach_common(sc, enaddr)) {
		/* Failed! */
		return;
	}

#ifdef __OpenBSD__
	ifp = &sc->arpcom.ac_if;
	bcopy(enaddr, sc->arpcom.ac_enaddr, sizeof(enaddr));
#else
	ifp = &sc->sc_ethercom.ec_if;
#endif
	bcopy(sc->sc_dev.dv_xname, ifp->if_xname, IFNAMSIZ);
	
	ifp->if_softc = sc;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = fxp_ioctl;
	ifp->if_start = fxp_start;
	ifp->if_watchdog = fxp_watchdog;

	printf(": %s, address %s\n", intrstr,
	    ether_sprintf(sc->arpcom.ac_enaddr));

	/*
	 * Initialize our media structures and probe the MII.
	 */
	sc->sc_mii.mii_ifp = ifp;
	sc->sc_mii.mii_readreg = fxp_mdi_read;
	sc->sc_mii.mii_writereg = fxp_mdi_write;
	sc->sc_mii.mii_statchg = fxp_statchg;
	ifmedia_init(&sc->sc_mii.mii_media, 0, fxp_mediachange,
	    fxp_mediastatus);
	mii_phy_probe(self, &sc->sc_mii, 0xffffffff);
	/* If no phy found, just use auto mode */
	if (LIST_FIRST(&sc->sc_mii.mii_phys) == NULL) {
		ifmedia_add(&sc->sc_mii.mii_media, IFM_ETHER|IFM_MANUAL,
		    0, NULL);
		printf(FXP_FORMAT ": no phy found, using manual mode\n",
		    FXP_ARGS(sc));
	}

	if (ifmedia_match(&sc->sc_mii.mii_media, IFM_ETHER|IFM_MANUAL, 0))
		ifmedia_set(&sc->sc_mii.mii_media, IFM_ETHER|IFM_MANUAL);
	else if (ifmedia_match(&sc->sc_mii.mii_media, IFM_ETHER|IFM_AUTO, 0))
		ifmedia_set(&sc->sc_mii.mii_media, IFM_ETHER|IFM_AUTO);
	else
		ifmedia_set(&sc->sc_mii.mii_media, IFM_ETHER|IFM_10_T);

	/*
	 * Attach the interface.
	 */
	if_attach(ifp);
	/*
	 * Let the system queue as many packets as we have available
	 * TX descriptors.
	 */
	ifp->if_snd.ifq_maxlen = FXP_NTXCB - 1;
#ifdef __NetBSD__
	ether_ifattach(ifp, enaddr);
#else
	ether_ifattach(ifp);
#endif
#if NBPFILTER > 0
#ifdef __OpenBSD__
	bpfattach(&sc->arpcom.ac_if.if_bpf, ifp, DLT_EN10MB,
	    sizeof(struct ether_header));
#else
	bpfattach(&sc->sc_ethercom.ec_if.if_bpf, ifp, DLT_EN10MB,
	    sizeof(struct ether_header));
#endif
#endif

	/*
	 * Add shutdown hook so that DMA is disabled prior to reboot. Not
	 * doing do could allow DMA to corrupt kernel memory during the
	 * reboot before the driver initializes.
	 */
	shutdownhook_establish(fxp_shutdown, sc);

#ifndef PMON
	/*
	 * Add suspend hook, for similiar reasons..
	 */
	powerhook_establish(fxp_power, sc);
#endif
}

/*
 * Device shutdown routine. Called at system shutdown after sync. The
 * main purpose of this routine is to shut off receiver DMA so that
 * kernel memory doesn't get clobbered during warmboot.
 */
static void
fxp_shutdown(sc)
	void *sc;
{
	fxp_stop((struct fxp_softc *) sc, 0);
}

#ifndef PMON
/*
 * Power handler routine. Called when the system is transitioning
 * into/out of power save modes.  As with fxp_shutdown, the main
 * purpose of this routine is to shut off receiver DMA so it doesn't
 * clobber kernel memory at the wrong time.
 */
void
fxp_power(why, arg)
	int why;
	void *arg;
{
	struct fxp_softc *sc = arg;
	struct ifnet *ifp;
	int s;

	s = splnet();
	if (why != PWR_RESUME)
		fxp_stop(sc, 0);
	else {
		ifp = &sc->arpcom.ac_if;
		if (ifp->if_flags & IFF_UP)
			fxp_init(sc);
	}
	splx(s);
}
#endif

static int
fxp_ether_ioctl(ifp, cmd, data)
	struct ifnet *ifp;
	FXP_IOCTLCMD_TYPE cmd;
	caddr_t data;
{
	struct ifaddr *ifa = (struct ifaddr *) data;
	struct fxp_softc *sc = ifp->if_softc;
	int error = 0;

	switch (cmd) {
#ifdef PMON
	case SIOCPOLL:
		break;
#endif
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;

		switch (ifa->ifa_addr->sa_family) {
#ifdef INET
		case AF_INET:
			error = fxp_init(sc);
			if(error == -1)
				return(error);

#ifdef __OpenBSD__
			arp_ifinit(&sc->arpcom, ifa);
#else
			arp_ifinit(ifp, ifa);
#endif
			break;
#endif
#ifdef NS
		case AF_NS:
		    {
			 register struct ns_addr *ina = &IA_SNS(ifa)->sns_addr;

			 if (ns_nullhost(*ina))
				ina->x_host = *(union ns_host *)
				    LLADDR(ifp->if_sadl);
			 else
				bcopy(ina->x_host.c_host, LLADDR(ifp->if_sadl),
				    ifp->if_addrlen);
			 /* Set new address. */
			 fxp_init(sc);
			 break;
		    }
#endif
		default:
			fxp_init(sc);
			break;
		}
		break;

	default:
		return (EINVAL);
	}

	return (error);
}

/*************************************************************
 * End of operating system-specific autoconfiguration glue
 *************************************************************/

/*
 * Do generic parts of attach.
 */
static int
fxp_attach_common(sc, enaddr)
	struct fxp_softc *sc;
	u_int8_t *enaddr;
{
	u_int16_t data;
	int i;

	/*
	 * Reset to a stable state.
	 */
	CSR_WRITE_4(sc, FXP_CSR_PORT, FXP_PORT_SELECTIVE_RESET);
	DELAY(100);
	sc->cbl_base = malloc(sizeof(struct fxp_cb_tx) * FXP_NTXCB,
	    M_DEVBUF, M_NOWAIT);
	if (sc->cbl_base == NULL)
		goto fail;

#if defined(__mips__)
	/*
	 *  Due to MIPS processor cache behaviour we change to uncached
	 *  addresses to access control structure areas.
	 */
	pci_sync_cache(sc->sc_pc, (vm_offset_t)sc->cbl_base,
				sizeof(struct fxp_cb_tx) * FXP_NTXCB, SYNC_W);
	sc->cbl_base = (void *)PHYS_TO_UNCACHED(vtophys(sc->cbl_base));
#endif /*__mips__*/
	sc->fxp_stats = malloc(sizeof(struct fxp_stats), M_DEVBUF, M_NOWAIT);
	if (sc->fxp_stats == NULL)
		goto fail;
	bzero(sc->fxp_stats, sizeof(struct fxp_stats));
#if defined(__mips__)
	pci_sync_cache(sc->sc_pc, (vm_offset_t)sc->fxp_stats,
				sizeof(struct fxp_stats), SYNC_W);
	sc->fxp_stats = (void *)PHYS_TO_UNCACHED(vtophys(sc->fxp_stats));
#endif /*__mips__*/
	
	sc->mcsp = malloc(sizeof(struct fxp_cb_mcs), M_DEVBUF, M_NOWAIT);
	if (sc->mcsp == NULL)
		goto fail;
#if defined(__mips__)
	pci_sync_cache(sc->sc_pc, (vm_offset_t)sc->mcsp,
				sizeof(struct fxp_cb_mcs), SYNC_W);
	sc->mcsp = (void *)PHYS_TO_UNCACHED(vtophys(sc->mcsp));
#endif /*__mips__*/

	/*
	 * Pre-allocate our receive buffers.
	 */
	for (i = 0; i < FXP_NRFABUFS; i++) {
		if (fxp_add_rfabuf(sc, NULL) != 0) {
			goto fail;
		}
	}

	/*
	 * Find out how large of an SEEPROM we have.
	 */
	fxp_autosize_eeprom(sc);
	/*
	 * Get info about the primary PHY
	 */
#if   defined(GODSONEV1)
	data=0x4701;
#else	
	fxp_read_eeprom(sc, (u_int16_t *)&data, 6, 1);
#endif
	sc->phy_primary_addr = data & 0xff;
	sc->phy_primary_device = (data >> 8) & 0x3f;
	sc->phy_10Mbps_only = data >> 15;

	/*
	 * Read MAC address.
	 */
#if defined(GODSONEV1)
	enaddr[0]=0x12;
	enaddr[1]=0x34;
	enaddr[2]=0x56;
	enaddr[3]=0x78;
	enaddr[4]=0x9a;
	enaddr[5]=0xbc;
#else
	fxp_read_eeprom(sc, (u_int16_t *)enaddr, 0, 3);
#endif
	return (0);

 fail:
	printf(FXP_FORMAT ": Failed to malloc memory\n", FXP_ARGS(sc));
	if (sc->cbl_base)
		free(sc->cbl_base, M_DEVBUF);
	if (sc->fxp_stats)
		free(sc->fxp_stats, M_DEVBUF);
	if (sc->mcsp)
		free(sc->mcsp, M_DEVBUF);
	/* frees entire chain */
	if (sc->rfa_headm)
		m_freem(sc->rfa_headm);

	return (ENOMEM);
}

/*
 * From NetBSD:
 *
 * Figure out EEPROM size.
 *
 * 559's can have either 64-word or 256-word EEPROMs, the 558
 * datasheet only talks about 64-word EEPROMs, and the 557 datasheet
 * talks about the existance of 16 to 256 word EEPROMs.
 *
 * The only known sizes are 64 and 256, where the 256 version is used
 * by CardBus cards to store CIS information.
 *
 * The address is shifted in msb-to-lsb, and after the last
 * address-bit the EEPROM is supposed to output a `dummy zero' bit,
 * after which follows the actual data. We try to detect this zero, by
 * probing the data-out bit in the EEPROM control register just after
 * having shifted in a bit. If the bit is zero, we assume we've
 * shifted enough address bits. The data-out should be tri-state,
 * before this, which should translate to a logical one.
 *
 * Other ways to do this would be to try to read a register with known
 * contents with a varying number of address bits, but no such
 * register seem to be available. The high bits of register 10 are 01
 * on the 558 and 559, but apparently not on the 557.
 * 
 * The Linux driver computes a checksum on the EEPROM data, but the
 * value of this checksum is not very well documented.
 */
static void
fxp_autosize_eeprom(sc)
	struct fxp_softc *sc;
{
	u_int16_t reg;
	int x;

	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EECS);
	/*
	 * Shift in read opcode.
	 */
	for (x = 3; x > 0; x--) {
		if (FXP_EEPROM_OPC_READ & (1 << (x - 1))) {
			reg = FXP_EEPROM_EECS | FXP_EEPROM_EEDI;
		} else {
			reg = FXP_EEPROM_EECS;
		}
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
		    reg | FXP_EEPROM_EESK);
		DELAY(1);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		DELAY(1);
	}
	/*
	 * Shift in address.
	 * Wait for the dummy zero following a correct address shift.
	 */
	for (x = 1; x <= 8; x++) {
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EECS);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
			FXP_EEPROM_EECS | FXP_EEPROM_EESK);
		DELAY(1);
		if ((CSR_READ_2(sc, FXP_CSR_EEPROMCONTROL) & FXP_EEPROM_EEDO) == 0)
			break;
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EECS);
		DELAY(1);
	}
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
	DELAY(1);
	sc->eeprom_size = x;
}
/*
 * Read from the serial EEPROM. Basically, you manually shift in
 * the read opcode (one bit at a time) and then shift in the address,
 * and then you shift out the data (all of this one bit at a time).
 * The word size is 16 bits, so you have to provide the address for
 * every 16 bits of data.
 */
void
fxp_read_eeprom(sc, data, offset, words)
	struct fxp_softc *sc;
	u_short *data;
	int offset;
	int words;
{
	u_int16_t reg;
	int i, x;

	for (i = 0; i < words; i++) {
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EECS);
		/*
		 * Shift in read opcode.
		 */
		for (x = 3; x > 0; x--) {
			if (FXP_EEPROM_OPC_READ & (1 << (x - 1))) {
				reg = FXP_EEPROM_EECS | FXP_EEPROM_EEDI;
			} else {
				reg = FXP_EEPROM_EECS;
			}
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
			    reg | FXP_EEPROM_EESK);
			DELAY(1);
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
			DELAY(1);
		}
		/*
		 * Shift in address.
		 */
		for (x = sc->eeprom_size; x > 0; x--) {
			if ((i + offset) & (1 << (x - 1))) {
				reg = FXP_EEPROM_EECS | FXP_EEPROM_EEDI;
			} else {
				reg = FXP_EEPROM_EECS;
			}
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
			    reg | FXP_EEPROM_EESK);
			DELAY(1);
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
			DELAY(1);
		}
		reg = FXP_EEPROM_EECS;
		data[i] = 0;
		/*
		 * Shift out data.
		 */
		for (x = 16; x > 0; x--) {
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
			    reg | FXP_EEPROM_EESK);
			DELAY(1);
			if (CSR_READ_2(sc, FXP_CSR_EEPROMCONTROL) &
			    FXP_EEPROM_EEDO)
				data[i] |= (1 << (x - 1));
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
			DELAY(1);
		}
#if BYTE_ORDER == BIG_ENDIAN
		data[i] = swap16(data[i]);
#endif
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
		DELAY(1);
	}
}

#if 0
/*
 * Write to the serial EEPROM. This is not intended to be used
 * uncautiosly(?). The main intention is to privide a means to
 * initiate an uninitialized EEPROM during production test.
 */
void
fxp_write_eeprom(sc, data, offset, words)
	struct fxp_softc *sc;
	u_short *data;
	int offset;
	int words;
{
	u_int16_t reg;
	int i, x;
	int d;

	/*
	 * Enable writing.
	 */
	d = (FXP_EEPROM_OPC_WRITENB << 4);
	x = 0x100;
	while (x != 0) {
		if (d & x) {
			reg = FXP_EEPROM_EECS | FXP_EEPROM_EEDI;
		} else {
			reg = FXP_EEPROM_EECS;
		}
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
		    reg | FXP_EEPROM_EESK);
		DELAY(1);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		DELAY(1);
		x >>= 1;
	}
/* XXXX Need data sheet to verify if raise CS is enough! (pefo) */
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
	DELAY(1);
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EESK);
	DELAY(1);
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
	DELAY(1);

	/*
	 * Now write the data words.
	 */
	for (i = 0; i < words; i++) {
#if BYTE_ORDER == BIG_ENDIAN
                data[i] = swap16(data[i]);
#endif
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EECS);
		/*
		 * Shift in write command, address and data.
		 */
		d = (FXP_EEPROM_OPC_WRITE << 6) | ((i + offset) & 0x3f);
		d = d << 16 | data[i];
		x = 0x1000000;
		while (x != 0) {
			if (d & x) {
				reg = FXP_EEPROM_EECS | FXP_EEPROM_EEDI;
			} else {
				reg = FXP_EEPROM_EECS;
			}
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
			    reg | FXP_EEPROM_EESK);
			DELAY(1);
			CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
			DELAY(1);
			x >>= 1;
		}
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
		DELAY(1);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EESK);
		DELAY(1);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
		DELAY(1);

		DELAY(200000);  /* Let write settle */
	}

	/*
	 * Disable writing.
	 */
	d = (FXP_EEPROM_OPC_WRITDIS << 4);
	x = 0x100;
	while (x != 0) {
		if (d & x) {
			reg = FXP_EEPROM_EECS | FXP_EEPROM_EEDI;
		} else {
			reg = FXP_EEPROM_EECS;
		}
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL,
		    reg | FXP_EEPROM_EESK);
		DELAY(1);
		CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, reg);
		DELAY(1);
		x >>= 1;
	}
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
	DELAY(1);
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, FXP_EEPROM_EESK);
	DELAY(1);
	CSR_WRITE_2(sc, FXP_CSR_EEPROMCONTROL, 0);
	DELAY(1);
}
#endif

/*
 * Start packet transmission on the interface.
 */
static void
fxp_start(ifp)
	struct ifnet *ifp;
{
	struct fxp_softc *sc = ifp->if_softc;
	struct fxp_cb_tx *txp;

#ifdef USE_FXP_MCAST
	/*
	 * See if we need to suspend xmit until the multicast filter
	 * has been reprogrammed (which can only be done at the head
	 * of the command chain).
	 */
	if (sc->need_mcsetup)
		return;
#endif

	txp = NULL;

	/*
	 * We're finished if there is nothing more to add to the list or if
	 * we're all filled up with buffers to transmit.
	 * NOTE: One TxCB is reserved to guarantee that fxp_mc_setup() can add
	 *       a NOP command when needed.
	 */
	while (ifp->if_snd.ifq_head != NULL && sc->tx_queued < FXP_NTXCB - 1) {
		struct mbuf *m, *mb_head;
		int segment;

		/*
		 * Grab a packet to transmit.
		 */
		IF_DEQUEUE(&ifp->if_snd, mb_head);

		/*
		 * Get pointer to next available tx desc.
		 */
		txp = sc->cbl_last->next;

		/*
		 * Go through each of the mbufs in the chain and initialize
		 * the transmit buffer descriptors with the physical address
		 * and size of the mbuf.
		 */
tbdinit:
		for (m = mb_head, segment = 0; m != NULL; m = m->m_next) {
			if (m->m_len != 0) {
				if (segment == FXP_NTXSEG)
					break;
				txp->tbd[segment].tb_addr =
				    htole32(vtophys(mtod(m, vm_offset_t)));
				txp->tbd[segment].tb_size = htole32(m->m_len);
#if defined(__mips__)
				pci_sync_cache(sc->sc_pc, mtod(m, vm_offset_t),
						m->m_len, SYNC_W);
#endif
				segment++;
			}
		}
		if (m != NULL) {
			struct mbuf *mn;

			/*
			 * We ran out of segments. We have to recopy this mbuf
			 * chain first. Bail out if we can't get the new buffers.
			 */
			MGETHDR(mn, M_DONTWAIT, MT_DATA);
			if (mn == NULL) {
				m_freem(mb_head);
				break;
			}
			if (mb_head->m_pkthdr.len > MHLEN) {
				MCLGET(mn, M_DONTWAIT);
				if ((mn->m_flags & M_EXT) == 0) {
					m_freem(mn);
					m_freem(mb_head);
					break;
				}
			}
			m_copydata(mb_head, 0, mb_head->m_pkthdr.len,
			    mtod(mn, caddr_t));
			mn->m_pkthdr.len = mn->m_len = mb_head->m_pkthdr.len;
			m_freem(mb_head);
			mb_head = mn;
			goto tbdinit;
		}

		txp->tbd_number = segment;
		txp->mb_head = mb_head;
		txp->cb_status = htole16(0);
		if (sc->tx_queued != FXP_CXINT_THRESH - 1) {
			txp->cb_command =
			    htole16(FXP_CB_COMMAND_XMIT | FXP_CB_COMMAND_SF | FXP_CB_COMMAND_S);
		} else {
			txp->cb_command =
			    htole16(FXP_CB_COMMAND_XMIT | FXP_CB_COMMAND_SF | FXP_CB_COMMAND_S | FXP_CB_COMMAND_I);
			/*
			 * Set a 5 second timer just in case we don't hear
			 * from the card again.
			 */
			ifp->if_timer = 5;
		}
		txp->tx_threshold = tx_threshold;
	
		/*
		 * Advance the end of list forward.
		 */
		sc->cbl_last->cb_command &= htole16(~FXP_CB_COMMAND_S);
		sc->cbl_last = txp;

		/*
		 * Advance the beginning of the list forward if there are
		 * no other packets queued (when nothing is queued, cbl_first
		 * sits on the last TxCB that was sent out).
		 */
		if (sc->tx_queued == 0)
			sc->cbl_first = txp;

		sc->tx_queued++;

#if NBPFILTER > 0
		/*
		 * Pass packet to bpf if there is a listener.
		 */
		if (ifp->if_bpf)
			bpf_mtap(FXP_BPFTAP_ARG(ifp), mb_head);
#endif
	}

	/*
	 * We're finished. If we added to the list, issue a RESUME to get DMA
	 * going again if suspended.
	 */
	if (txp != NULL) {
		fxp_scb_wait(sc);
		CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_RESUME);
	}
}

/*
 * Process interface interrupts.
 */
FXP_INTR_TYPE
fxp_intr(arg)
	void *arg;
{
	struct fxp_softc *sc = arg;
	struct ifnet *ifp = &sc->sc_if;
	u_int8_t statack;
#if defined(__NetBSD__) || defined(__OpenBSD__)
	int claimed = 0;

	/*
	 * If the interface isn't running, don't try to
	 * service the interrupt.. just ack it and bail.
	 */
	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		statack = CSR_READ_1(sc, FXP_CSR_SCB_STATACK);
		if (statack) {
			claimed = 1;
			CSR_WRITE_1(sc, FXP_CSR_SCB_STATACK, statack);
		}
		return claimed;
	}
#endif

	while ((statack = CSR_READ_1(sc, FXP_CSR_SCB_STATACK)) != 0) {
#if defined(__NetBSD__) || defined(__OpenBSD__)
		claimed = 1;
#endif
		/*
		 * First ACK all the interrupts in this pass.
		 */
		CSR_WRITE_1(sc, FXP_CSR_SCB_STATACK, statack);

		/*
		 * Free any finished transmit mbuf chains.
		 */
		if (statack & FXP_SCB_STATACK_CXTNO||FXP_SCB_STATACK_CNA) {
			struct fxp_cb_tx *txp;

			for (txp = sc->cbl_first; sc->tx_queued &&
			    (txp->cb_status & htole16(FXP_CB_STATUS_C)) != 0;
			    txp = txp->next) {
				if (txp->mb_head != NULL) {
					m_freem(txp->mb_head);
					txp->mb_head = NULL;
				}
				sc->tx_queued--;
			}
			sc->cbl_first = txp;
			ifp->if_timer = 0;
#ifdef USE_FXP_MCAST
			if (sc->tx_queued == 0) {
				if (sc->need_mcsetup)
					fxp_mc_setup(sc);
			}
#endif
			/*
			 * Try to start more packets transmitting.
			 */
			if (ifp->if_snd.ifq_head != NULL)
				fxp_start(ifp);
		}
		//printf("transmit buf freed\n");
		/*
		 * Process receiver interrupts. If a no-resource (RNR)
		 * condition exists, get whatever packets we can and
		 * re-start the receiver.
		 */
		if (statack & (FXP_SCB_STATACK_FR | FXP_SCB_STATACK_RNR)) {
			struct mbuf *m;
			u_int8_t *rfap;
rcvloop:
			//printf("recving a packet\n");
			m = sc->rfa_headm;
			rfap = m->m_ext.ext_buf + RFA_ALIGNMENT_FUDGE;

#if defined(__mips__)
			/*
			 * Read uncached so we don't create any funny
			 * cache coherency side effects.
			 */
			//printf("rfap=%x\n",rfap);
			if (*(u_int16_t *)(PHYS_TO_UNCACHED(vtophys(rfap)) +
			    offsetof(struct fxp_rfa, rfa_status)) &
			    htole16(FXP_RFA_STATUS_C)) {
#else 
			if (*(u_int16_t *)(rfap +
			    offsetof(struct fxp_rfa, rfa_status)) &
			    htole16(FXP_RFA_STATUS_C)) {
#endif /* __mips__ */
			        //printf("packet ready for %x\n",rfap);
				/*
				 * Remove first packet from the chain.
				 */
				sc->rfa_headm = m->m_next;
				m->m_next = NULL;

				/*
				 * Add a new buffer to the receive chain.
				 * If this fails, the old buffer is recycled
				 * instead.
				 */
				if (fxp_add_rfabuf(sc, m) == 0) {
					struct ether_header *eh;
					u_int16_t total_len;

					total_len = (htole16(*(u_int16_t *)(rfap +
					    offsetof(struct fxp_rfa,
					    actual_size)))) &
					    (MCLBYTES - 1);
					if (total_len <
					    sizeof(struct ether_header)) {
						m_freem(m);
						goto rcvloop;
					}
					m->m_pkthdr.rcvif = ifp;
					m->m_pkthdr.len = m->m_len =
					    total_len -
					    sizeof(struct ether_header);
#ifdef BADPCIBRIDGE
					m->m_data -= 2;
					bcopy(m->m_data + 2, m->m_data, total_len);
#endif

#ifdef GODSONEV1
					{
						int i;
					        if ((*(unsigned char* volatile)PHYS_TO_UNCACHED(vtophys(m->m_data+0)))!=0xff) {
							for(i=0;i<total_len;i+=32){
								m->m_data[i]=*(unsigned char*)PHYS_TO_UNCACHED(vtophys(m->m_data+i));
#ifdef BEBUG_DMA_FLUSH_CACHE
								printf("%x: %2x\n", (unsigned char*)PHYS_TO_UNCACHED(vtophys(m->m_data+i)),*(unsigned char*)PHYS_TO_UNCACHED(vtophys(m->m_data+i)));
								printf("%x: %2x\t%x,(%2x)\n", (unsigned int)&m->m_data[i],(unsigned int)(unsigned char)m->m_data[80], (unsigned char*)PHYS_TO_UNCACHED(vtophys(m->m_data+i)),*(unsigned char*)PHYS_TO_UNCACHED(vtophys(m->m_data+i)));
#endif
							}
						}
						m->m_data[total_len-1]=*(unsigned char*)PHYS_TO_UNCACHED(vtophys(m->m_data+total_len-1));
							
					}

#endif
					eh = mtod(m, struct ether_header *);
#if NBPFILTER > 0
					if (ifp->if_bpf)
						bpf_tap(FXP_BPFTAP_ARG(ifp),
						    mtod(m, caddr_t),
						    total_len); 
#endif /* NBPFILTER > 0 */
					m->m_data +=
					    sizeof(struct ether_header);
					//printf("ether input,size=%d\n",total_len);
					ether_input(ifp, eh, m);
				}
				else {
#ifndef Pocono
					int i;
 					for (i=0;i<100;i++)
					printf("HELP! fxp recycling rxbuf!\n");
#endif
				}
				goto rcvloop;
			}
			if (statack & FXP_SCB_STATACK_RNR) {
				fxp_scb_wait(sc);
/* XXXX MIPS: Flush not req. Already done when put on rfa_headm */
				CSR_WRITE_4(sc, FXP_CSR_SCB_GENERAL,
				    vtophys(sc->rfa_headm->m_ext.ext_buf) +
					RFA_ALIGNMENT_FUDGE);
				CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND,
				    FXP_SCB_COMMAND_RU_START);
			}
		}
	}
#if defined(__NetBSD__) || defined(__OpenBSD__)
	return (claimed);
#endif
}

/*
 * Update packet in/out/collision statistics. The i82557 doesn't
 * allow you to access these counters without doing a fairly
 * expensive DMA to get _all_ of the statistics it maintains, so
 * we do this operation here only once per second. The statistics
 * counters in the kernel are updated from the previous dump-stats
 * DMA and then a new dump-stats DMA is started. The on-chip
 * counters are zeroed when the DMA completes. If we can't start
 * the DMA immediately, we don't wait - we just prepare to read
 * them again next time.
 */
void
fxp_stats_update(arg)
	void *arg;
{
#ifdef USE_FXP_STATS
	struct fxp_softc *sc = arg;
	struct ifnet *ifp = &sc->sc_if;
	struct fxp_stats *sp = sc->fxp_stats;
	int s;

	ifp->if_opackets += sp->tx_good;
	ifp->if_collisions += sp->tx_total_collisions;
	if (sp->rx_good) {
		ifp->if_ipackets += sp->rx_good;
		sc->rx_idle_secs = 0;
	} else {
		sc->rx_idle_secs++;
	}
	ifp->if_ierrors +=
	    sp->rx_crc_errors +
	    sp->rx_alignment_errors +
	    sp->rx_rnr_errors +
	    sp->rx_overrun_errors;
	/*
	 * If any transmit underruns occured, bump up the transmit
	 * threshold by another 512 bytes (64 * 8).
	 */
	if (sp->tx_underruns) {
		ifp->if_oerrors += sp->tx_underruns;
		if (tx_threshold < 192)
			tx_threshold += 64;
	}
	s = splimp();
	/*
	 * If we haven't received any packets in FXP_MAC_RX_IDLE seconds,
	 * then assume the receiver has locked up and attempt to clear
	 * the condition by reprogramming the multicast filter. This is
	 * a work-around for a bug in the 82557 where the receiver locks
	 * up if it gets certain types of garbage in the syncronization
	 * bits prior to the packet header. This bug is supposed to only
	 * occur in 10Mbps mode, but has been seen to occur in 100Mbps
	 * mode as well (perhaps due to a 10/100 speed transition).
	 */
	if (sc->rx_idle_secs > FXP_MAX_RX_IDLE) {
		sc->rx_idle_secs = 0;
		fxp_mc_setup(sc);
	}
	/*
	 * If there is no pending command, start another stats
	 * dump. Otherwise punt for now.
	 */
	if (CSR_READ_1(sc, FXP_CSR_SCB_COMMAND) == 0) {
		/*
		 * Start another stats dump.
		 */
		CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND,
		    FXP_SCB_COMMAND_CU_DUMPRESET);
	} else {
		/*
		 * A previous command is still waiting to be accepted.
		 * Just zero our copy of the stats and wait for the
		 * next timer event to update them.
		 */
		sp->tx_good = 0;
		sp->tx_underruns = 0;
		sp->tx_total_collisions = 0;

		sp->rx_good = 0;
		sp->rx_crc_errors = 0;
		sp->rx_alignment_errors = 0;
		sp->rx_rnr_errors = 0;
		sp->rx_overrun_errors = 0;
	}

	/* Tick the MII clock. */
	mii_tick(&sc->sc_mii);

	splx(s);
	/*
	 * Schedule another timeout one second from now.
	 */
	timeout(fxp_stats_update, sc, hz);
#endif
}

/*
 * Stop the interface. Cancels the statistics updater and resets
 * the interface.
 */
void
fxp_stop(sc, drain)
	struct fxp_softc *sc;
	int drain;
{
	struct ifnet *ifp = &sc->sc_if;
	struct fxp_cb_tx *txp;
	int i;

	/*
	 * Turn down interface (done early to avoid bad interactions
	 * between panics, shutdown hooks, and the watchdog timer)
	 */
	ifp->if_timer = 0;
	ifp->if_flags &= ~(IFF_RUNNING | IFF_OACTIVE);

#ifdef USE_FXP_STATS
	/*
	 * Cancel stats updater.
	 */
	untimeout(fxp_stats_update, sc);
#endif

	/*
	 * Issue software reset
	 */
	CSR_WRITE_4(sc, FXP_CSR_PORT, FXP_PORT_SELECTIVE_RESET);
	DELAY(10);

	/*
	 * Release any xmit buffers.
	 */
	for (txp = sc->cbl_first; txp != NULL && txp->mb_head != NULL;
	    txp = txp->next) {
		m_freem(txp->mb_head);
		txp->mb_head = NULL;
	}
	sc->tx_queued = 0;

	if (drain) {
		/*
		 * Free all the receive buffers then reallocate/reinitialize
		 */
		if (sc->rfa_headm != NULL)
			m_freem(sc->rfa_headm);
		sc->rfa_headm = NULL;
		sc->rfa_tailm = NULL;
		for (i = 0; i < FXP_NRFABUFS; i++) {
			if (fxp_add_rfabuf(sc, NULL) != 0) {
				/*
				 * This "can't happen" - we're at splimp()
				 * and we just freed all the buffers we need
				 * above.
				 */
				panic("fxp_stop: no buffers!");
			}
		}
	}

}

/*
 * Watchdog/transmission transmit timeout handler. Called when a
 * transmission is started on the interface, but no interrupt is
 * received before the timeout. This usually indicates that the
 * card has wedged for some reason.
 */
void
fxp_watchdog(ifp)
	struct ifnet *ifp;
{
	struct fxp_softc *sc = ifp->if_softc;
	int s;
	
	log(LOG_ERR, FXP_FORMAT ": device timeout\n", FXP_ARGS(sc));
	ifp->if_oerrors++;

	if (fxp_init(sc) != 0) {
		ifp->if_timer = FXP_DELAY_BEFORE_REINIT;
		return;
	}

	/* Empty transmit queue */
	s = splimp();      /* Protect Q-handling in fxp_start */
	if (ifp->if_snd.ifq_head != NULL)
	{
	     fxp_start(ifp);
	}
	splx(s);
}

int
fxp_init(xsc)
	void *xsc;
{
	struct fxp_softc *sc = xsc;
	struct ifnet *ifp = &sc->sc_if;
	struct fxp_cb_config *cbp;
	struct fxp_cb_ias *cb_ias;
	struct fxp_cb_tx *txp;
	int i, s, prm;

	s = splimp();
	/*
	 * Cancel any pending I/O
	 */
	fxp_stop(sc, 0);

	prm = (ifp->if_flags & IFF_PROMISC) ? 1 : 0;

	/*
	 * Initialize base of CBL and RFA memory. Loading with zero
	 * sets it up for regular linear addressing.
	 */
	for(i=0;i<10000;i++) {
	CSR_WRITE_4(sc, FXP_CSR_SCB_GENERAL, 0);
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_BASE);

	fxp_scb_wait(sc);
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_RU_BASE);
	}

	/*
	 * Initialize base of dump-stats buffer.
	 */
	fxp_scb_wait(sc);
	CSR_WRITE_4(sc, FXP_CSR_SCB_GENERAL, vtophys(sc->fxp_stats));
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_DUMP_ADR);

	/*
	 * We temporarily use memory that contains the TxCB list to
	 * construct the config CB. The TxCB list memory is rebuilt
	 * later.
	 */
	cbp = (struct fxp_cb_config *) sc->cbl_base;

	/*
	 * This bcopy is kind of disgusting, but there are a bunch of must be
	 * zero and must be one bits in this structure and this is the easiest
	 * way to initialize them all to proper values.
	 */
	bcopy(fxp_cb_config_template, (void *)&cbp->cb_status,
		sizeof(fxp_cb_config_template));

	cbp->cb_command = htole16(FXP_CB_COMMAND_CONFIG | FXP_CB_COMMAND_EL);

	/*
	 * Start the config command/DMA.
	 */
	fxp_scb_wait(sc);
	CSR_WRITE_4(sc, FXP_CSR_SCB_GENERAL, vtophys(&cbp->cb_status));
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_START);
	/* ...and wait for it to complete. */
	for (i = 0; !(cbp->cb_status & htole16(FXP_CB_STATUS_C)) && i < FXP_MAX_STATUS_READS; ++i)
		DELAY(2);
	
	if (i == FXP_MAX_STATUS_READS) {
		printf("bus congestion, restarting");
		return -1;
	}

	/*
	 * Now initialize the station address. Temporarily use the TxCB
	 * memory area like we did above for the config CB.
	 */
	cb_ias = (struct fxp_cb_ias *) sc->cbl_base;
	cb_ias->cb_status = htole16(0);
	cb_ias->cb_command = htole16(FXP_CB_COMMAND_IAS | FXP_CB_COMMAND_EL);
	cb_ias->link_addr = htole32(-1);
	bcopy(sc->arpcom.ac_enaddr, (void *)cb_ias->macaddr,
	    sizeof(sc->arpcom.ac_enaddr));

	/*
	 * Start the IAS (Individual Address Setup) command/DMA.
	 */
	fxp_scb_wait(sc);
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_START);
	/* ...and wait for it to complete. */
	for (i = 0; !(cb_ias->cb_status & htole16(FXP_CB_STATUS_C)) && i < FXP_MAX_STATUS_READS; ++i)
		DELAY(2);

	if (i == FXP_MAX_STATUS_READS) {
		printf("bus congestion, restarting");
		return -1;
	}


	/*
	 * Initialize transmit control block (TxCB) list.
	 */

	txp = sc->cbl_base;
	bzero(txp, sizeof(struct fxp_cb_tx) * FXP_NTXCB);
	for (i = 0; i < FXP_NTXCB; i++) {
		txp[i].cb_status = htole16(FXP_CB_STATUS_C | FXP_CB_STATUS_OK);
		txp[i].cb_command = htole16(FXP_CB_COMMAND_NOP);
		txp[i].link_addr = htole32(vtophys(&txp[(i + 1) & FXP_TXCB_MASK].cb_status));
		txp[i].tbd_array_addr = htole32(vtophys(&txp[i].tbd[0]));
		txp[i].next = &txp[(i + 1) & FXP_TXCB_MASK];
	}
	/*
	 * Set the suspend flag on the first TxCB and start the control
	 * unit. It will execute the NOP and then suspend.
	 */
	txp->cb_command = htole16(FXP_CB_COMMAND_NOP | FXP_CB_COMMAND_S);
	sc->cbl_first = sc->cbl_last = txp;
	sc->tx_queued = 1;

	fxp_scb_wait(sc);
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_START);

	/*
	 * Initialize receiver buffer area - RFA.
	 */
	fxp_scb_wait(sc);
/* XXXX MIPS: Flush not req. Already done when put on rfa_headm */
	CSR_WRITE_4(sc, FXP_CSR_SCB_GENERAL,
	    vtophys(sc->rfa_headm->m_ext.ext_buf) + RFA_ALIGNMENT_FUDGE);
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_RU_START);

	/*
	 * Set current media.
	 */
	mii_mediachg(&sc->sc_mii);

	ifp->if_flags |= IFF_RUNNING;
	ifp->if_flags &= ~IFF_OACTIVE;
	splx(s);

#ifdef USE_FXP_STATS
	/*
	 * Start stats updater.
	 */
	timeout(fxp_stats_update, sc, hz);
#endif
	return(0);
}

/*
 * Change media according to request.
 */
int
fxp_mediachange(ifp)
	struct ifnet *ifp;
{

	if (ifp->if_flags & IFF_UP)
		fxp_init(ifp->if_softc);
	return (0);
}

/*
 * Notify the world which media we're using.
 */
void
fxp_mediastatus(ifp, ifmr)
	struct ifnet *ifp;
	struct ifmediareq *ifmr;
{
	struct fxp_softc *sc = ifp->if_softc;

	mii_pollstat(&sc->sc_mii);
	ifmr->ifm_status = sc->sc_mii.mii_media_status;
	ifmr->ifm_active = sc->sc_mii.mii_media_active;
}

/*
 * Add a buffer to the end of the RFA buffer list.
 * Return 0 if successful, 1 for failure. A failure results in
 * adding the 'oldm' (if non-NULL) on to the end of the list -
 * tossing out its old contents and recycling it.
 * The RFA struct is stuck at the beginning of mbuf cluster and the
 * data pointer is fixed up to point just past it.
 */
int
fxp_add_rfabuf(sc, oldm)
	struct fxp_softc *sc;
	struct mbuf *oldm;
{
	u_int32_t v;
	struct mbuf *m;
	u_int8_t *rfap;

	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m != NULL) {
		MCLGET(m, M_DONTWAIT);
		if ((m->m_flags & M_EXT) == 0) {
			m_freem(m);
			if (oldm == NULL)
				return 1;
			m = oldm;
			m->m_data = m->m_ext.ext_buf;
		}
	} else {
		//printf("m=%x,oldm=%x\n",m,oldm);
		if (oldm == NULL)
			return 1;
		m = oldm;
		m->m_data = m->m_ext.ext_buf;
	}

	/*
	 * Move the data pointer up so that the incoming data packet
	 * will be 32-bit aligned.
	 * Get a pointer to the base of the mbuf cluster and move
	 * data start past it.
	 */

#if defined(__mips__)
	/*
	 * Sync the buffer so we can access it uncached.
	 */
	if (m->m_ext.ext_buf!=NULL) {
		pci_sync_cache(sc->sc_pc, (vm_offset_t)m->m_ext.ext_buf,
				MCLBYTES, SYNC_R);
	}
	m->m_data += RFA_ALIGNMENT_FUDGE;
	rfap = (u_int8_t *)PHYS_TO_UNCACHED(vtophys(m->m_data));
	//printf("rfap=%x\n",rfap);
#else
	m->m_data += RFA_ALIGNMENT_FUDGE;
	rfap = m->m_data;
#endif
	m->m_data += sizeof(struct fxp_rfa);
	*(u_int16_t *)(rfap + offsetof(struct fxp_rfa, size)) =
	    htole16(MCLBYTES - sizeof(struct fxp_rfa) - RFA_ALIGNMENT_FUDGE);

	/*
	 * Initialize the rest of the RFA.  Note that since the RFA
	 * is misaligned, we cannot store values directly.  Instead,
	 * we use an optimized, inline copy.
	 */
	*(u_int16_t *)(rfap + offsetof(struct fxp_rfa, rfa_status)) = 0;
	*(u_int16_t *)(rfap + offsetof(struct fxp_rfa, rfa_control)) =
	    htole16(FXP_RFA_CONTROL_EL);
	*(u_int16_t *)(rfap + offsetof(struct fxp_rfa, actual_size)) = 0;

	v = -1;
	fxp_lwcopy(&v,
	    (u_int32_t *)(rfap + offsetof(struct fxp_rfa, link_addr)));
	fxp_lwcopy(&v,
	    (u_int32_t *)(rfap + offsetof(struct fxp_rfa, rbd_addr)));

	/*
	 * If there are other buffers already on the list, attach this
	 * one to the end by fixing up the tail to point to this one.
	 */
	if (sc->rfa_headm != NULL) {
		sc->rfa_tailm->m_next = m;
		v = htole32(vtophys(rfap));
		rfap = sc->rfa_tailm->m_ext.ext_buf + RFA_ALIGNMENT_FUDGE;
#if defined(__mips__)
		/* Noone should have touched this, so no flush req. */
		rfap = (u_int8_t *)PHYS_TO_UNCACHED(vtophys(rfap));
#endif /* __mips__ */
		fxp_lwcopy(&v,
		    (u_int32_t *)(rfap + offsetof(struct fxp_rfa, link_addr)));
		*(u_int16_t *)(rfap + offsetof(struct fxp_rfa, rfa_control)) &=
		    ~htole16(FXP_RFA_CONTROL_EL);
	} else {
		sc->rfa_headm = m;
	}
	sc->rfa_tailm = m;

	return (m == oldm);
}

volatile int
fxp_mdi_read(self, phy, reg)
	struct device *self;
	int phy;
	int reg;
{
	struct fxp_softc *sc = (struct fxp_softc *)self;
	int count = 10000;
	int value;

	CSR_WRITE_4(sc, FXP_CSR_MDICONTROL,
	    (FXP_MDI_READ << 26) | (reg << 16) | (phy << 21));

	while (((value = CSR_READ_4(sc, FXP_CSR_MDICONTROL)) & 0x10000000) == 0
	    && count--)
		DELAY(10);

	if (count <= 0)
		printf(FXP_FORMAT ": fxp_mdi_read: timed out\n",
		    FXP_ARGS(sc));

	return (value & 0xffff);
}

static void
fxp_statchg(self)
	struct device *self;
{

	/* XXX Update ifp->if_baudrate */
}

void
fxp_mdi_write(self, phy, reg, value)
	struct device *self;
	int phy;
	int reg;
	int value;
{
	struct fxp_softc *sc = (struct fxp_softc *)self;
	int count = 10000;

	CSR_WRITE_4(sc, FXP_CSR_MDICONTROL,
	    (FXP_MDI_WRITE << 26) | (reg << 16) | (phy << 21) |
	    (value & 0xffff));

	while((CSR_READ_4(sc, FXP_CSR_MDICONTROL) & 0x10000000) == 0 &&
	    count--)
		DELAY(10);

	if (count <= 0)
		printf(FXP_FORMAT ": fxp_mdi_write: timed out\n",
		    FXP_ARGS(sc));
}

int
fxp_ioctl(ifp, command, data)
	struct ifnet *ifp;
	FXP_IOCTLCMD_TYPE command;
	caddr_t data;
{
	struct fxp_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	int s, error = 0;

	s = splimp();

	switch (command) {

	case SIOCSIFADDR:
#if !(defined(__NetBSD__) || defined(__OpenBSD__))
	case SIOCGIFADDR:
	case SIOCSIFMTU:
#endif
		error = ether_ioctl(ifp, command, data);
		break;

	case SIOCSIFFLAGS:
		sc->all_mcasts = (ifp->if_flags & IFF_ALLMULTI) ? 1 : 0;

		/*
		 * If interface is marked up and not running, then start it.
		 * If it is marked down and running, stop it.
		 * XXX If it's up then re-initialize it. This is so flags
		 * such as IFF_PROMISC are handled.
		 */
		if (ifp->if_flags & IFF_UP) {
			fxp_init(sc);
		} else {
			if (ifp->if_flags & IFF_RUNNING)
				fxp_stop(sc, 1);
		}
		break;

#ifdef USE_FXP_MCAST
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		sc->all_mcasts = (ifp->if_flags & IFF_ALLMULTI) ? 1 : 0;
#if defined(__NetBSD__) || defined(__OpenBSD__)
#if defined(__OpenBSD__)
		error = (command == SIOCADDMULTI) ?
		    ether_addmulti(ifr, &sc->arpcom) :
		    ether_delmulti(ifr, &sc->arpcom);
#else
		error = (command == SIOCADDMULTI) ?
		    ether_addmulti(ifr, &sc->sc_ethercom) :
		    ether_delmulti(ifr, &sc->sc_ethercom);
#endif

		if (error == ENETRESET) {
			/*
			 * Multicast list has changed; set the hardware
			 * filter accordingly.
			 */
			if (!sc->all_mcasts)
				fxp_mc_setup(sc);
			/*
			 * fxp_mc_setup() can turn on all_mcasts if we run
			 * out of space, so check it again rather than else {}.
			 */
			if (sc->all_mcasts)
				fxp_init(sc);
			error = 0;
		}
#else /* __FreeBSD__ */
		/*
		 * Multicast list has changed; set the hardware filter
		 * accordingly.
		 */
		fxp_init(sc);
		error = 0;
#endif /* __NetBSD__ || __OpenBSD__ */
		break;
#endif

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->sc_mii.mii_media, command);
		break;

	default:
		error = EINVAL;
	}
	(void) splx(s);
	return (error);
}

#ifdef USE_FXP_MCAST
/*
 * Program the multicast filter.
 *
 * We have an artificial restriction that the multicast setup command
 * must be the first command in the chain, so we take steps to ensure
 * this. By requiring this, it allows us to keep up the performance of
 * the pre-initialized command ring (esp. link pointers) by not actually
 * inserting the mcsetup command in the ring - i.e. its link pointer
 * points to the TxCB ring, but the mcsetup descriptor itself is not part
 * of it. We then can do 'CU_START' on the mcsetup descriptor and have it
 * lead into the regular TxCB ring when it completes.
 *
 * This function must be called at splimp.
 */
void
fxp_mc_setup(sc)
	struct fxp_softc *sc;
{
	struct fxp_cb_mcs *mcsp = sc->mcsp;
	struct ifnet *ifp = &sc->sc_if;
#if defined(__OpenBSD__)
	struct ether_multistep step;
	struct ether_multi *enm;
#else
	struct ifmultiaddr *ifma;
#endif
	int nmcasts;

	/*
	 * If there are queued commands, we must wait until they are all
	 * completed. If we are already waiting, then add a NOP command
	 * with interrupt option so that we're notified when all commands
	 * have been completed - fxp_start() ensures that no additional
	 * TX commands will be added when need_mcsetup is true.
	 */
	if (sc->tx_queued) {
		struct fxp_cb_tx *txp;

		/*
		 * need_mcsetup will be true if we are already waiting for the
		 * NOP command to be completed (see below). In this case, bail.
		 */
		if (sc->need_mcsetup)
			return;
		sc->need_mcsetup = 1;

		/*
		 * Add a NOP command with interrupt so that we are notified when all
		 * TX commands have been processed.
		 */
		txp = sc->cbl_last->next;
		txp->mb_head = NULL;
		txp->cb_status = htole16(0);
		txp->cb_command = htole16(FXP_CB_COMMAND_NOP | FXP_CB_COMMAND_S | FXP_CB_COMMAND_I);
		/*
		 * Advance the end of list forward.
		 */
		sc->cbl_last->cb_command &= htole16(~FXP_CB_COMMAND_S);
		sc->cbl_last = txp;
		sc->tx_queued++;
		/*
		 * Issue a resume in case the CU has just suspended.
		 */
		fxp_scb_wait(sc);
		CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_RESUME);
		/*
		 * Set a 5 second timer just in case we don't hear from the
		 * card again.
		 */
		ifp->if_timer = 5;

		return;
	}
	sc->need_mcsetup = 0;

	/*
	 * Initialize multicast setup descriptor.
	 */
	mcsp->next = sc->cbl_base;
	mcsp->mb_head = NULL;
	mcsp->cb_status = htole16(0);
	mcsp->cb_command = htole16(FXP_CB_COMMAND_MCAS | FXP_CB_COMMAND_S | FXP_CB_COMMAND_I);
	mcsp->link_addr = htole32(vtophys(&sc->cbl_base->cb_status));

	nmcasts = 0;
	if (!sc->all_mcasts) {
#if defined(__OpenBSD__)
		ETHER_FIRST_MULTI(step, &sc->arpcom, enm);
		while (enm != NULL) {
			if (nmcasts >= MAXMCADDR) {
				sc->all_mcasts = 1;
				nmcasts = 0;
				break;
			}

			/* Punt on ranges. */
			if (bcmp(enm->enm_addrlo, enm->enm_addrhi,
			    sizeof(enm->enm_addrlo)) != 0) {
				sc->all_mcasts = 1;
				nmcasts = 0;
				break;
			}
			bcopy(enm->enm_addrlo,
			    (void *) &sc->mcsp->mc_addr[nmcasts][0], 6);
			nmcasts++;
			ETHER_NEXT_MULTI(step, enm);
		}
#else
		for (ifma = ifp->if_multiaddrs.lh_first; ifma != NULL;
		    ifma = ifma->ifma_link.le_next) {
			if (ifma->ifma_addr->sa_family != AF_LINK)
				continue;
			if (nmcasts >= MAXMCADDR) {
				sc->all_mcasts = 1;
				nmcasts = 0;
				break;
			}
			bcopy(LLADDR((struct sockaddr_dl *)ifma->ifma_addr),
			    (void *) &sc->mcsp->mc_addr[nmcasts][0], 6);
			nmcasts++;
		}
#endif
	}
	mcsp->mc_cnt = htole16(nmcasts * 6);
	sc->cbl_first = sc->cbl_last = (struct fxp_cb_tx *) mcsp;
	sc->tx_queued = 1;

	/*
	 * Wait until command unit is not active. This should never
	 * be the case when nothing is queued, but make sure anyway.
	 */
	while ((CSR_READ_1(sc, FXP_CSR_SCB_RUSCUS) >> 6) ==
	    FXP_SCB_CUS_ACTIVE) ;

	/*
	 * Start the multicast setup command.
	 */
	fxp_scb_wait(sc);
	CSR_WRITE_4(sc, FXP_CSR_SCB_GENERAL, vtophys(&mcsp->cb_status));
	CSR_WRITE_1(sc, FXP_CSR_SCB_COMMAND, FXP_SCB_COMMAND_CU_START);

	ifp->if_timer = 2;
	return;
}
#endif
