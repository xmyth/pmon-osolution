/******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : SMBS_hr.c
Group            : IPSW,CMG - IPDF
Author           : MCD Application Team
Date First Issued: 18/07/2003    
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. STMicroelectronics 
    SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
    DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
********************************Documentation**********************************
General Purpose - This file contains all the hardware registers of I2C

********************************Revision History*******************************
_______________________________________________________________________________
Date :18/07/2003                 Release:1.0      	  	 	       	       		      
_______________________________________________________________________________

******************************************************************************/

#include "SMBS_config.h"
			  /********************************
			   Peripherals Registers Definition
			   ********************************/                                                                                                        
#ifdef _MWERKS_                                                                  
/* I2C Hardware Registers */  
#pragma DATA_SEG SHORT I2C
  volatile unsigned char I2CCR;                      /* I2C control register */
  volatile unsigned char I2CSR1;                     /* I2C status register1 */
  volatile unsigned char I2CSR2;                     /* I2C status register2 */
  volatile unsigned char I2CCCR;               /* I2C clock control register */  
  volatile unsigned char I2COAR1;               /* I2C own address register1 */
  volatile unsigned char I2COAR2;               /* I2C own address register2 */  
  volatile unsigned char I2CDR;                         /* I2C data register */    

/* PortB mapping for testing purpose */                                                  
#pragma DATA_SEG SHORT PORTB
  volatile unsigned char PBDR;                       /* PORT B data register */          
  volatile unsigned char PBDDR;            /* PORT B data direction register */
  volatile unsigned char PBOR;                     /* PORT B option register */
  
#endif
 
/*** (c) 2003   STMicroelectronics ****************** END OF FILE ************/