/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "ST7FLI49MK1T6.h"
#include "common.h"
#include "eeprom.h"

extern void eeprom_init(void);
extern void eeprom_update_status(PM_STATUS);
extern void sys_poweron(void);
extern void sys_poweroff(void);
extern void sys_init(void);

PM_STATUS eeprom_get_status();

extern unsigned char g_pm_status_his;

void sys_init(void);

unsigned char lt2_rtc_count = 0;

main()
{
	sys_init();
	while (1);
}

/*
 * interrupt 
 */
 
@interrupt void LT2_RTC_INT(void) {
	lt2_rtc_count++;
	LTCSR1;
}


void sys_init(void) {

	DisableInterrupts;
	LTCSR1 = 0x30;

	eeprom_init();

	if (PM_STATUS_ABNORMAL == g_pm_status_his)
	{
		sys_poweron();
	} else {
		sys_poweroff();
	}

	EnableInterrupts;
	
}

void sys_poweron(void) {

	unsigned char i, j;
	
	SetBit (PBDDR, 6);
	SetBit (PBOR, 6);
	SetBit (PBDR, 6);

	ClrBit (PBDDR, 5);
	SetBit (PBOR, 5);

	for (i = 0; i < 255; i++)
	{
		j++;
	}

	ClrBit (PBDR, 6);

	for (i = 0; i < 255; i++)
	{
		j++;
	}
	
	SetBit (PBDR, 6);

	for (i = 0; i < 255; i++)
	{
		j++;
	}
	
	SetBit (PADDR, 4);
	SetBit (PAOR, 4);
	SetBit (PADR, 4);

	SetBit (PADDR, 5);
	SetBit (PAOR, 5);
	SetBit (PADR, 5);

	eeprom_update_status(PM_STATUS_POWERON);
}

void sys_poweroff(void) {

	ClrBit (PADR, 4);
	ClrBit (PADR, 5);
	eeprom_update_status(PM_STATUS_POWEROFF);
}


