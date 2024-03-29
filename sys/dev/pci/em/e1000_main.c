/*******************************************************************************

  
  Copyright(c) 1999 - 2003 Intel Corporation. All rights reserved.
  
  This program is free software; you can redistribute it and/or modify it 
  under the terms of the GNU General Public License as published by the Free 
  Software Foundation; either version 2 of the License, or (at your option) 
  any later version.
  
  This program is distributed in the hope that it will be useful, but WITHOUT 
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
  more details.
  
  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 59 
  Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  
  The full GNU General Public License is included in this distribution in the
  file called LICENSE.
  
  Contact Information:
  Linux NICS <linux.nics@intel.com>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

*******************************************************************************/

#include "e1000.h"

/* Change Log
 *
 * 5.1.13	5/28/03
 *   o Bug fix: request_irq() failure resulted in freeing resources twice!
 *     [Don Fry (brazilnut@us.ibm.com)]
 *   o Bug fix: fix VLAN support on ppc64 [Mark Rakes (mrakes@vivato.net)]
 *   o Bug fix: missing Tx cleanup opportunities during interrupt handling.
 *   o Bug fix: alloc_etherdev failure didn't cleanup regions in probe.
 *   o Cleanup: s/int/unsigned int/ for descriptor ring indexes.
 *   
 * 5.1.11	5/6/03
 *   o Feature: Added support for 82546EB (Quad-port) hardware.
 *   o Feature: Added support for Diagnostics through Ethtool.
 *   o Cleanup: Removed /proc support.
 *   o Cleanup: Removed proprietary IDIAG interface.
 *   o Bug fix: TSO bug fixes.
 *
 * 5.0.42	3/5/03
 */

char e1000_driver_name[] = "e1000";
char e1000_driver_string[] = "Intel(R) PRO/1000 Network Driver";
char e1000_driver_version[] = "5.1.13-k1";
char e1000_copyright[] = "Copyright (c) 1999-2003 Intel Corporation.";

/* e1000_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * { Vendor ID, Device ID, SubVendor ID, SubDevice ID,
 *   Class, Class Mask, private data (not used) }
 */
static struct pci_device_id e1000_pci_tbl[] __devinitdata = {
	{0x8086, 0x1000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1001, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1004, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1008, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1009, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x100C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x100D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x100E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x100F, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1011, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1010, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1012, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1016, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1017, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x101E, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x101D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1013, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1019, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x8086, 0x1079, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	/* required last entry */
	{0,}
};

MODULE_DEVICE_TABLE(pci, e1000_pci_tbl);

/* Local Function Prototypes */

int e1000_up(struct e1000_adapter *adapter);
void e1000_down(struct e1000_adapter *adapter);
void e1000_reset(struct e1000_adapter *adapter);

static int e1000_init_module(void);
static void e1000_exit_module(void);
static int e1000_probe(struct pci_dev *pdev, const struct pci_device_id *ent);
static int e1000_sw_init(struct e1000_adapter *adapter);
static int e1000_open(struct net_device *netdev);
static int e1000_close(struct net_device *netdev);
static int e1000_setup_tx_resources(struct e1000_adapter *adapter);
static int e1000_setup_rx_resources(struct e1000_adapter *adapter);
static void e1000_configure_tx(struct e1000_adapter *adapter);
static void e1000_configure_rx(struct e1000_adapter *adapter);
static void e1000_setup_rctl(struct e1000_adapter *adapter);
static void e1000_clean_tx_ring(struct e1000_adapter *adapter);
static void e1000_clean_rx_ring(struct e1000_adapter *adapter);
static void e1000_free_tx_resources(struct e1000_adapter *adapter);
static void e1000_free_rx_resources(struct e1000_adapter *adapter);
static void e1000_set_multi(struct net_device *netdev);
static void e1000_update_phy_info(unsigned long data);
static void e1000_watchdog(unsigned long data);
static void e1000_82547_tx_fifo_stall(unsigned long data);
static int e1000_xmit_frame(struct sk_buff *skb, struct net_device *netdev);
static struct net_device_stats * e1000_get_stats(struct net_device *netdev);
static int e1000_change_mtu(struct net_device *netdev, int new_mtu);
static int e1000_set_mac(struct net_device *netdev, void *p);
static void e1000_update_stats(struct e1000_adapter *adapter);
static inline void e1000_irq_disable(struct e1000_adapter *adapter);
static inline void e1000_irq_enable(struct e1000_adapter *adapter);
static void e1000_intr(int irq, void *data, struct pt_regs *regs);
static boolean_t e1000_clean_tx_irq(struct e1000_adapter *adapter);
#ifdef CONFIG_E1000_NAPI
static int e1000_clean(struct net_device *netdev, int *budget);
static boolean_t e1000_clean_rx_irq(struct e1000_adapter *adapter,
                                    int *work_done, int work_to_do);
#else
static boolean_t e1000_clean_rx_irq(struct e1000_adapter *adapter);
#endif
static void e1000_alloc_rx_buffers(struct e1000_adapter *adapter);
static int e1000_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd);
static int e1000_mii_ioctl(struct net_device *netdev, struct ifreq *ifr,
			   int cmd);
static void e1000_enter_82542_rst(struct e1000_adapter *adapter);
static void e1000_leave_82542_rst(struct e1000_adapter *adapter);
static inline void e1000_rx_checksum(struct e1000_adapter *adapter,
                                     struct e1000_rx_desc *rx_desc,
                                     struct sk_buff *skb);
static void e1000_tx_timeout(struct net_device *dev);
static void e1000_tx_timeout_task(struct net_device *dev);
static void e1000_smartspeed(struct e1000_adapter *adapter);
static inline int e1000_82547_fifo_workaround(struct e1000_adapter *adapter,
					      struct sk_buff *skb);




/* Exported from other modules */

extern void e1000_check_options(struct e1000_adapter *adapter);
extern int e1000_ethtool_ioctl(struct net_device *netdev, struct ifreq *ifr);



int
e1000_up(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	/* hardware has been reset, we need to reload some things */

	e1000_set_multi(netdev);


	e1000_configure_tx(adapter);
	e1000_setup_rctl(adapter);
	e1000_configure_rx(adapter);
	e1000_alloc_rx_buffers(adapter);

	if(request_irq(netdev->irq, &e1000_intr, SA_SHIRQ | SA_SAMPLE_RANDOM,
		       netdev->name, netdev))
		return -1;

	mod_timer(&adapter->watchdog_timer, jiffies);
	e1000_irq_enable(adapter);

	return 0;
}

void
e1000_down(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	e1000_irq_disable(adapter);
	free_irq(netdev->irq, netdev);
	del_timer_sync(&adapter->tx_fifo_stall_timer);
	del_timer_sync(&adapter->watchdog_timer);
	del_timer_sync(&adapter->phy_info_timer);
	adapter->link_speed = 0;
	adapter->link_duplex = 0;
	netif_carrier_off(netdev);
	netif_stop_queue(netdev);

	e1000_reset(adapter);
	e1000_clean_tx_ring(adapter);
	e1000_clean_rx_ring(adapter);
}

void
e1000_reset(struct e1000_adapter *adapter)
{
	uint32_t pba;
	/* Repartition Pba for greater than 9k mtu
	 * To take effect CTRL.RST is required.
	 */

	if(adapter->hw.mac_type < e1000_82547) {
		if(adapter->rx_buffer_len > E1000_RXBUFFER_8192)
			pba = E1000_PBA_40K;
		else
			pba = E1000_PBA_48K;
	} else {
		if(adapter->rx_buffer_len > E1000_RXBUFFER_8192)
			pba = E1000_PBA_22K;
		else
			pba = E1000_PBA_30K;
		adapter->tx_fifo_head = 0;
		adapter->tx_head_addr = pba << E1000_TX_HEAD_ADDR_SHIFT;
		adapter->tx_fifo_size =
			(E1000_PBA_40K - pba) << E1000_TX_FIFO_SIZE_SHIFT;
		atomic_set(&adapter->tx_fifo_stall, 0);
	}
	E1000_WRITE_REG(&adapter->hw, PBA, pba);

	adapter->hw.fc = adapter->hw.original_fc;
	e1000_reset_hw(&adapter->hw);
	if(adapter->hw.mac_type >= e1000_82544)
		E1000_WRITE_REG(&adapter->hw, WUC, 0);
	e1000_init_hw(&adapter->hw);
	e1000_reset_adaptive(&adapter->hw);
	e1000_phy_get_info(&adapter->hw, &adapter->phy_info);
}

