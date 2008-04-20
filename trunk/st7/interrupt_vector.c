/*	BASIC INTERRUPT VECTORS TABLE FOR ST7 devices
 *	Copyright (c) 2002-2005 STMicroelectronics
 */


extern void _stext();		/* startup routine */  

extern void LT2_RTC_INT(void);

extern void PWR_PRESSED_INT(void);

extern void TRAP_INT(void);

extern void I2C_INT(void);

@interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}


/* Interrupt vector table, to be linked at the address
   0xFFE0 (in ROM) */ 
void (* const _vectab[])() = {
	NonHandledInterrupt,  		/* 0xFFE0 */
	NonHandledInterrupt,			/* 0xFFE2 */
	NonHandledInterrupt,			/* 0xFFE4 */
	LT2_RTC_INT,							/* 0xFFE6 */
	I2C_INT,            			/* 0xFFE8 */
	NonHandledInterrupt,			/* 0xFFEA */
	NonHandledInterrupt,			/* 0xFFEC */
	NonHandledInterrupt,			/* 0xFFEE */
	NonHandledInterrupt,			/* 0xFFF0 */
	NonHandledInterrupt,			/* 0xFFF2 */
	PWR_PRESSED_INT,			/* 0xFFF4 */
	NonHandledInterrupt,			/* 0xFFF6 */
	NonHandledInterrupt,			/* 0xFFF8 */
	NonHandledInterrupt,			/* 0xFFFA */
	TRAP_INT,			/* Trap vector */
	_stext,			/* Reset Vector */
};
