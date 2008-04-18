/*
*******************************************************************************
* COPYRIGHT 2003 STMicroelectronics
* Source File Name : main.c                      
* Group            : IPSW,CMG-IPDF
* Author           : MCD Application Team
* Date First Issued: 18/07/2003        
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. STMicroelectronics 
    SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
    DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
********************************Documentation**********************************
* General Purpose - This file contains the Example program for SMBus slave 
                    driver communication for Write Word, Write Block and read 
                    word protocols. Here PEC option is not chosen. The program
                    does the following processes.
                    (i) Writes word "ST"
                    (ii) Writes block of 15 bytes
                    (iii) Reads the word sent by master. Compares it with the 
                     buffer Buff_Out3. If the received word is "abcd" then it
                     makes PB6 high to indicate that received data is correct.
                     If received data is different from "abcd" then PB7 is made
                     high and control is stuck in a while loop.
                        
********************************RevisionHistory********************************
_______________________________________________________________________________
Date : 18/07/2003     Release: 1.0
******************************************************************************/
#include "SMBS_config.h"                             /* Fcpu defined as 8MHz */
#include "SMBS_hr.h"

#include "ST7FLI49MK1T6.h"

/* --------Define Macros for bit manipulation ------------*/
#define SetBit(VAR,BIT_NUM)	( (VAR) |= (1<<(BIT_NUM)) )
#define ClrBit(VAR,BIT_NUM)	( (VAR) &= ((1<<(BIT_NUM))^0xFF) )
#define ValBit(VAR,BIT_NUM)	( (VAR) & (1<<(BIT_NUM)) )
#define BitIsClear(VAR,BIT_NUM) ( 0 == ValBit(VAR,BIT_NUM) )
#define BitIsSet(VAR,BIT_NUM)   ( !BitIsClear(VAR,BIT_NUM) )

unsigned char lt2_rtc_count = 0;
unsigned char lt2_rtc2_count = 0;
unsigned char count = 0;
unsigned char started = 0;
void main()
{       
	LTCSR1 = 0x30; 	//LTCSR1: ICIE ICF TB TB1IE TB1F 0 0 0

	LTARR = 0x0F;
	LTCSR2;         // ÐèÒªÏÈ¶ÁÒ»´ÎLTCSR2 ¼Ä´æÆ÷£¬²Å¿ÉÒÔÔÚ¿ª·¢»·¾³ÖÐÖÐ¶Ï¡£
	LTCSR2 = 0x02; 	//LTCSR2: 0 0 0 0 0 0 TB2IE TB2F
	
     ClrBit(PADDR, 6);
		 ClrBit(PADDR, 7);
		 ClrBit(PAOR, 6);
		 ClrBit(PAOR, 7);	//Floating Input	
	

			
   SetBit(PADDR, 4);
		 SetBit(PAOR, 4);
		 ClrBit (PADR, 4);
		 
		 SetBit(PADDR, 5);
		 SetBit(PAOR, 5);	
		 ClrBit (PADR, 5);



		 
		 SetBit (PBDDR, 6);
		 SetBit (PBOR, 6);
		 SetBit (PBDR, 6);
	
	
		EnableInterrupts ;                   /* Global interrupt mask disabled */

    SMBS_Init (0x25,0x40);     /* Slave address configured as 16h */
		 
		while(1)
		{
    Nop;
		Nop;
		Nop;
		Nop;
		Nop;
			};
					
     /*----------------------------------------------------------------------*/
     DisableInterrupts ;     
}                                 

/*============================== USER FUNCTIONS =============================*/
/*-----------------------------------------------------------------------------
ROUTINE NAME : SMBS_QC_UsrRoutine
INPUT        : None
OUTPUT       : None
DESCRIPTION  : Quick command user routine. Here, part of the slave address 
               denotes the command – the R/W# bit. The R/W# bit may be used to 
               simply turn a device function on or off, or enable/disable a 
               low-power standby mode. User can read I2CDR register for slave 
               address to write his/her own routine.
COMMENTS     : This function is optional.
-----------------------------------------------------------------------------*/                                 
void SMBS_QC_UsrRoutine(void)
{
     /* User can write his own routine here */
}
/******************** (c) 2003  ST Microelectronics *************END OF FILE***/        


/******************************************************************************
* Function		: LITE TIMER RTC 
* Description	: 2ms @ Fcpu = 8MHZ
* Input				: None
* Output	   	: None
* Return	   	: None	
******************************************************************************/
@interrupt void LT2_RTC_INT(void)
{
	lt2_rtc_count++;
	LTCSR1;	
	
	if (lt2_rtc_count == 100)
	{
		count++;
		lt2_rtc_count = 0;
	}
		
	 if (started == 1)
		return;
	
	if (count == 10)
	{
		ClrBit (PBDR, 6);
	} else if (count == 20)
	{
		SetBit (PBDR, 6);
  } else if (count == 30)
	{
		SetBit (PADR, 4);
		SetBit (PADR, 5);
		started = 1;
	}			

}

/******************************************************************************
* Function		: interrupt for lite timer rtc 
* Description	: One 8-bit upcounter with autoreload and programmable timebase 
								period from 4¦Ìs to 1.024ms in 4¦Ìs increments (@ 8 MHz fOSC)
* Input				: None
* Output			: None
* Return			: None	
******************************************************************************/
@interrupt void LT2_RTC2_INT(void)
{
	lt2_rtc2_count++;
	LTCSR2;															
}


/* ======================= THE END ======================================*/