static int __devinit
em_probe(struct net_device *netdev,
		            const struct pci_device_id *ent,struct pci_dev *pdev)
{
    struct e1000_adapter *adapter;
    static int cards_found = 0;
    unsigned long mmio_start;
    int mmio_len;
    int pci_using_dac;
    int i;
    uint16_t eeprom_data;

	adapter = netdev->priv;
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.back = adapter;

	mmio_start = pci_resource_start(pdev, BAR_0);
	mmio_len = pci_resource_len(pdev, BAR_0);

	adapter->hw.hw_addr = ioremap(mmio_start, mmio_len);
	if(!adapter->hw.hw_addr)
		goto err_ioremap;

	for(i = BAR_1; i <= BAR_5; i++) {
		if(pci_resource_len(pdev, i) == 0)
			continue;
		if(pci_resource_flags(pdev, i) & IORESOURCE_IO) {
			adapter->hw.io_base = pci_resource_start(pdev, i);
			break;
		}
	}


	adapter->bd_number = cards_found;

	/* setup the private structure */

	if(e1000_sw_init(adapter))
		goto err_sw_init;

	if(adapter->hw.mac_type >= e1000_82543) {
		netdev->features = NETIF_F_SG |
				   NETIF_F_HW_CSUM |
				   NETIF_F_HW_VLAN_TX |
				   NETIF_F_HW_VLAN_RX |
				   NETIF_F_HW_VLAN_FILTER;
	} else {
		netdev->features = NETIF_F_SG;
	}


	if(pci_using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	/* make sure the EEPROM is good */
#if 0
	if(e1000_validate_eeprom_checksum(&adapter->hw) < 0) {
		printk(KERN_ERR "The EEPROM Checksum Is Not Valid\n");
		goto err_eeprom;
	}
#endif
	/* copy the MAC address out of the EEPROM */

	e1000_read_mac_addr(&adapter->hw);
	memcpy(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);

	if(!is_valid_ether_addr(netdev->dev_addr))
		goto err_eeprom;

	e1000_read_part_num(&adapter->hw, &(adapter->part_num));

	e1000_get_bus_info(&adapter->hw);

	init_timer(&adapter->tx_fifo_stall_timer);
	adapter->tx_fifo_stall_timer.function = &e1000_82547_tx_fifo_stall;
	adapter->tx_fifo_stall_timer.data = (unsigned long) adapter;

	init_timer(&adapter->watchdog_timer);
	adapter->watchdog_timer.function = &e1000_watchdog;
	adapter->watchdog_timer.data = (unsigned long) adapter;

	init_timer(&adapter->phy_info_timer);
	adapter->phy_info_timer.function = &e1000_update_phy_info;
	adapter->phy_info_timer.data = (unsigned long) adapter;

	INIT_TQUEUE(&adapter->tx_timeout_task,
		(void (*)(void *))e1000_tx_timeout_task, netdev);

	netdev->irq = pdev->irq;
	netdev->mem_start = mmio_start;
	netdev->mem_end = mmio_start + mmio_len;
	netdev->base_addr = adapter->hw.io_base;

	/* we're going to reset, so assume we have no link for now */

	netif_carrier_off(netdev);
	netif_stop_queue(netdev);

	printk(KERN_INFO "%s: Intel(R) PRO/1000 Network Connection\n",
	       netdev->name);
	e1000_check_options(adapter);

	/* Initial Wake on LAN setting
	 * If APM wake is enabled in the EEPROM,
	 * enable the ACPI Magic Packet filter
	 */

	e1000_read_eeprom(&adapter->hw, EEPROM_INIT_CONTROL2_REG,1, &eeprom_data);
	if((adapter->hw.mac_type >= e1000_82544) &&
	   (eeprom_data & E1000_EEPROM_APME))
		adapter->wol |= E1000_WUFC_MAG;


	/* reset the hardware with the new settings */

	e1000_reset(adapter);

	cards_found++;
	return 0;

err_sw_init:
err_eeprom:
	iounmap(adapter->hw.hw_addr);
err_ioremap:
	kfree(netdev);
	return -ENOMEM;
}


/**
 * e1000_sw_init - Initialize general software structures (struct e1000_adapter)
 * @adapter: board private structure to initialize
 *
 * e1000_sw_init initializes the Adapter private data structure.
 * Fields are initialized based on PCI device information and
 * OS network device settings (MTU size).
 **/

static int __devinit
e1000_sw_init(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;

	/* PCI config space info */

	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_id = pdev->subsystem_device;

	pci_read_config_byte(pdev, PCI_REVISION_ID, &hw->revision_id);

	pci_read_config_word(pdev, PCI_COMMAND, &hw->pci_cmd_word);

	adapter->rx_buffer_len = E1000_RXBUFFER_2048;
	hw->max_frame_size = netdev->mtu +
			     ENET_HEADER_SIZE + ETHERNET_FCS_SIZE;
	hw->min_frame_size = MINIMUM_ETHERNET_FRAME_SIZE;

	/* identify the MAC */

	if (e1000_set_mac_type(hw)) {
		E1000_ERR("Unknown MAC Type\n");
		return -1;
	}

	/* initialize eeprom parameters */

	e1000_init_eeprom_params(hw);

	/* flow control settings */

	hw->fc_high_water = E1000_FC_HIGH_THRESH;
	hw->fc_low_water = E1000_FC_LOW_THRESH;
	hw->fc_pause_time = E1000_FC_PAUSE_TIME;
	hw->fc_send_xon = 1;

	if((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547))
		hw->phy_init_script = 1;

	/* Media type - copper or fiber */

	if(hw->mac_type >= e1000_82543) {
		uint32_t status = E1000_READ_REG(hw, STATUS);

		if(status & E1000_STATUS_TBIMODE)
			hw->media_type = e1000_media_type_fiber;
		else
			hw->media_type = e1000_media_type_copper;
	} else {
		hw->media_type = e1000_media_type_fiber;
	}

	if(hw->mac_type < e1000_82543)
		hw->report_tx_early = 0;
	else
		hw->report_tx_early = 1;

	hw->wait_autoneg_complete = FALSE;
	hw->tbi_compatibility_en = TRUE;
	hw->adaptive_ifs = TRUE;

	/* Copper options */

	if(hw->media_type == e1000_media_type_copper) {
		hw->mdix = AUTO_ALL_MODES;
		hw->disable_polarity_correction = FALSE;
	}

	atomic_set(&adapter->irq_sem, 1);
	spin_lock_init(&adapter->stats_lock);

	return 0;
}

/**
 * e1000_open - Called when a network interface is made active
 * @netdev: network interface device structure
 *
 * Returns 0 on success, negative value on failure
 *
 * The open entry point is called when a network interface is made
 * active by the system (IFF_UP).  At this point all resources needed
 * for transmit and receive operations are allocated, the interrupt
 * handler is registered with the OS, the watchdog timer is started,
 * and the stack is notified that the interface is ready.
 **/

static int
e1000_open(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev->priv;

	/* allocate transmit descriptors */

	if(e1000_setup_tx_resources(adapter))
		goto err_setup_tx;

	/* allocate receive descriptors */

	if(e1000_setup_rx_resources(adapter))
		goto err_setup_rx;

	if(e1000_up(adapter))
		goto err_up;

	return 0;

err_up:
	e1000_free_rx_resources(adapter);
err_setup_rx:
	e1000_free_tx_resources(adapter);
err_setup_tx:
	e1000_reset(adapter);

	return -EBUSY;
}

/**
 * e1000_close - Disables a network interface
 * @netdev: network interface device structure
 *
 * Returns 0, this is not allowed to fail
 *
 * The close entry point is called when an interface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are freed.
 **/

static int
e1000_close(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev->priv;

	e1000_down(adapter);

	e1000_free_tx_resources(adapter);
	e1000_free_rx_resources(adapter);

	return 0;
}

/**
 * e1000_setup_tx_resources - allocate Tx resources (Descriptors)
 * @adapter: board private structure
 *
 * Return 0 on success, negative on failure
 **/

static int
e1000_setup_tx_resources(struct e1000_adapter *adapter)
{
	struct e1000_desc_ring *txdr = &adapter->tx_ring;
	struct pci_dev *pdev = adapter->pdev;
	int size;

	size = sizeof(struct e1000_buffer) * txdr->count;
	txdr->buffer_info = kmalloc(size, GFP_KERNEL);
	if(!txdr->buffer_info) {
		return -ENOMEM;
	}
	memset(txdr->buffer_info, 0, size);

	/* round up to nearest 4K */

	txdr->size = txdr->count * sizeof(struct e1000_tx_desc);
	E1000_ROUNDUP(txdr->size, 4096);

	txdr->desc = pci_alloc_consistent(pdev, txdr->size, &txdr->dma);
	if(!txdr->desc) {
		kfree(txdr->buffer_info);
		return -ENOMEM;
	}
	memset(txdr->desc, 0, txdr->size);

	txdr->next_to_use = 0;
	txdr->next_to_clean = 0;

	return 0;
}

/**
 * e1000_configure_tx - Configure 8254x Transmit Unit after Reset
 * @adapter: board private structure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/

static void
e1000_configure_tx(struct e1000_adapter *adapter)
{
	uint64_t tdba = adapter->tx_ring.dma;
	uint32_t tdlen = adapter->tx_ring.count * sizeof(struct e1000_tx_desc);
	uint32_t tctl, tipg;

	E1000_WRITE_REG(&adapter->hw, TDBAL, (tdba & 0x00000000ffffffffULL));
	E1000_WRITE_REG(&adapter->hw, TDBAH, (tdba >> 32));

	E1000_WRITE_REG(&adapter->hw, TDLEN, tdlen);

	/* Setup the HW Tx Head and Tail descriptor pointers */

	E1000_WRITE_REG(&adapter->hw, TDH, 0);
	E1000_WRITE_REG(&adapter->hw, TDT, 0);

	/* Set the default values for the Tx Inter Packet Gap timer */

	switch (adapter->hw.mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
		tipg = DEFAULT_82542_TIPG_IPGT;
		tipg |= DEFAULT_82542_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		tipg |= DEFAULT_82542_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
		break;
	default:
		if(adapter->hw.media_type == e1000_media_type_fiber)
			tipg = DEFAULT_82543_TIPG_IPGT_FIBER;
		else
			tipg = DEFAULT_82543_TIPG_IPGT_COPPER;
		tipg |= DEFAULT_82543_TIPG_IPGR1 << E1000_TIPG_IPGR1_SHIFT;
		tipg |= DEFAULT_82543_TIPG_IPGR2 << E1000_TIPG_IPGR2_SHIFT;
	}
	E1000_WRITE_REG(&adapter->hw, TIPG, tipg);

	/* Set the Tx Interrupt Delay register */

	E1000_WRITE_REG(&adapter->hw, TIDV, adapter->tx_int_delay);
	if(adapter->hw.mac_type >= e1000_82540)
		E1000_WRITE_REG(&adapter->hw, TADV, adapter->tx_abs_int_delay);

	/* Program the Transmit Control Register */

	tctl = E1000_READ_REG(&adapter->hw, TCTL);

	tctl &= ~E1000_TCTL_CT;
	tctl |= E1000_TCTL_EN | E1000_TCTL_PSP |
		(E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

	E1000_WRITE_REG(&adapter->hw, TCTL, tctl);

	e1000_config_collision_dist(&adapter->hw);

	/* Setup Transmit Descriptor Settings for eop descriptor */
	adapter->txd_cmd = E1000_TXD_CMD_IDE | E1000_TXD_CMD_EOP |
		E1000_TXD_CMD_IFCS;

	if(adapter->hw.report_tx_early == 1)
		adapter->txd_cmd |= E1000_TXD_CMD_RS;
	else
		adapter->txd_cmd |= E1000_TXD_CMD_RPS;
}

/**
 * e1000_setup_rx_resources - allocate Rx resources (Descriptors)
 * @adapter: board private structure
 *
 * Returns 0 on success, negative on failure
 **/

static int
e1000_setup_rx_resources(struct e1000_adapter *adapter)
{
	struct e1000_desc_ring *rxdr = &adapter->rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	int size;

	size = sizeof(struct e1000_buffer) * rxdr->count;
	rxdr->buffer_info = kmalloc(size, GFP_KERNEL);
	if(!rxdr->buffer_info) {
		return -ENOMEM;
	}
	memset(rxdr->buffer_info, 0, size);

	/* Round up to nearest 4K */

	rxdr->size = rxdr->count * sizeof(struct e1000_rx_desc);
	E1000_ROUNDUP(rxdr->size, 4096);

	rxdr->desc = pci_alloc_consistent(pdev, rxdr->size, &rxdr->dma);

	if(!rxdr->desc) {
		kfree(rxdr->buffer_info);
		return -ENOMEM;
	}
	memset(rxdr->desc, 0, rxdr->size);

	rxdr->next_to_clean = 0;
	rxdr->next_to_use = 0;

	return 0;
}

/**
 * e1000_setup_rctl - configure the receive control register
 * @adapter: Board private structure
 **/

static void
e1000_setup_rctl(struct e1000_adapter *adapter)
{
	uint32_t rctl;

	rctl = E1000_READ_REG(&adapter->hw, RCTL);

	rctl &= ~(3 << E1000_RCTL_MO_SHIFT);

	rctl |= E1000_RCTL_EN | E1000_RCTL_BAM |
		E1000_RCTL_LBM_NO | E1000_RCTL_RDMTS_HALF |
		(adapter->hw.mc_filter_type << E1000_RCTL_MO_SHIFT);

	if(adapter->hw.tbi_compatibility_on == 1)
		rctl |= E1000_RCTL_SBP;
	else
		rctl &= ~E1000_RCTL_SBP;

	rctl &= ~(E1000_RCTL_SZ_4096);
	switch (adapter->rx_buffer_len) {
	case E1000_RXBUFFER_2048:
	default:
		rctl |= E1000_RCTL_SZ_2048;
		rctl &= ~(E1000_RCTL_BSEX | E1000_RCTL_LPE);
		break;
	case E1000_RXBUFFER_4096:
		rctl |= E1000_RCTL_SZ_4096 | E1000_RCTL_BSEX | E1000_RCTL_LPE;
		break;
	case E1000_RXBUFFER_8192:
		rctl |= E1000_RCTL_SZ_8192 | E1000_RCTL_BSEX | E1000_RCTL_LPE;
		break;
	case E1000_RXBUFFER_16384:
		rctl |= E1000_RCTL_SZ_16384 | E1000_RCTL_BSEX | E1000_RCTL_LPE;
		break;
	}

	E1000_WRITE_REG(&adapter->hw, RCTL, rctl);
}

/**
 * e1000_configure_rx - Configure 8254x Receive Unit after Reset
 * @adapter: board private structure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/

static void
e1000_configure_rx(struct e1000_adapter *adapter)
{
	uint64_t rdba = adapter->rx_ring.dma;
	uint32_t rdlen = adapter->rx_ring.count * sizeof(struct e1000_rx_desc);
	uint32_t rctl;
	uint32_t rxcsum;

	/* make sure receives are disabled while setting up the descriptors */

	rctl = E1000_READ_REG(&adapter->hw, RCTL);
	E1000_WRITE_REG(&adapter->hw, RCTL, rctl & ~E1000_RCTL_EN);

	/* set the Receive Delay Timer Register */

	E1000_WRITE_REG(&adapter->hw, RDTR, adapter->rx_int_delay);

	if(adapter->hw.mac_type >= e1000_82540) {
		E1000_WRITE_REG(&adapter->hw, RADV, adapter->rx_abs_int_delay);
		if(adapter->itr > 1)
			E1000_WRITE_REG(&adapter->hw, ITR,
				1000000000 / (adapter->itr * 256));
	}

	/* Setup the Base and Length of the Rx Descriptor Ring */

	E1000_WRITE_REG(&adapter->hw, RDBAL, (rdba & 0x00000000ffffffffULL));
	E1000_WRITE_REG(&adapter->hw, RDBAH, (rdba >> 32));

	E1000_WRITE_REG(&adapter->hw, RDLEN, rdlen);

	/* Setup the HW Rx Head and Tail Descriptor Pointers */
	E1000_WRITE_REG(&adapter->hw, RDH, 0);
	E1000_WRITE_REG(&adapter->hw, RDT, 0);

	/* Enable 82543 Receive Checksum Offload for TCP and UDP */
	if((adapter->hw.mac_type >= e1000_82543) &&
	   (adapter->rx_csum == TRUE)) {
		rxcsum = E1000_READ_REG(&adapter->hw, RXCSUM);
		rxcsum |= E1000_RXCSUM_TUOFL;
		E1000_WRITE_REG(&adapter->hw, RXCSUM, rxcsum);
	}

	/* Enable Receives */

	E1000_WRITE_REG(&adapter->hw, RCTL, rctl);
}

