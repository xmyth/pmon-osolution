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

/*****************************************************************************/
/***** H A R D W A R E   R E G I S T E R   B I T   D E F I N I T I O N S *****/
/*****************************************************************************/
#define ITE         0x01                           /* Interrupt enable flags */  
#define STOP        0x02                   /* Stop condition indication flag */
#define ACK         0x04                             /* I2C acknowledge flag */
#define ENGC				0x08										/* Enable General Call bit */
#define PE          0x20                           /* Peripheral enable flag */


#define	MASTER			0x01
#define	MSMODE			0x02
#define ADSL        0x04                 /* Address matched indication flage */
#define BTF         0x08                        /* Byte transfer status flag */
#define BUSY				0x10
#define TRA         0x20                           /* Interrupt enable flags */
#define ADD10				0x40
#define	EVF					0x80

#define ERR         0x16                                      /* Error flags */
#define FRI         0x40                               /* I2COAR2 FR[i] bits */


#define AF          0x10
#define BERR        0x20
#define STOPF       0x08

#endif

/*** (c) 2003   STMicroelectronics ****************** END OF FILE ************/