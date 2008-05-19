#include "SMBS.h"
#include "common.h"
#include "eeprom.h"
#include "ST7FLI49MK1T6.h"

extern PM_STATUS g_traped_pm_status;

#define INVALID_ADDR 0xFF
unsigned char I2CAddress = -1;
unsigned char I2COffset = INVALID_ADDR;

void SMBS_Init (unsigned char Slave_Add1, unsigned char Slave_Add2)
{
	I2CCR &= (unsigned char)(~PE) ;                          /* PE disabled */
	I2CDR = 0x00 ;
	I2CCCR = 0x00 ;
	I2COAR1 = 0x00 ;
	I2COAR2 = 0x00 ;                       /* All I2C registers initialised */          
	I2COAR1 = Slave_Add1 ;             /* Configures I2C slave address */
	I2COAR2 = Slave_Add2 ;
	
								
	if ( Fcpu >= 6000000)                        /* Checking for Fcpu range */
		I2COAR2 |= FRI0 ;                                   /* Sets FR0 bit */
			
	I2CCR = PE ;                                              /* PE enabled */
	I2CCR = (PE | ACK) ;                             /* Acknowledge enabled */
	I2CCR |= ITE ;   						//Enable Interrupt
	I2CAddress =INVALID_ADDR;
  
}

unsigned char STATE = EVT_NONE;

void ResetI2C(void)
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
	I2CCR = (PE | ACK);

  I2CAddress =INVALID_ADDR;

  //IRET
	STATE = EVT_NONE;
	
	I2CCR |= ITE ;   						//Enable Interrupt

return;		
}        


//unsigned char statnum = 0;
//unsigned char eeprom[30];

@interrupt void I2C_INT(void)
{         
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char SMBS_SR1 = I2CSR1;
  unsigned char SMBS_SR2 = I2CSR2;    

//  stat[statnum][0] = SMBS_SR1;
//  stat[statnum++][1] = SMBS_SR2;
                                                                  
  if (SMBS_SR2 & BERR)	//Check if Bus Error
  {
		ResetI2C();
		return;
	}
	
	if (SMBS_SR2 & AF)
	{
		//EV3-1
		STATE = EVT3_1;
		I2CDR = 0xFF;
		return;
	}
		
	//EV1: EVF=1, ADSL=1, cleared by reading SR1 register.
	//EV2: EVF=1, BTF=1, cleared by reading SR1 register followed by reading DR register.
	//EV3: EVF=1, BTF=1, cleared by reading SR1 register followed by writing DR register.
	//EV3-1: EVF=1, AF=1, BTF=1; AF is cleared by reading SR1 register. BTF is cleared by releasing the lines
	//(STOP=1, STOP=0) or by writing DR register (DR=FFh). If lines are released by STOP=1, STOP=0, the On-chip peripherals subsequent EV4 is not seen.
	//EV4: EVF=1, STOPF=1, cleared by reading SR2 register.
	
	if (SMBS_SR1 & EVF == 0)
		return;

	if (SMBS_SR1 & ADSL)
	{
		I2CAddress = I2CDR;
		STATE = EVT1;
		return;
	}
	if (SMBS_SR1 & BTF)
	{
		//Next, in 7-bit mode read the DR register to determine from the least significant bit (Data
		//Direction Bit) if the slave must enter Receiver or Transmitter mode.
		
		if (I2CAddress & BIT0)
		{
			//EV3
			STATE = EVT3;
			
			//Read OP
			//I2CDR = EEPROM[I2COffset];
      //I2CDR=eeprom[I2COffset];
			if (I2COffset == 0)
			{
				I2CDR = eeprom_get_status(); 
			}
			else if (I2COffset == 1)
			{
				I2CDR = eeprom_get_cfg();
			}
			else if (I2COffset == 2)
			{
				I2CDR = eeprom_get_status_his();
			}
			else
			{
				I2CDR = 0xaa;
			}
			I2COffset++;
		}
		else
		{
			//EV2
			STATE = EVT2;

			if (I2COffset == INVALID_ADDR)
				I2COffset = I2CDR;
			else
			{
					//Write OP
				//EEPROM[I2COffset] = I2CDR;
        g_traped_pm_status = (PM_STATUS)I2CDR;
        Trap;
				//eeprom[I2COffset] = I2CDR;
				//I2COffset++;
			}
		}
	}
	else if (SMBS_SR2 & STOPF)
	{
		//EV4
		STATE = EVT_NONE;
		I2COffset = INVALID_ADDR;
	}
	else
	{
		ResetI2C();
	}

  return;                      
}
