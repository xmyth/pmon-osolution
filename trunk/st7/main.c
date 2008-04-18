/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "ST7FLI49MK1T6.h"
#include "common.h"
#include "eeprom.h"


extern void sys_init(void);
extern void sys_power(PM_STATUS status);

unsigned char lt2_rtc_count = 0;
unsigned char t_sec = 0;
unsigned char pwrbtn_pressed = 0;

PM_STATUS g_traped = PM_STATUS_NULL;

main()
{
	sys_init();
	while (1);
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
	
	if (eeprom_init() == PM_STATUS_ABNORMAL) {
		g_traped = PM_STATUS_POWERON;
	} else {
		g_traped = PM_STATUS_POWEROFF;
	}
	EnableInterrupts;
	Trap;
}

/*
 * interrupt 
 */
 
@interrupt void LT2_RTC_INT(void) {
	lt2_rtc_count++;
	LTCSR1;
	if (lt2_rtc_count ==250) {
		t_sec ++;
		lt2_rtc_count = 0;
	}	
}

@interrupt void PWR_PRESSED_INT(void) {
	
	PM_STATUS pm_status = PM_STATUS_NULL;
	
	if (g_traped != PM_STATUS_NULL) {
		sys_power(g_traped);
		g_traped = PM_STATUS_NULL;
		return;
	}
	
	if (pwrbtn_pressed == 0) {
		SetBit (EICR, 2);
		ClrBit (EICR, 3);
		lt2_rtc_count = 0;
		t_sec = 0;
		pwrbtn_pressed = 1;
	} else {
		ClrBit (EICR, 2);
		SetBit (EICR, 3);
		pwrbtn_pressed = 0;
		
		if (t_sec >= 5 || (t_sec == 4  && lt2_rtc_count > 0)) {
			pm_status = PM_STATUS_POWEROFF;
		} else {
			pm_status = PM_STATUS_POWERON;
		}
		
		if (pm_status != PM_STATUS_NULL && pm_status != eeprom_get_status()) {
			sys_power(pm_status);	
		}		
	}	
}

void sys_power(PM_STATUS pm_status) {
	
	if (pm_status == PM_STATUS_POWERON) {
		
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
		
	} else {
		
		ClrBit (PADR, 4);
		ClrBit (PADR, 5);
		
	}
	
	eeprom_update_status(pm_status);
}


