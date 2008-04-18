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
unsigned char lt2_rtc_count = 0;
unsigned char t_sec = 0;
unsigned char pwr_pressed = 0;

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
	if (lt2_rtc_count ==255) {
		t_sec ++;
	}	
}

@interrupt void PWR_PRESSED_INT(void) {
	//DisableInterrupts;
	/*
	if (pwr_pressed == 0) {
		SetBit (EICR, 2);
		ClrBit (EICR, 3);
		t_sec = 0;
		pwr_pressed = 1;
	} else {
		ClrBit (EICR, 2);
		SetBit (EICR, 3);
		pwr_pressed = 0;
		
		if (t_sec > 5) {
			sys_poweroff();
		} else {
			sys_poweron();
		}
	}*/
	
	//sys_poweron();
	//EnableInterrupts;	
}

void sys_init(void) {

	DisableInterrupts;
	LTCSR1 = 0x30;
	
	SetBit (PADDR, 4);
	SetBit (PAOR, 4);
	ClrBit (PADR, 4);

	SetBit (PADDR, 5);
	SetBit (PAOR, 5);
	ClrBit (PADR, 5);

	SetBit (PBDDR, 6);
	SetBit (PBOR, 6);
	SetBit (PBDR, 6);
	
	ClrBit (PBDDR, 5);
	SetBit (PBOR, 5);
	
	ClrBit (EICR, 2);
	SetBit (EICR, 3);
	
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
	unsigned char i, j, k;	
	
	for (i = 0; i < 255; i++)
		for (j = 0; j < 255; j++)
					;

	ClrBit (PBDR, 6);

	for (i = 0; i < 255; i++)
		for (j = 0; j < 255; j++)
				;
	
	SetBit (PBDR, 6);

	for (i = 0; i < 255; i++)
		for (j = 0; j < 255; j++)
				;

	SetBit (PADR, 4);

	SetBit (PADR, 5);

	//eeprom_update_status(PM_STATUS_POWERON);

}

void sys_poweroff(void) {
	
	ClrBit (PADR, 4);
	ClrBit (PADR, 5);
	//eeprom_update_status(PM_STATUS_POWEROFF);
	
}


