/******************************************************************************
COPYRIGHT 2003 STMicroelectronics 
Source File Name : SMBS_hr.h
Group            : IPSW,CMG - IPDF
Author           : MCD Application Team
Date First Issued: 18/07/2003 
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. STMicroelectronics 
    SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
    DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
********************************Documentation**********************************
General Purpose - This file declares all the hardware registers as extern

********************************Revision History*******************************
_______________________________________________________________________________
Date :18/07/2003                  Release:1.0       	   		        	      
******************************************************************************/
#ifndef SMBS_HR_H
#define SMBS_HR_H 

#include "SMBS_config.h"
#include "ST7FLI49MK1T6.h"
/*****************************************************************************/
/***** P E R I P H E R A L S   R E G I S T E R S   D E F I N I T I O N S *****/
/*****************************************************************************/
#ifdef _COSMIC_                               
/* I2C Hardware Registers */ 
#endif


#define BIT0 1
#define BIT1 2
#define BIT2 4
#define BIT3 8
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80



/*****************************************************************************/
/***** H A R D W A R E   R E G I S T E R   B I T   D E F I N I T I O N S *****/
/*****************************************************************************/

//CCR
#define ITE         BIT0                           /* Interrupt enable flags */  
#define STOP        BIT1                   /* Stop condition indication flag */
#define ACK         BIT2                             /* I2C acknowledge flag */
#define START				BIT3		
#define ENGC				BIT4										/* Enable General Call bit */
#define PE          BIT5                           /* Peripheral enable flag */

//CSR1
#define	SB					BIT0
#define	MSMODE			BIT1
#define ADSL        BIT2                 /* Address matched indication flage */
#define BTF         BIT3                        /* Byte transfer status flag */
#define BUSY				BIT4
#define TRA         BIT5                           /* Interrupt enable flags */
#define ADD10				BIT6
#define	EVF					BIT7

//CSR2
#define GCAL				BIT0
#define BERR        BIT1
#define ARLO				BIT2 
#define STOPF       BIT3
#define AF          BIT4


//OAR2
#define FRI0        BIT6                               /* I2COAR2 FR[i] bits */

#define EVT_NONE	  0
#define EVT1				1
#define EVT2				2
#define EVT3				3
#define EVT3_1			31
#define EVT4				4

#endif

/*** (c) 2003   STMicroelectronics ****************** END OF FILE ************/