/**
 * e1000_free_tx_resources - Free Tx Resources
 * @adapter: board private structure
 *
 * Free all transmit software resources
 **/

static void
e1000_free_tx_resources(struct e1000_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;

	e1000_clean_tx_ring(adapter);

	kfree(adapter->tx_ring.buffer_info);
	adapter->tx_ring.buffer_info = NULL;

	pci_free_consistent(pdev, adapter->tx_ring.size,
	                    adapter->tx_ring.desc, adapter->tx_ring.dma);

	adapter->tx_ring.desc = NULL;
}

/**
 * e1000_clean_tx_ring - Free Tx Buffers
 * @adapter: board private structure
 **/

static void
e1000_clean_tx_ring(struct e1000_adapter *adapter)
{
	struct e1000_desc_ring *tx_ring = &adapter->tx_ring;
	struct e1000_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned long size;
	unsigned int i;

	/* Free all the Tx ring sk_buffs */

	for(i = 0; i < tx_ring->count; i++) {
		buffer_info = &tx_ring->buffer_info[i];
		if(buffer_info->skb) {

			pci_unmap_page(pdev,
			               buffer_info->dma,
			               buffer_info->length,
			               PCI_DMA_TODEVICE);

			dev_kfree_skb(buffer_info->skb);

			buffer_info->skb = NULL;
		}
	}

	size = sizeof(struct e1000_buffer) * tx_ring->count;
	memset(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	E1000_WRITE_REG(&adapter->hw, TDH, 0);
	E1000_WRITE_REG(&adapter->hw, TDT, 0);
}

/**
 * e1000_free_rx_resources - Free Rx Resources
 * @adapter: board private structure
 *
 * Free all receive software resources
 **/

static void
e1000_free_rx_resources(struct e1000_adapter *adapter)
{
	struct e1000_desc_ring *rx_ring = &adapter->rx_ring;
	struct pci_dev *pdev = adapter->pdev;

	e1000_clean_rx_ring(adapter);

	kfree(rx_ring->buffer_info);
	rx_ring->buffer_info = NULL;

	pci_free_consistent(pdev, rx_ring->size, rx_ring->desc, rx_ring->dma);

	rx_ring->desc = NULL;
}

/**
 * e1000_clean_rx_ring - Free Rx Buffers
 * @adapter: board private structure
 **/

static void
e1000_clean_rx_ring(struct e1000_adapter *adapter)
{
	struct e1000_desc_ring *rx_ring = &adapter->rx_ring;
	struct e1000_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned long size;
	unsigned int i;

	/* Free all the Rx ring sk_buffs */

	for(i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		if(buffer_info->skb) {

			pci_unmap_single(pdev,
			                 buffer_info->dma,
			                 buffer_info->length,
			                 PCI_DMA_FROMDEVICE);

			dev_kfree_skb(buffer_info->skb);

			buffer_info->skb = NULL;
		}
	}

	size = sizeof(struct e1000_buffer) * rx_ring->count;
	memset(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	E1000_WRITE_REG(&adapter->hw, RDH, 0);
	E1000_WRITE_REG(&adapter->hw, RDT, 0);
}

/* The 82542 2.0 (revision 2) needs to have the receive unit in reset
 * and memory write and invalidate disabled for certain operations
 */
static void
e1000_enter_82542_rst(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	uint32_t rctl;

	e1000_pci_clear_mwi(&adapter->hw);

	rctl = E1000_READ_REG(&adapter->hw, RCTL);
	rctl |= E1000_RCTL_RST;
	E1000_WRITE_REG(&adapter->hw, RCTL, rctl);
	E1000_WRITE_FLUSH(&adapter->hw);
	mdelay(5);

	if(netif_running(netdev))
		e1000_clean_rx_ring(adapter);
}

static void
e1000_leave_82542_rst(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	uint32_t rctl;

	rctl = E1000_READ_REG(&adapter->hw, RCTL);
	rctl &= ~E1000_RCTL_RST;
	E1000_WRITE_REG(&adapter->hw, RCTL, rctl);
	E1000_WRITE_FLUSH(&adapter->hw);
	mdelay(5);

	if(adapter->hw.pci_cmd_word & PCI_COMMAND_INVALIDATE)
		e1000_pci_set_mwi(&adapter->hw);

	if(netif_running(netdev)) {
		e1000_configure_rx(adapter);
		e1000_alloc_rx_buffers(adapter);
	}
}

/**
 * e1000_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network interface device structure
 * @p: pointer to an address structure
 *
 * Returns 0 on success, negative on failure
 **/

static int
e1000_set_mac(struct net_device *netdev, void *p)
{
	struct e1000_adapter *adapter = netdev->priv;
	struct sockaddr *addr = p;

	if(!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	/* 82542 2.0 needs to be in reset to write receive address registers */

	if(adapter->hw.mac_type == e1000_82542_rev2_0)
		e1000_enter_82542_rst(adapter);

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	memcpy(adapter->hw.mac_addr, addr->sa_data, netdev->addr_len);

	e1000_rar_set(&adapter->hw, adapter->hw.mac_addr, 0);

	if(adapter->hw.mac_type == e1000_82542_rev2_0)
		e1000_leave_82542_rst(adapter);

	return 0;
}

/**
 * e1000_set_multi - Multicast and Promiscuous mode set
 * @netdev: network interface device structure
 *
 * The set_multi entry point is called whenever the multicast address
 * list or the network interface flags are updated.  This routine is
 * responsible for configuring the hardware for proper multicast,
 * promiscuous mode, and all-multi behavior.
 **/

static void
e1000_set_multi(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev->priv;
	struct e1000_hw *hw = &adapter->hw;
	struct dev_mc_list *mc_ptr;
	uint32_t rctl;
	uint32_t hash_value;
	int i;

	/* Check for Promiscuous and All Multicast modes */

	rctl = E1000_READ_REG(hw, RCTL);

	if(netdev->flags & IFF_PROMISC) {
		rctl |= (E1000_RCTL_UPE | E1000_RCTL_MPE);
	} else if(netdev->flags & IFF_ALLMULTI) {
		rctl |= E1000_RCTL_MPE;
		rctl &= ~E1000_RCTL_UPE;
	} else {
		rctl &= ~(E1000_RCTL_UPE | E1000_RCTL_MPE);
	}

	E1000_WRITE_REG(hw, RCTL, rctl);

	/* 82542 2.0 needs to be in reset to write receive address registers */

	if(hw->mac_type == e1000_82542_rev2_0)
		e1000_enter_82542_rst(adapter);

	/* load the first 14 multicast address into the exact filters 1-14
	 * RAR 0 is used for the station MAC adddress
	 * if there are not 14 addresses, go ahead and clear the filters
	 */
	mc_ptr = netdev->mc_list;

	for(i = 1; i < E1000_RAR_ENTRIES; i++) {
		if(mc_ptr) {
			e1000_rar_set(hw, mc_ptr->dmi_addr, i);
			mc_ptr = mc_ptr->next;
		} else {
			E1000_WRITE_REG_ARRAY(hw, RA, i << 1, 0);
			E1000_WRITE_REG_ARRAY(hw, RA, (i << 1) + 1, 0);
		}
	}

	/* clear the old settings from the multicast hash table */

	for(i = 0; i < E1000_NUM_MTA_REGISTERS; i++)
		E1000_WRITE_REG_ARRAY(hw, MTA, i, 0);

	/* load any remaining addresses into the hash table */

	for(; mc_ptr; mc_ptr = mc_ptr->next) {
		hash_value = e1000_hash_mc_addr(hw, mc_ptr->dmi_addr);
		e1000_mta_set(hw, hash_value);
	}

	if(hw->mac_type == e1000_82542_rev2_0)
		e1000_leave_82542_rst(adapter);
}

static void
e1000_tx_flush(struct e1000_adapter *adapter)
{
	uint32_t ctrl, tctl, txcw, icr;

	e1000_irq_disable(adapter);

	if(adapter->hw.mac_type < e1000_82543) {
		/* Transmit Unit Reset */
		tctl = E1000_READ_REG(&adapter->hw, TCTL);
		E1000_WRITE_REG(&adapter->hw, TCTL, tctl | E1000_TCTL_RST);
		E1000_WRITE_REG(&adapter->hw, TCTL, tctl);
		e1000_clean_tx_ring(adapter);
		e1000_configure_tx(adapter);
	} else {
		txcw = E1000_READ_REG(&adapter->hw, TXCW);
		E1000_WRITE_REG(&adapter->hw, TXCW, txcw & ~E1000_TXCW_ANE);

		ctrl = E1000_READ_REG(&adapter->hw, CTRL);
		E1000_WRITE_REG(&adapter->hw, CTRL, ctrl | E1000_CTRL_SLU |
				E1000_CTRL_ILOS);

		mdelay(10);

		e1000_clean_tx_irq(adapter);
		E1000_WRITE_REG(&adapter->hw, CTRL, ctrl);
		E1000_WRITE_REG(&adapter->hw, TXCW, txcw);

		/* clear the link status change interrupts this caused */
		icr = E1000_READ_REG(&adapter->hw, ICR);
	}

	e1000_irq_enable(adapter);
}

/* need to wait a few seconds after link up to get diagnostic information from the phy */

static void
e1000_update_phy_info(unsigned long data)
{
	struct e1000_adapter *adapter = (struct e1000_adapter *) data;
	e1000_phy_get_info(&adapter->hw, &adapter->phy_info);
}

/**
 * e1000_82547_tx_fifo_stall - Timer Call-back
 * @data: pointer to adapter cast into an unsigned long
 **/

static void
e1000_82547_tx_fifo_stall(unsigned long data)
{
	struct e1000_adapter *adapter = (struct e1000_adapter *) data;
	struct net_device *netdev = adapter->netdev;
	uint32_t tctl;

	if(atomic_read(&adapter->tx_fifo_stall)) {
		if((E1000_READ_REG(&adapter->hw, TDT) ==
		    E1000_READ_REG(&adapter->hw, TDH)) &&
		   (E1000_READ_REG(&adapter->hw, TDFT) ==
		    E1000_READ_REG(&adapter->hw, TDFH)) &&
		   (E1000_READ_REG(&adapter->hw, TDFTS) ==
		    E1000_READ_REG(&adapter->hw, TDFHS))) {
			tctl = E1000_READ_REG(&adapter->hw, TCTL);
			E1000_WRITE_REG(&adapter->hw, TCTL,
					tctl & ~E1000_TCTL_EN);
			E1000_WRITE_REG(&adapter->hw, TDFT,
					adapter->tx_head_addr);
			E1000_WRITE_REG(&adapter->hw, TDFH,
					adapter->tx_head_addr);
			E1000_WRITE_REG(&adapter->hw, TDFTS,
					adapter->tx_head_addr);
			E1000_WRITE_REG(&adapter->hw, TDFHS,
					adapter->tx_head_addr);
			E1000_WRITE_REG(&adapter->hw, TCTL, tctl);
			E1000_WRITE_FLUSH(&adapter->hw);

			adapter->tx_fifo_head = 0;
			atomic_set(&adapter->tx_fifo_stall, 0);
			netif_wake_queue(netdev);
		} else {
			mod_timer(&adapter->tx_fifo_stall_timer, jiffies + 1);
		}
	}
}

/**
 * e1000_watchdog - Timer Call-back
 * @data: pointer to netdev cast into an unsigned long
 **/

static void
e1000_watchdog(unsigned long data)
{
	struct e1000_adapter *adapter = (struct e1000_adapter *) data;
	struct net_device *netdev = adapter->netdev;
	struct e1000_desc_ring *txdr = &adapter->tx_ring;
	unsigned int i;

	e1000_check_for_link(&adapter->hw);

	if(E1000_READ_REG(&adapter->hw, STATUS) & E1000_STATUS_LU) {
		if(!netif_carrier_ok(netdev)) {
			e1000_get_speed_and_duplex(&adapter->hw,
			                           &adapter->link_speed,
			                           &adapter->link_duplex);

			printk(KERN_INFO
			       "e1000: %s NIC Link is Up %d Mbps %s\n",
			       netdev->name, adapter->link_speed,
			       adapter->link_duplex == FULL_DUPLEX ?
			       "Full Duplex" : "Half Duplex");

			netif_carrier_on(netdev);
			netif_wake_queue(netdev);
			mod_timer(&adapter->phy_info_timer, jiffies + 2 * HZ);
			adapter->smartspeed = 0;
		}
	} else {
		if(netif_carrier_ok(netdev)) {
			adapter->link_speed = 0;
			adapter->link_duplex = 0;
			printk(KERN_INFO
			       "e1000: %s NIC Link is Down\n",
			       netdev->name);
			netif_carrier_off(netdev);
			netif_stop_queue(netdev);
			mod_timer(&adapter->phy_info_timer, jiffies + 2 * HZ);
		}

		e1000_smartspeed(adapter);
	}

	e1000_update_stats(adapter);
	e1000_update_adaptive(&adapter->hw);

	if(!netif_carrier_ok(netdev)) {
		if(E1000_DESC_UNUSED(txdr) + 1 < txdr->count) {
			unsigned long flags;
			spin_lock_irqsave(&netdev->xmit_lock, flags);
			e1000_tx_flush(adapter);
			spin_unlock_irqrestore(&netdev->xmit_lock, flags);
		}
	}

	/* Dynamic mode for Interrupt Throttle Rate (ITR) */
	if(adapter->hw.mac_type >= e1000_82540 && adapter->itr == 1) {
		/* Symmetric Tx/Rx gets a reduced ITR=2000; Total
		 * asymmetrical Tx or Rx gets ITR=8000; everyone
		 * else is between 2000-8000. */
		uint32_t goc = (adapter->gotcl + adapter->gorcl) / 10000;
		uint32_t dif = (adapter->gotcl > adapter->gorcl ? 
			adapter->gotcl - adapter->gorcl :
			adapter->gorcl - adapter->gotcl) / 10000;
		uint32_t itr = goc > 0 ? (dif * 6000 / goc + 2000) : 8000;
		E1000_WRITE_REG(&adapter->hw, ITR, 1000000000 / (itr * 256));
	}

	/* Cause software interrupt to ensure rx ring is cleaned */
	E1000_WRITE_REG(&adapter->hw, ICS, E1000_ICS_RXDMT0);

	/* Early detection of hung controller */
	i = txdr->next_to_clean;
	if(txdr->buffer_info[i].dma &&
	   time_after(jiffies, txdr->buffer_info[i].time_stamp + HZ) &&
	   !(E1000_READ_REG(&adapter->hw, STATUS) & E1000_STATUS_TXOFF))
		netif_stop_queue(netdev);

	/* Reset the timer */
	mod_timer(&adapter->watchdog_timer, jiffies + 2 * HZ);
}

#define E1000_TX_FLAGS_CSUM		0x00000001
#define E1000_TX_FLAGS_VLAN		0x00000002
#define E1000_TX_FLAGS_TSO		0x00000004
#define E1000_TX_FLAGS_VLAN_MASK	0xffff0000
#define E1000_TX_FLAGS_VLAN_SHIFT	16



#define E1000_MAX_TXD_PWR	12
#define E1000_MAX_DATA_PER_TXD	(1<<E1000_MAX_TXD_PWR)

static inline int
e1000_tx_map(struct e1000_adapter *adapter, struct sk_buff *skb,
	unsigned int first)
{
	struct e1000_desc_ring *tx_ring = &adapter->tx_ring;
	struct e1000_buffer *buffer_info;
	int len = skb->len;
	unsigned int offset = 0, size, count = 0, i;

	unsigned int f;

	i = tx_ring->next_to_use;

	while(len) {
		buffer_info = &tx_ring->buffer_info[i];
		size = min(len, E1000_MAX_DATA_PER_TXD);
		buffer_info->length = size;
		buffer_info->dma =
			pci_map_single(adapter->pdev,
				skb->data + offset,
				size,
				PCI_DMA_TODEVICE);
		buffer_info->time_stamp = jiffies;

		len -= size;
		offset += size;
		count++;
		if(++i == tx_ring->count) i = 0;
	}

	i = (i == 0) ? tx_ring->count - 1 : i - 1;
	tx_ring->buffer_info[i].skb = skb;
	tx_ring->buffer_info[first].next_to_watch = i;

	return count;
}

static inline void
e1000_tx_queue(struct e1000_adapter *adapter, int count, int tx_flags)
{
	struct e1000_desc_ring *tx_ring = &adapter->tx_ring;
	struct e1000_tx_desc *tx_desc = NULL;
	struct e1000_buffer *buffer_info;
	uint32_t txd_upper = 0, txd_lower = E1000_TXD_CMD_IFCS;
	unsigned int i;

	if(tx_flags & E1000_TX_FLAGS_TSO) {
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D |
		             E1000_TXD_CMD_TSE;
		txd_upper |= (E1000_TXD_POPTS_IXSM | E1000_TXD_POPTS_TXSM) << 8;
	}

	if(tx_flags & E1000_TX_FLAGS_CSUM) {
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D;
		txd_upper |= E1000_TXD_POPTS_TXSM << 8;
	}

	if(tx_flags & E1000_TX_FLAGS_VLAN) {
		txd_lower |= E1000_TXD_CMD_VLE;
		txd_upper |= (tx_flags & E1000_TX_FLAGS_VLAN_MASK);
	}

	i = tx_ring->next_to_use;

	while(count--) {
		buffer_info = &tx_ring->buffer_info[i];
		tx_desc = E1000_TX_DESC(*tx_ring, i);
		tx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);
		tx_desc->lower.data =
			cpu_to_le32(txd_lower | buffer_info->length);
		tx_desc->upper.data = cpu_to_le32(txd_upper);
		if(++i == tx_ring->count) i = 0;
	}

	tx_desc->lower.data |= cpu_to_le32(adapter->txd_cmd);

	/* Force memory writes to complete before letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable for weak-ordered memory model archs,
	 * such as IA-64). */
	wmb();

	tx_ring->next_to_use = i;
	E1000_WRITE_REG(&adapter->hw, TDT, i);
}

/**
 * 82547 workaround to avoid controller hang in half-duplex environment.
 * The workaround is to avoid queuing a large packet that would span
 * the internal Tx FIFO ring boundary by notifying the stack to resend
 * the packet at a later time.  This gives the Tx FIFO an opportunity to
 * flush all packets.  When that occurs, we reset the Tx FIFO pointers
 * to the beginning of the Tx FIFO.
 **/

#define E1000_FIFO_HDR			0x10
#define E1000_82547_PAD_LEN		0x3E0

static inline int
e1000_82547_fifo_workaround(struct e1000_adapter *adapter, struct sk_buff *skb)
{
	uint32_t fifo_space = adapter->tx_fifo_size - adapter->tx_fifo_head;
	uint32_t skb_fifo_len = skb->len + E1000_FIFO_HDR;

	E1000_ROUNDUP(skb_fifo_len, E1000_FIFO_HDR);

	if(adapter->link_duplex != HALF_DUPLEX)
		goto no_fifo_stall_required;

	if(atomic_read(&adapter->tx_fifo_stall))
		return 1;

	if(skb_fifo_len >= (E1000_82547_PAD_LEN + fifo_space)) {
		atomic_set(&adapter->tx_fifo_stall, 1);
		return 1;
	}

no_fifo_stall_required:
	adapter->tx_fifo_head += skb_fifo_len;
	if(adapter->tx_fifo_head >= adapter->tx_fifo_size)
		adapter->tx_fifo_head -= adapter->tx_fifo_size;
	return 0;
}

/* Tx Descriptors needed, worst case */
#define TXD_USE_COUNT(S) (((S) >> E1000_MAX_TXD_PWR) + \
			 (((S) & (E1000_MAX_DATA_PER_TXD - 1)) ? 1 : 0))
#define DESC_NEEDED TXD_USE_COUNT(MAX_JUMBO_FRAME_SIZE) + \
	MAX_SKB_FRAGS * TXD_USE_COUNT(PAGE_SIZE) + 1

static int
e1000_xmit_frame(struct sk_buff *skb, struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev->priv;
	unsigned int first;
	unsigned int tx_flags = 0;

	if(skb->len <= 0) {
		dev_kfree_skb_any(skb);
		return 0;
	}

	if(E1000_DESC_UNUSED(&adapter->tx_ring) < DESC_NEEDED) {
		netif_stop_queue(netdev);
		return 1;
	}

	if(adapter->hw.mac_type == e1000_82547) {
		if(e1000_82547_fifo_workaround(adapter, skb)) {
			netif_stop_queue(netdev);
			mod_timer(&adapter->tx_fifo_stall_timer, jiffies);
			return 1;
		}
	}


	first = adapter->tx_ring.next_to_use;
#if 0	
	if(e1000_tso(adapter, skb))
		tx_flags |= E1000_TX_FLAGS_TSO;
	else if(e1000_tx_csum(adapter, skb))
		tx_flags |= E1000_TX_FLAGS_CSUM;
#endif
	e1000_tx_queue(adapter, e1000_tx_map(adapter, skb, first), tx_flags);

	netdev->trans_start = jiffies;

	return 0;
}

/**
 * e1000_tx_timeout - Respond to a Tx Hang
 * @netdev: network interface device structure
 **/

static void
e1000_tx_timeout(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev->priv;

	/* Do the reset outside of interrupt context */
	schedule_task(&adapter->tx_timeout_task);
}

static void
e1000_tx_timeout_task(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev->priv;

	netif_device_detach(netdev);
	e1000_down(adapter);
	e1000_up(adapter);
	netif_device_attach(netdev);
}

/**
 * e1000_get_stats - Get System Network Statistics
 * @netdev: network interface device structure
 *
 * Returns the address of the device statistics structure.
 * The statistics are actually updated from the timer callback.
 **/

static struct net_device_stats *
e1000_get_stats(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev->priv;

	return &adapter->net_stats;
}

/**
 * e1000_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network interface device structure
 * @new_mtu: new value for maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/

static int
e1000_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct e1000_adapter *adapter = netdev->priv;
	int old_mtu = adapter->rx_buffer_len;
	int max_frame = new_mtu + ENET_HEADER_SIZE + ETHERNET_FCS_SIZE;

	if((max_frame < MINIMUM_ETHERNET_FRAME_SIZE) ||
	   (max_frame > MAX_JUMBO_FRAME_SIZE)) {
		E1000_ERR("Invalid MTU setting\n");
		return -EINVAL;
	}

	if(max_frame <= MAXIMUM_ETHERNET_FRAME_SIZE) {
		adapter->rx_buffer_len = E1000_RXBUFFER_2048;

	} else if(adapter->hw.mac_type < e1000_82543) {
		E1000_ERR("Jumbo Frames not supported on 82542\n");
		return -EINVAL;

	} else if(max_frame <= E1000_RXBUFFER_4096) {
		adapter->rx_buffer_len = E1000_RXBUFFER_4096;

	} else if(max_frame <= E1000_RXBUFFER_8192) {
		adapter->rx_buffer_len = E1000_RXBUFFER_8192;

	} else {
		adapter->rx_buffer_len = E1000_RXBUFFER_16384;
	}

	if(old_mtu != adapter->rx_buffer_len && netif_running(netdev)) {

		e1000_down(adapter);
		e1000_up(adapter);
	}

	netdev->mtu = new_mtu;
	adapter->hw.max_frame_size = max_frame;

	return 0;
}

/**
 * e1000_update_stats - Update the board statistics counters
 * @adapter: board private structure
 **/

static void
e1000_update_stats(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	unsigned long flags;
	uint16_t phy_tmp;

#define PHY_IDLE_ERROR_COUNT_MASK 0x00FF

	spin_lock_irqsave(&adapter->stats_lock, flags);

	/* these counters are modified from e1000_adjust_tbi_stats,
	 * called from the interrupt context, so they must only
	 * be written while holding adapter->stats_lock
	 */

	adapter->stats.crcerrs += E1000_READ_REG(hw, CRCERRS);
	adapter->stats.gprc += E1000_READ_REG(hw, GPRC);
	adapter->gorcl = E1000_READ_REG(hw, GORCL);
	adapter->stats.gorcl += adapter->gorcl;
	adapter->stats.gorch += E1000_READ_REG(hw, GORCH);
	adapter->stats.bprc += E1000_READ_REG(hw, BPRC);
	adapter->stats.mprc += E1000_READ_REG(hw, MPRC);
	adapter->stats.roc += E1000_READ_REG(hw, ROC);
	adapter->stats.prc64 += E1000_READ_REG(hw, PRC64);
	adapter->stats.prc127 += E1000_READ_REG(hw, PRC127);
	adapter->stats.prc255 += E1000_READ_REG(hw, PRC255);
	adapter->stats.prc511 += E1000_READ_REG(hw, PRC511);
	adapter->stats.prc1023 += E1000_READ_REG(hw, PRC1023);
	adapter->stats.prc1522 += E1000_READ_REG(hw, PRC1522);

	spin_unlock_irqrestore(&adapter->stats_lock, flags);

	/* the rest of the counters are only modified here */

	adapter->stats.symerrs += E1000_READ_REG(hw, SYMERRS);
	adapter->stats.mpc += E1000_READ_REG(hw, MPC);
	adapter->stats.scc += E1000_READ_REG(hw, SCC);
	adapter->stats.ecol += E1000_READ_REG(hw, ECOL);
	adapter->stats.mcc += E1000_READ_REG(hw, MCC);
	adapter->stats.latecol += E1000_READ_REG(hw, LATECOL);
	adapter->stats.dc += E1000_READ_REG(hw, DC);
	adapter->stats.sec += E1000_READ_REG(hw, SEC);
	adapter->stats.rlec += E1000_READ_REG(hw, RLEC);
	adapter->stats.xonrxc += E1000_READ_REG(hw, XONRXC);
	adapter->stats.xontxc += E1000_READ_REG(hw, XONTXC);
	adapter->stats.xoffrxc += E1000_READ_REG(hw, XOFFRXC);
	adapter->stats.xofftxc += E1000_READ_REG(hw, XOFFTXC);
	adapter->stats.fcruc += E1000_READ_REG(hw, FCRUC);
	adapter->stats.gptc += E1000_READ_REG(hw, GPTC);
	adapter->gotcl = E1000_READ_REG(hw, GOTCL);
	adapter->stats.gotcl += adapter->gotcl;
	adapter->stats.gotch += E1000_READ_REG(hw, GOTCH);
	adapter->stats.rnbc += E1000_READ_REG(hw, RNBC);
	adapter->stats.ruc += E1000_READ_REG(hw, RUC);
	adapter->stats.rfc += E1000_READ_REG(hw, RFC);
	adapter->stats.rjc += E1000_READ_REG(hw, RJC);
	adapter->stats.torl += E1000_READ_REG(hw, TORL);
	adapter->stats.torh += E1000_READ_REG(hw, TORH);
	adapter->stats.totl += E1000_READ_REG(hw, TOTL);
	adapter->stats.toth += E1000_READ_REG(hw, TOTH);
	adapter->stats.tpr += E1000_READ_REG(hw, TPR);
	adapter->stats.ptc64 += E1000_READ_REG(hw, PTC64);
	adapter->stats.ptc127 += E1000_READ_REG(hw, PTC127);
	adapter->stats.ptc255 += E1000_READ_REG(hw, PTC255);
	adapter->stats.ptc511 += E1000_READ_REG(hw, PTC511);
	adapter->stats.ptc1023 += E1000_READ_REG(hw, PTC1023);
	adapter->stats.ptc1522 += E1000_READ_REG(hw, PTC1522);
	adapter->stats.mptc += E1000_READ_REG(hw, MPTC);
	adapter->stats.bptc += E1000_READ_REG(hw, BPTC);

	/* used for adaptive IFS */

	hw->tx_packet_delta = E1000_READ_REG(hw, TPT);
	adapter->stats.tpt += hw->tx_packet_delta;
	hw->collision_delta = E1000_READ_REG(hw, COLC);
	adapter->stats.colc += hw->collision_delta;

	if(hw->mac_type >= e1000_82543) {
		adapter->stats.algnerrc += E1000_READ_REG(hw, ALGNERRC);
		adapter->stats.rxerrc += E1000_READ_REG(hw, RXERRC);
		adapter->stats.tncrs += E1000_READ_REG(hw, TNCRS);
		adapter->stats.cexterr += E1000_READ_REG(hw, CEXTERR);
		adapter->stats.tsctc += E1000_READ_REG(hw, TSCTC);
		adapter->stats.tsctfc += E1000_READ_REG(hw, TSCTFC);
	}

	/* Fill out the OS statistics structure */

	adapter->net_stats.rx_packets = adapter->stats.gprc;
	adapter->net_stats.tx_packets = adapter->stats.gptc;
	adapter->net_stats.rx_bytes = adapter->stats.gorcl;
	adapter->net_stats.tx_bytes = adapter->stats.gotcl;
	adapter->net_stats.multicast = adapter->stats.mprc;
	adapter->net_stats.collisions = adapter->stats.colc;

	/* Rx Errors */

	adapter->net_stats.rx_errors = adapter->stats.rxerrc +
		adapter->stats.crcerrs + adapter->stats.algnerrc +
		adapter->stats.rlec + adapter->stats.rnbc +
		adapter->stats.mpc + adapter->stats.cexterr;
	adapter->net_stats.rx_dropped = adapter->stats.rnbc;
	adapter->net_stats.rx_length_errors = adapter->stats.rlec;
	adapter->net_stats.rx_crc_errors = adapter->stats.crcerrs;
	adapter->net_stats.rx_frame_errors = adapter->stats.algnerrc;
	adapter->net_stats.rx_fifo_errors = adapter->stats.mpc;
	adapter->net_stats.rx_missed_errors = adapter->stats.mpc;

	/* Tx Errors */

	adapter->net_stats.tx_errors = adapter->stats.ecol +
	                               adapter->stats.latecol;
	adapter->net_stats.tx_aborted_errors = adapter->stats.ecol;
	adapter->net_stats.tx_window_errors = adapter->stats.latecol;
	adapter->net_stats.tx_carrier_errors = adapter->stats.tncrs;

	/* Tx Dropped needs to be maintained elsewhere */

	/* Phy Stats */

	if(hw->media_type == e1000_media_type_copper) {
		if((adapter->link_speed == SPEED_1000) &&
		   (!e1000_read_phy_reg(hw, PHY_1000T_STATUS, &phy_tmp))) {
			phy_tmp &= PHY_IDLE_ERROR_COUNT_MASK;
			adapter->phy_stats.idle_errors += phy_tmp;
		}

		if((hw->mac_type <= e1000_82546) &&
		   (hw->phy_type == e1000_phy_m88) &&
		   !e1000_read_phy_reg(hw, M88E1000_RX_ERR_CNTR, &phy_tmp))
			adapter->phy_stats.receive_errors += phy_tmp;
	}
#ifdef PMON
{
	struct net_device *sc = adapter->netdev;
	struct ifnet *ifp = &sc->sc_if;

	ifp->if_ipackets = adapter->net_stats.rx_packets;
	ifp->if_opackets = adapter->net_stats.tx_packets;
	ifp->if_collisions = adapter->net_stats.collisions;
	ifp->if_ierrors = adapter->net_stats.rx_errors;
	ifp->if_oerrors = adapter->net_stats.tx_errors;
	ifp->if_ibytes = adapter->net_stats.rx_bytes;
	ifp->if_obytes = adapter->net_stats.tx_bytes;
}
#endif
}

/**
 * e1000_irq_disable - Mask off interrupt generation on the NIC
 * @adapter: board private structure
 **/

static inline void
e1000_irq_disable(struct e1000_adapter *adapter)
{
	atomic_inc(&adapter->irq_sem);
	E1000_WRITE_REG(&adapter->hw, IMC, ~0);
	E1000_WRITE_FLUSH(&adapter->hw);
	synchronize_irq();
}

/**
 * e1000_irq_enable - Enable default interrupt generation settings
 * @adapter: board private structure
 **/

static inline void
e1000_irq_enable(struct e1000_adapter *adapter)
{
	if(atomic_dec_and_test(&adapter->irq_sem)) {
		E1000_WRITE_REG(&adapter->hw, IMS, IMS_ENABLE_MASK);
		E1000_WRITE_FLUSH(&adapter->hw);
	}
}

/**
 * e1000_intr - Interrupt Handler
 * @irq: interrupt number
 * @data: pointer to a network interface device structure
 * @pt_regs: CPU registers structure
 **/

static void
e1000_intr(int irq, void *data, struct pt_regs *regs)
{
	struct net_device *netdev = data;
	struct e1000_adapter *adapter = netdev->priv;
	uint32_t icr = E1000_READ_REG(&adapter->hw, ICR);
#ifndef CONFIG_E1000_NAPI
	unsigned int i;
#endif

	if(!icr)
		return;  /* Not our interrupt */

	if(icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC)) {
		adapter->hw.get_link_status = 1;
		mod_timer(&adapter->watchdog_timer, jiffies);
	}

#ifdef CONFIG_E1000_NAPI
	if(netif_rx_schedule_prep(netdev)) {

		/* Disable interrupts and register for poll. The flush 
		  of the posted write is intentionally left out.
		*/

		atomic_inc(&adapter->irq_sem);
		E1000_WRITE_REG(&adapter->hw, IMC, ~0);
		__netif_rx_schedule(netdev);
	}
#else
	for(i = 0; i < E1000_MAX_INTR; i++)
		if(!e1000_clean_rx_irq(adapter) &
		   !e1000_clean_tx_irq(adapter))
			break;
#endif
}

