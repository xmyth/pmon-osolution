/******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : SMBS_config.h  
Group            : IPSW,CMG - IPDF
Author           : MCD Application Team
Date First Issued: 18/07/2003
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. STMicroelectronics 
    SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
    DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
********************************Documentation**********************************
General Purpose - This file is used to select the frequency and Packet Error
                  Checking
********************************Revision History*******************************
_______________________________________________________________________________
Date :18/07/2003                 Release:1.0		       		 
******************************************************************************/
#ifndef	SMBS_CONFIG_H
#define	SMBS_CONFIG_H

/*****************************Non User Part***********************************/
#include "SMBS.h" 

#endif	     
/*-----------------------------Compiler Selection----------------------------*/     
#if (defined(__HIWARE__) || defined(__MWERKS__))
#define _MWERKS_ 
#else
#ifdef __CSMC__
#define _COSMIC_
#else
#error "Unsupported Compiler!"                 /* Compiler defines not found */
#endif
#endif 

/*----------------------------Enumerated data type---------------------------*/
#ifndef enum_type
#define enum_type
typedef enum {
	FALSE	=(unsigned char) 0x00,			
	TRUE   = !(FALSE)                
        }BOOL; 
#endif	     

/*---------------------Macros for Assembly instructions----------------------*/   
#ifdef _MWERKS_
#define EnableInterrupts {asm RIM;}
#define DisableInterrupts {asm SIM;}
#define Nop   {asm nop;}
#define WaitforInterrupt {asm wfi;}
#endif

#ifdef _COSMIC_
#define EnableInterrupts {_asm ("RIM");}  
#define DisableInterrupts {_asm ("SIM");} 
#define Nop {_asm ("nop");} 
#define WaitforInterrupt {_asm ("wfi");} 
#endif
     
/******************************** End of Non-user Part ***********************/

/**************************** User customizable Part *************************/
/*---------------------------------Define Fcpu-------------------------------*/
#define Fcpu ((unsigned long) 8000000)   
/*-----------------------Selection of PEC calculation------------------------*/
//#define SMBS_PEC          
/******************************** End of User Part ***************************/

/**** (c) 2003   STMicroelectronics *************************** END OF FILE **/