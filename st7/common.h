#ifndef __COMMON_H__
#define __COMMON_H__

/* --------Define Macros for bit manipulation ------------*/
#define SetBit(VAR,BIT_NUM)	( (VAR) |= (1<<(BIT_NUM)) )
#define ClrBit(VAR,BIT_NUM)	( (VAR) &= ((1<<(BIT_NUM))^0xFF) )
#define ValBit(VAR,BIT_NUM)	( (VAR) & (1<<(BIT_NUM)) )
#define BitIsClear(VAR,BIT_NUM) ( 0 == ValBit(VAR,BIT_NUM) )
#define BitIsSet(VAR,BIT_NUM)   ( !BitIsClear(VAR,BIT_NUM) )

/*----------Macros for Assembly instructions-----------*/   
#define EnableInterrupts {_asm ("RIM");}  
#define DisableInterrupts {_asm ("SIM");} 
#define Nop {_asm ("nop");} 
#define WaitforInterrupt {_asm ("wfi");} 
#define Trap {_asm ("trap"); }

#endif
