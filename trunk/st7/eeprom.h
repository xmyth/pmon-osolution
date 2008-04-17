#ifndef __EEPROM_H__
#define __EEPROM_H__
extern unsigned char crc8_calc(unsigned char val, unsigned char *ptr, int length);
extern unsigned char crc8_verify(unsigned char *ptr, int length, unsigned char check_sum);


typedef enum {
	PM_STATUS_POWEROFF = 0,
	PM_STATUS_POWERON,
	PM_STATUS_RUNNING,
	PM_STATUS_STR,
	PM_STATUS_STD,
	PM_STATUS_ABNORMAL
} PM_STATUS;

DEF_8BIT_REG_AT(E_EEPROM_START, 0x1000);
DEF_8BIT_REG_AT(E_VENDOR_ID, 0x1000);
DEF_8BIT_REG_AT(E_VERSION, 0x1001);
DEF_8BIT_REG_AT(E_LENGTH, 0x1002
DEF_8BIT_REG_AT(E_PM_STATUS, 0x1003);
DEF_8BIT_REG_AT(E_CHECK_SUM, 0x1004);

#endif