#ifdef CONFIG_E1000_NAPI
/**
 * e1000_clean - NAPI Rx polling callback
 * @adapter: board private structure
 **/

static int
e1000_clean(struct net_device *netdev, int *budget)
{
	struct e1000_adapter *adapter = netdev->priv;
	int work_to_do = min(*budget, netdev->quota);
	int work_done = 0;
	
	e1000_clean_tx_irq(adapter);
	e1000_clean_rx_irq(adapter, &work_done, work_to_do);

	*budget -= work_done;
	netdev->quota -= work_done;
	
	if(work_done < work_to_do) {
		netif_rx_complete(netdev);
		e1000_irq_enable(adapter);
	}

	return (work_done >= work_to_do);
}
#endif

/**
 * e1000_clean_tx_irq - Reclaim resources after transmit completes
 * @adapter: board private structure
 **/

static boolean_t
e1000_clean_tx_irq(struct e1000_adapter *adapter)
{
	struct e1000_desc_ring *tx_ring = &adapter->tx_ring;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_tx_desc *tx_desc, *eop_desc;
	struct e1000_buffer *buffer_info;
	unsigned int i, eop;
	boolean_t cleaned = FALSE;

	i = tx_ring->next_to_clean;
	eop = tx_ring->buffer_info[i].next_to_watch;
	eop_desc = E1000_TX_DESC(*tx_ring, eop);

	while(eop_desc->upper.data & cpu_to_le32(E1000_TXD_STAT_DD)) {

		for(cleaned = FALSE; !cleaned; ) {
			tx_desc = E1000_TX_DESC(*tx_ring, i);
			buffer_info = &tx_ring->buffer_info[i];

			if(buffer_info->dma) {

				pci_unmap_page(pdev,
					       buffer_info->dma,
					       buffer_info->length,
					       PCI_DMA_TODEVICE);

				buffer_info->dma = 0;
			}

			if(buffer_info->skb) {

				dev_kfree_skb_any(buffer_info->skb);

				buffer_info->skb = NULL;
			}

			tx_desc->buffer_addr = 0;
			tx_desc->lower.data = 0;
			tx_desc->upper.data = 0;

			cleaned = (i == eop);
			if(++i == tx_ring->count) i = 0;
		}
		
		eop = tx_ring->buffer_info[i].next_to_watch;
		eop_desc = E1000_TX_DESC(*tx_ring, eop);
	}

	tx_ring->next_to_clean = i;

	if(cleaned && netif_queue_stopped(netdev) && netif_carrier_ok(netdev))
		netif_wake_queue(netdev);

	return cleaned;
}

