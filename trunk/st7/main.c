/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "ST7FLI49MK1T6.h"
#include "common.h"
#include "eeprom.h"
#include "smbs.h"

void sys_init(void);
void sys_power(PM_STATUS status);
void notify_cpu_poweroff(void);

unsigned char lt2_rtc_count = 0;
unsigned char t_sec = 0;
unsigned char pwrbtn_pressed = 0;
unsigned char g_pwrbtn_long_pressed_poweroff = 0;

PM_STATUS g_traped_pm_status = PM_STATUS_NULL;
int g_traped_boot = 0;

main()
{
	sys_init();
	while (1);
}

void sys_init(void) {

	DisableInterrupts;
	LTCSR1 = 0x30;

  //I2C SDA CLK Setting Floating Inpu
  ClrBit(PADDR, 6);
  ClrBit(PADDR, 7);
  ClrBit(PAOR, 6);
  ClrBit(PAOR, 7);		
	
  SMBS_Init (0x25,0x40);     /* Slave address configured*/

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

	g_traped_boot = 1;
	EnableInterrupts;
	Trap;
}

/*
 * interrupt 
 */
 
@interrupt void LT2_RTC_INT(void) {
	lt2_rtc_count++;
	LTCSR1;
	if (pwrbtn_pressed == 1 && lt2_rtc_count ==250) {
		t_sec ++;
		lt2_rtc_count = 0;
		
		if (t_sec == 4 && eeprom_get_status() != PM_STATUS_POWEROFF) {
			g_pwrbtn_long_pressed_poweroff = 1;
			g_traped_pm_status = PM_STATUS_POWEROFF;
			Trap;
		}
	}	
}

@interrupt void TRAP_INT(void) {
	
	if (g_traped_boot == 1) {
		if (eeprom_init() == PM_STATUS_ABNORMAL) {
			sys_power(PM_STATUS_POWERON);
		} else {
			sys_power(PM_STATUS_POWEROFF);
		}

		g_traped_boot = 0;
		return;
	}

	if (g_traped_pm_status != PM_STATUS_NULL) {
		sys_power(g_traped_pm_status);
		g_traped_pm_status = PM_STATUS_NULL;
		return;
	}
}

@interrupt void PWR_PRESSED_INT(void) {
	
	PM_STATUS pm_status_cur;
	
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
		t_sec = 0;		
		pm_status_cur = eeprom_get_status();
		
		if (pm_status_cur == PM_STATUS_POWEROFF) {
			if (g_pwrbtn_long_pressed_poweroff != 1) {
				g_traped_pm_status = PM_STATUS_POWERON;				
			} else {
				g_pwrbtn_long_pressed_poweroff = 0;
			}
		} else if (pm_status_cur == PM_STATUS_POWERON) {
			g_traped_pm_status = PM_STATUS_POWEROFF;
		} else if (pm_status_cur == PM_STATUS_RUNNING) {
			notify_cpu_poweroff();
		}
		if (g_traped_pm_status != PM_STATUS_NULL) {
			Trap;
		}
	}	
}

void sys_power(PM_STATUS pm_status) {
	
	if (pm_status == PM_STATUS_NULL || pm_status == (PM_STATUS)E_PM_STATUS) {
		if (g_traped_boot == 0) {
			return;
		}
	}
	
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
		
	} else if (pm_status == PM_STATUS_POWEROFF) {
		
		ClrBit (PADR, 4);
		ClrBit (PADR, 5);		
	}
	
	eeprom_update_status(pm_status);
}

void notify_cpu_poweroff(void) {
}

