/******************************************************************************
COPYRIGHT 2003 STMicroelectronics
Source File Name : SMBS.c 
Group            : IPSW,CMG-IPDF
Author           : MCD Application Team
Date First Issued: 18/07/2003   
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY. STMicroelectronics 
    SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
    DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM USE OF THIS SOFTWARE.

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
********************************Documentation**********************************
General Purpose - Contains source code for all the functions of Slave SMBus.
********************************Revision History*******************************
_______________________________________________________________________________
Date :18/07/2003                  Release:1.0         	   	   	      	       		        
******************************************************************************/

#include "SMBS_config.h"                                /* Selection of Fcpu */
#include "SMBS_hr.h"
#include "ST7FLI49MK1T6.h"
/*-----------------------------------------------------------------------------
ROUTINE NAME : SMBS_Init
INPUT        : Add_Param, Slave_Add
OUTPUT       : None.
DESCRIPTION  : Initialization of all I2C registers. Acknowledge and interrupt 
               are enabled. Slave address of SMBus selected.
COMMENTS     : Must be called before starting any SMBus operation
-----------------------------------------------------------------------------*/
void SMBS_Init (SMBS_Address_t Add_Param,unsigned char Slave_Add1,
                unsigned char Slave_Add2)
{
     I2CCR &= (unsigned char)(~PE) ;                          /* PE disabled */
     I2CDR = 0x00 ;
     I2CCCR = 0x00 ;
     I2COAR1 = 0x00 ;
     I2COAR2 = 0x00 ;                       /* All I2C registers initialised */          
     if (Add_Param == SMBS_MISC)
     {
          I2COAR1 = Slave_Add1 ;             /* Configures I2C slave address */
          I2COAR2 = Slave_Add2 ;
     } 
                    
     if ( Fcpu >= 6000000)                        /* Checking for Fcpu range */
          I2COAR2 |= FRI ;                                   /* Sets FR0 bit */
          
     I2CCR = PE ;                                              /* PE enabled */
     I2CCR = (PE | ACK) ;                             /* Acknowledge enabled */

}

unsigned char tab[3] = {1, 4, 5};

#define CR_INIT_VALUE     25             

void RST(void)
{
	//rst     CLR     I2CCR                  ;Force reset status of control register
	I2CCR = 0;
	//TNZ     I2CDR                  ;Touch registers remove pending interrupt
	I2CDR = 0;
	//BRES    I2CCR,#PE
	I2CCR &= ~PE;
	//BSET    I2CCR,#PE              ;reset I2C cell 
	I2CCR |= PE;
	//LD      a,#CR_INIT_VALUE       ;Set initial control register value. 
	//LD      I2CCR,A
	I2CCR = CR_INIT_VALUE;
	//CLR	index
	//index = 0;
	//IRET
	return;		
}        


void i2c_rt()
{         
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char SMBS_SR1 = I2CSR1;
  unsigned char SMBS_SR2 = I2CSR2;                                                                      
  
  //BCP     A,#%00010010           ;Acknowledge Failure or Bus Error?    	              
  //JREQ    test_EV1               ;if not -> test_EV1.
  
  if ((SMBS_SR2 & 0x12) == 0)
  {
    //test_EV1 
    //BTJF    I2CST1,#ADSL,test_EV2   ;own address is recognized   
    if ((SMBS_SR1 & ADSL) == 0)
      {
      //test_EV2                                ;or EV3 
      //        BTJF    I2CST1,#BTF,test_EV4    ;if BTF=0 -> test if a Stop is received.
      if ((SMBS_SR1 & BTF) == 0)
        {
        //test_EV4	
        //BTJF    I2CST2,#STOPF,rst       ;end of reception or transmission.
        if ((SMBS_SR2 & STOPF) == 0)
        {
          RST();
          return;		
        }
      
        //CLR	index 	
        //index = 0;
        //.end_it IRET
        return;
      }
      //BTJT    I2CST1,#TRA,EV3         ;if the slave in transmitter mode ->EV3
      if (SMBS_SR1 & TRA)
      {
        //EV3     LD      X,index
        //        LD      A,(tab,X)               ;the slave transmitter mode
        //	LD      I2CDR,A                 ;transmission of values stored into tab.
//        I2CDR = index;
        //INC 	index                   
//        index++;
//				index = index % 3;
        //end_ev3 IRET	        
        return;
      }
      //EV2     LD      A,I2CDR		        ;if not, the slave is the receiver.   
      //LD      X,index 
      //LD      (tab,X),A               ;store the received value into tab.
     // tab[index] = I2CDR;
      //INC     index                 
      //index++;
      
      //end_EV2 IRET
      return;
    }
    //IRET 	        	
    return;
  }
  //BCP	A,#%00000010           ;Checking for bus error
  if (SMBS_SR2 & 0x20 == 1)
  {
    //JRNE	rst		       ;if BERR, jump to rst
    RST();
    return;
  }
  //LD	A,index 	       ;if AF and index=last byte -> EV3_1.
  //CP	A,#3
//  if (index == 3)
  {
    //JRPL	EV3_1
    //EV3_1   LD	A,#$FF			;Non acknowledge (AF=1).
    //LD	I2CDR,A			;Dummy write to see STOP condition
    I2CDR = 0xff;
    //IRET     		
    return;
  }
  
  RST();
  //IRET
  return;                      
}

/*** (c) 2003  ST Microelectronics ****************** END OF FILE ************/