/**
 * e1000_clean_rx_irq - Send received data up the network stack,
 * @adapter: board private structure
 **/

static boolean_t
#ifdef CONFIG_E1000_NAPI
e1000_clean_rx_irq(struct e1000_adapter *adapter, int *work_done,
                   int work_to_do)
#else
e1000_clean_rx_irq(struct e1000_adapter *adapter)
#endif
{
	struct e1000_desc_ring *rx_ring = &adapter->rx_ring;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_rx_desc *rx_desc;
	struct e1000_buffer *buffer_info;
	struct sk_buff *skb;
	unsigned long flags;
	uint32_t length;
	uint8_t last_byte;
	unsigned int i;
	boolean_t cleaned = FALSE;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC(*rx_ring, i);

	while(rx_desc->status & E1000_RXD_STAT_DD) {
		buffer_info = &rx_ring->buffer_info[i];

#ifdef CONFIG_E1000_NAPI
		if(*work_done >= work_to_do)
			break;

		(*work_done)++;
#endif

		cleaned = TRUE;

		pci_unmap_single(pdev,
		                 buffer_info->dma,
		                 buffer_info->length,
		                 PCI_DMA_FROMDEVICE);

		skb = buffer_info->skb;
		length = le16_to_cpu(rx_desc->length);
		//printf("rx_desc=%x,length=%d\n",rx_desc,length);

		if(!(rx_desc->status & E1000_RXD_STAT_EOP)) {

			/* All receives must fit into a single buffer */

			E1000_DBG("Receive packet consumed multiple buffers\n");

			dev_kfree_skb_irq(skb);
			rx_desc->status = 0;
			buffer_info->skb = NULL;

			if(++i == rx_ring->count) i = 0;

			rx_desc = E1000_RX_DESC(*rx_ring, i);
			continue;
		}

		if(rx_desc->errors & E1000_RXD_ERR_FRAME_ERR_MASK) {

			last_byte = *(skb->data + length - 1);

			if(TBI_ACCEPT(&adapter->hw, rx_desc->status,
			              rx_desc->errors, length, last_byte)) {

				spin_lock_irqsave(&adapter->stats_lock, flags);

				e1000_tbi_adjust_stats(&adapter->hw,
				                       &adapter->stats,
				                       length, skb->data);

				spin_unlock_irqrestore(&adapter->stats_lock,
				                       flags);
				length--;
			} else {

				dev_kfree_skb_irq(skb);
				rx_desc->status = 0;
				buffer_info->skb = NULL;

				if(++i == rx_ring->count) i = 0;

				rx_desc = E1000_RX_DESC(*rx_ring, i);
				continue;
			}
		}

		/* Good Receive */
		skb_put(skb, length - ETHERNET_FCS_SIZE);

		/* Receive Checksum Offload */
		//e1000_rx_checksum(adapter, rx_desc, skb);

		skb->protocol = eth_type_trans(skb, netdev);

			netif_rx(skb);

		netdev->last_rx = jiffies;

		rx_desc->status = 0;
		buffer_info->skb = NULL;

		if(++i == rx_ring->count) i = 0;

		rx_desc = E1000_RX_DESC(*rx_ring, i);
	}

	rx_ring->next_to_clean = i;

	e1000_alloc_rx_buffers(adapter);
	return cleaned;
}

