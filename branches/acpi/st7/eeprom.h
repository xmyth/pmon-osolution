#ifndef __EEPROM_H__
#define __EEPROM_H__

typedef enum {
	PM_STATUS_NULL = 0,
	PM_STATUS_POWEROFF,
	PM_STATUS_POWERON,
	PM_STATUS_RUNNING,
	PM_STATUS_STR,
	PM_STATUS_STD,
	PM_STATUS_ABNORMAL,
	PM_STATUS_AUTO,
	PM_STATUS_POWERON_FORCED,
	PM_STATUS_POWEROFF_PORCED,
	PM_STATUS_STR_RESUME,
	PM_STATUS_STD_RESUME
} PM_STATUS;

DEF_8BIT_REG_AT(E_EEPROM_START, 0x1000);
DEF_8BIT_REG_AT(E_VENDOR_ID, 0x1000);
DEF_8BIT_REG_AT(E_VERSION, 0x1001);
DEF_8BIT_REG_AT(E_LENGTH, 0x1002);
DEF_8BIT_REG_AT(E_PM_STATUS, 0x1003);
DEF_8BIT_REG_AT(E_PM_BOOT_CFG, 0x1004);
DEF_8BIT_REG_AT(E_CHECK_SUM, 0x1005);

extern PM_STATUS eeprom_init(void);
extern PM_STATUS eeprom_get_status(void);
extern PM_STATUS eeprom_get_cfg(void);

extern void eeprom_update_status(PM_STATUS);

#endif
