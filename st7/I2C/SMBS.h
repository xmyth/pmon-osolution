/******************************************************************************
COPYRIGHT 2001 STMicroelectronics
Source File Name : SMBS.h 
Group            : IPSW,CMG-IPDF
Author           : MCD Application Team
Date First Issued: 18/07/2003
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. STMicroelectronics 
    SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
    DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
********************************Documentation**********************************
General Purpose - Contains prototypes for all the functions of slave SMBus

********************************Revision History*******************************
_______________________________________________________________________________
Date :18/07/2003                  Release:1.0
 		        		     
******************************************************************************/
#ifndef SMBS_SLAVE_H
#define SMBS_SLAVE_H

#include "SMBS_config.h"
/*---------------------------------------------------------------------------*/
                                              /* Assignment of slave address */
typedef enum {
             SMBS_DYNMIC_ADD         = (unsigned char) 0xFF,
             SMBS_10BIT_ADD          = (unsigned char) 0xF0,
             SMBS_DEVICE_DFLT        = (unsigned char) 0xC2,
             SMBS_DFLT_ADD           = (unsigned char) 0x6E, 
             SMBS_ACCESS_HOST        = (unsigned char) 0x50,
             SMBS_ALERT_RESPONSE     = (unsigned char) 0x18,
             SMBS_HOST               = (unsigned char) 0x10,             
             SMBS_MISC               = (unsigned char) 0x04,             
             SMBS_CBUS               = (unsigned char) 0x02,
             SMBS_GCAL               = (unsigned char) 0x00
             }SMBS_Address_t;               
/*---------------------------------------------------------------------------*/	 
                  /* Description of error and status messages of slave SMBus */
typedef enum {
             SMBS_BUSY                         = (unsigned char) 0x1A,
             SMBS_TIMEOUT                      = (unsigned char) 0x18, 
             SMBS_DEVICE_ACCESS_DENIED         = (unsigned char) 0x12,
             SMBS_NOT_ACK                      = (unsigned char) 0x10,
             SMBS_UNKNOWN_FAILURE              = (unsigned char) 0x04,
             SMBS_BUS_ERROR                    = (unsigned char) 0x02,
             SMBS_OK                           = (unsigned char) 0x00
             }SMBS_ErrCode_t;               
/*---------------------------------------------------------------------------*/
                  /* Description of all the functions defined in this module */

void SMBS_Init (unsigned char, unsigned char);  
                   /* Initialise I2C registers and selects the slave address */                                                 
 
#endif

/**** (c) 2001   STMicroelectronics *************************** END OF FILE **/