/**
 * e1000_alloc_rx_buffers - Replace used receive buffers
 * @data: address of board private structure
 **/

static void
e1000_alloc_rx_buffers(struct e1000_adapter *adapter)
{
	struct e1000_desc_ring *rx_ring = &adapter->rx_ring;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_rx_desc *rx_desc;
	struct e1000_buffer *buffer_info;
	struct sk_buff *skb;
	int reserve_len = 2;
	unsigned int i;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	while(!buffer_info->skb) {
		rx_desc = E1000_RX_DESC(*rx_ring, i);

		skb = dev_alloc_skb(adapter->rx_buffer_len + reserve_len);

		if(!skb) {
			/* Better luck next round */
			break;
		}

		/* Make buffer alignment 2 beyond a 16 byte boundary
		 * this will result in a 16 byte aligned IP header after
		 * the 14 byte MAC header is removed
		 */
		skb_reserve(skb, reserve_len);

		skb->dev = netdev;

		buffer_info->skb = skb;
		buffer_info->length = adapter->rx_buffer_len;
		buffer_info->dma =
			pci_map_single(pdev,
			               skb->data,
			               adapter->rx_buffer_len,
			               PCI_DMA_FROMDEVICE);

		rx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);

		if((i & ~(E1000_RX_BUFFER_WRITE - 1)) == i) {
			/* Force memory writes to complete before letting h/w
			 * know there are new descriptors to fetch.  (Only
			 * applicable for weak-ordered memory model archs,
			 * such as IA-64). */
			wmb();

			E1000_WRITE_REG(&adapter->hw, RDT, i);
		}

		if(++i == rx_ring->count) i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	}

	rx_ring->next_to_use = i;
}

