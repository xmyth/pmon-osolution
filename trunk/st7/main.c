/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "ST7FLI49MK1T6.h"
#include "common.h"

void sys_init(void);

unsigned char lt2_rtc_count = 0;

main()
{
	sys_init();
	EnableInterrupts;
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
	LTCSR1 = 0x30;
}