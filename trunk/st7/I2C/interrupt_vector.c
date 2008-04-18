/*
*******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : vector_264.c
Group            : IPSW,CMG-IPDF.
Author           : MCD Application Team
Date First Issued: 18/07/2003 
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. STMicroelectronics 
    SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
    DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
********************************Documentation**********************************
General Purpose - Interrupt mapping file for ST72F264
********************************RevisionHistory********************************
_______________________________________________________________________________
Date :18/07/2003                  Release:1.0
******************************************************************************/


#define NULL 0
extern void SMBS_IT_Function();
extern void I2C_INT(void);
extern void LT2_RTC2_INT(void);
extern void LT2_RTC_INT(void);

extern void _stext();

void (* const _vectab[])() = {
					NULL,  		/* 0xFFE0 */
					LT2_RTC2_INT,			        /* 0xFFE2 */
					NULL,			/* 0xFFE4 */
					LT2_RTC_INT,			        /* 0xFFE6 */
					
					I2C_INT,			/* 0xFFE8 */
					NULL,			/* 0xFFEA */
					NULL,			/* 0xFFEC */
					NULL,			/* 0xFFEE */
					NULL,			/* 0xFFF0 */
					NULL,			/* 0xFFF2 */
					NULL,			/* 0xFFF4 */
					NULL,			/* 0xFFF6 */
					NULL,			/* 0xFFF8 */
					NULL,			/* 0xFFFA */
					NULL,			/* Trap vector */
					_stext,			/* Reset Vector */
};
/******************* (c) 2003  ST Microelectronics *********** END OF FILE****/