/**
 * e1000_smartspeed - Workaround for SmartSpeed on 82541 and 82547 controllers.
 * @adapter:
 **/

static void
e1000_smartspeed(struct e1000_adapter *adapter)
{
	uint16_t phy_status;
	uint16_t phy_ctrl;

	if((adapter->hw.phy_type != e1000_phy_igp) || !adapter->hw.autoneg ||
	   !(adapter->hw.autoneg_advertised & ADVERTISE_1000_FULL))
		return;

	if(adapter->smartspeed == 0) {
		/* If Master/Slave config fault is asserted twice,
		 * we assume back-to-back */
		e1000_read_phy_reg(&adapter->hw, PHY_1000T_STATUS, &phy_status);
		if(!(phy_status & SR_1000T_MS_CONFIG_FAULT)) return;
		e1000_read_phy_reg(&adapter->hw, PHY_1000T_STATUS, &phy_status);
		if(!(phy_status & SR_1000T_MS_CONFIG_FAULT)) return;
		e1000_read_phy_reg(&adapter->hw, PHY_1000T_CTRL, &phy_ctrl);
		if(phy_ctrl & CR_1000T_MS_ENABLE) {
			phy_ctrl &= ~CR_1000T_MS_ENABLE;
			e1000_write_phy_reg(&adapter->hw, PHY_1000T_CTRL,
					    phy_ctrl);
			adapter->smartspeed++;
			if(!e1000_phy_setup_autoneg(&adapter->hw) &&
			   !e1000_read_phy_reg(&adapter->hw, PHY_CTRL,
				   	       &phy_ctrl)) {
				phy_ctrl |= (MII_CR_AUTO_NEG_EN |
					     MII_CR_RESTART_AUTO_NEG);
				e1000_write_phy_reg(&adapter->hw, PHY_CTRL,
						    phy_ctrl);
			}
		}
		return;
	} else if(adapter->smartspeed == E1000_SMARTSPEED_DOWNSHIFT) {
		/* If still no link, perhaps using 2/3 pair cable */
		e1000_read_phy_reg(&adapter->hw, PHY_1000T_CTRL, &phy_ctrl);
		phy_ctrl |= CR_1000T_MS_ENABLE;
		e1000_write_phy_reg(&adapter->hw, PHY_1000T_CTRL, phy_ctrl);
		if(!e1000_phy_setup_autoneg(&adapter->hw) &&
		   !e1000_read_phy_reg(&adapter->hw, PHY_CTRL, &phy_ctrl)) {
			phy_ctrl |= (MII_CR_AUTO_NEG_EN |
				     MII_CR_RESTART_AUTO_NEG);
			e1000_write_phy_reg(&adapter->hw, PHY_CTRL, phy_ctrl);
		}
	}
	/* Restart process after E1000_SMARTSPEED_MAX iterations */
	if(adapter->smartspeed++ == E1000_SMARTSPEED_MAX)
		adapter->smartspeed = 0;
}

int e1000_ethtool_ioctl(struct net_device *netdev, struct ifreq *ifr)
	{
		return -EOPNOTSUPP;
	}

/**
 * e1000_ioctl -
 * @netdev:
 * @ifreq:
 * @cmd:
 **/

static int
e1000_ioctl(struct net_device *netdev, struct ifreq *ifr, int cmd)
{
		return -EOPNOTSUPP;
}

#if 0
/**
 * e1000_rx_checksum - Receive Checksum Offload for 82543
 * @adapter: board private structure
 * @rx_desc: receive descriptor
 * @sk_buff: socket buffer with received data
 **/

static inline void
e1000_rx_checksum(struct e1000_adapter *adapter,
                  struct e1000_rx_desc *rx_desc,
                  struct sk_buff *skb)
{
	/* 82543 or newer only */
	if((adapter->hw.mac_type < e1000_82543) ||
	/* Ignore Checksum bit is set */
	(rx_desc->status & E1000_RXD_STAT_IXSM) ||
	/* TCP Checksum has not been calculated */
	(!(rx_desc->status & E1000_RXD_STAT_TCPCS))) {
		skb->ip_summed = CHECKSUM_NONE;
		return;
	}

	/* At this point we know the hardware did the TCP checksum */
	/* now look at the TCP checksum error bit */
	if(rx_desc->errors & E1000_RXD_ERR_TCPE) {
		/* let the stack verify checksum errors */
		skb->ip_summed = CHECKSUM_NONE;
		adapter->hw_csum_err++;
	} else {
	/* TCP checksum is good */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		adapter->hw_csum_good++;
	}
}
#endif

void
e1000_pci_set_mwi(struct e1000_hw *hw)
{
	struct e1000_adapter *adapter = hw->back;

	pci_set_mwi(adapter->pdev);
}

void
e1000_pci_clear_mwi(struct e1000_hw *hw)
{
	struct e1000_adapter *adapter = hw->back;

	pci_clear_mwi(adapter->pdev);
}

void
e1000_read_pci_cfg(struct e1000_hw *hw, uint32_t reg, uint16_t *value)
{
	struct e1000_adapter *adapter = hw->back;

	pci_read_config_word(adapter->pdev, reg, value);
}

void
e1000_write_pci_cfg(struct e1000_hw *hw, uint32_t reg, uint16_t *value)
{
	struct e1000_adapter *adapter = hw->back;

	pci_write_config_word(adapter->pdev, reg, *value);
}

uint32_t
e1000_io_read(struct e1000_hw *hw, uint32_t port)
{
	return inl(port);
}

void
e1000_io_write(struct e1000_hw *hw, uint32_t port, uint32_t value)
{
#ifdef PMON
	outl(port,value);
#else
	outl(value, port);
#endif
}







static int
e1000_suspend(struct pci_dev *pdev, uint32_t state)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct e1000_adapter *adapter = netdev->priv;
	uint32_t ctrl, ctrl_ext, rctl, manc, status;
	uint32_t wufc = adapter->wol;

	netif_device_detach(netdev);

	if(netif_running(netdev))
		e1000_down(adapter);

	status = E1000_READ_REG(&adapter->hw, STATUS);
	if(status & E1000_STATUS_LU)
		wufc &= ~E1000_WUFC_LNKC;

	if(wufc) {
		e1000_setup_rctl(adapter);
		e1000_set_multi(netdev);

		/* turn on all-multi mode if wake on multicast is enabled */
		if(adapter->wol & E1000_WUFC_MC) {
			rctl = E1000_READ_REG(&adapter->hw, RCTL);
			rctl |= E1000_RCTL_MPE;
			E1000_WRITE_REG(&adapter->hw, RCTL, rctl);
		}

		if(adapter->hw.mac_type >= e1000_82540) {
			ctrl = E1000_READ_REG(&adapter->hw, CTRL);
			/* advertise wake from D3Cold */
			#define E1000_CTRL_ADVD3WUC 0x00100000
			/* phy power management enable */
			#define E1000_CTRL_EN_PHY_PWR_MGMT 0x00200000
			ctrl |= E1000_CTRL_ADVD3WUC |
				E1000_CTRL_EN_PHY_PWR_MGMT;
			E1000_WRITE_REG(&adapter->hw, CTRL, ctrl);
		}

		if(adapter->hw.media_type == e1000_media_type_fiber) {
			/* keep the laser running in D3 */
			ctrl_ext = E1000_READ_REG(&adapter->hw, CTRL_EXT);
			ctrl_ext |= E1000_CTRL_EXT_SDP7_DATA;
			E1000_WRITE_REG(&adapter->hw, CTRL_EXT, ctrl_ext);
		}

		E1000_WRITE_REG(&adapter->hw, WUC, E1000_WUC_PME_EN);
		E1000_WRITE_REG(&adapter->hw, WUFC, wufc);
		pci_enable_wake(pdev, 3, 1);
		pci_enable_wake(pdev, 4, 1); /* 4 == D3 cold */
	} else {
		E1000_WRITE_REG(&adapter->hw, WUC, 0);
		E1000_WRITE_REG(&adapter->hw, WUFC, 0);
		pci_enable_wake(pdev, 3, 0);
		pci_enable_wake(pdev, 4, 0); /* 4 == D3 cold */
	}

	pci_save_state(pdev, adapter->pci_state);

	if(adapter->hw.mac_type >= e1000_82540) {
		manc = E1000_READ_REG(&adapter->hw, MANC);
		if(manc & E1000_MANC_SMBUS_EN) {
			manc |= E1000_MANC_ARP_EN;
			E1000_WRITE_REG(&adapter->hw, MANC, manc);
			pci_enable_wake(pdev, 3, 1);
			pci_enable_wake(pdev, 4, 1); /* 4 == D3 cold */
		}
	}

	state = (state > 0) ? 3 : 0;
	pci_set_power_state(pdev, state);

	return 0;
}

#ifndef PMON
#include "e1000_linux.c"
#endif

/* e1000_main.c */
