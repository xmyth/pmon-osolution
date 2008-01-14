#define i2cread newi2cread
	li	msize,0
	li	sdCfg,0
	PRINTSTR("DIMM read\r\n")

	/* only one memory slot, slave address is 1010000b */
	li  	a1, 0x0
    	li      a0,0xa1
    	bal     i2cread
	nop
	beq	v0,0xff,1f
	nop
	beq v0,0x80,1f
	nop
	move a0,v0
	bal hexserial
	nop
    	PRINTSTR ("\r\nNo DIMM in slot 0 \r\n");
	b 2f
	nop
1:
	or  	sdCfg, 0x1<<29
	nop
	li a0,0xa1
	bal ii2c_cfg
	nop
2:
	li  	a1, 0x0
    	li      a0,0xa3
    	bal     i2cread
	nop
	li 	a1,0x0
	beq	v0,0xff,1f
	nop
	beq v0,0x80,1f
	nop
	move a0,v0
	bal hexserial
	nop
	PRINTSTR ("\r\nNo DIMM in slot 1 \r\n");
	b 2f
	nop
1:
	li a0,0xa3
	bal ii2c_cfg
	nop

	b 2f
	nop

2:
	b 211f
	nop
/*ic2 cfg
* a0=0xa1 for slot 0,a0=0xa3 for slot 1
* t5 used for save i2c addr a0,t6 save ra.
*/
LEAF(ii2c_cfg)
	move t6,ra
	move t5,a0

#ifdef I2C_DEBUG
	li t1,0
1:
	move a1,t1
	move a0,t5
	bal	i2cread
	nop

	#print
	move a0, v0
	bal  hexserial
	nop
	PRINTSTR("\r\n")
	addiu t1,t1,1
	li   v0, 0x20
	bleu  t1, v0, 1b
	nop
#endif
       
	/* read Module Rank Density */
	PRINTSTR("Read Module Rank Density at 0x1f\r\n")
	move	a0,t5	/* #zgj-11-17 */
	li	a1,0x1f
	bal	i2cread
	nop
	move 	v1, v0
	andi	v1, 0x1
	beqz	v1, 1f
	nop
	li 	msize, 0x40000000 
	//1G
	b	9f
	nop
1:	move 	v1, v0
	andi	v1, 0x2 
	beqz	v1, 2f
	nop
	li 	msize, 0x80000000 
	//2G
	b	9f
	nop
2:	move 	v1, v0
	andi	v1, 0x4 
	beqz	v1, 3f
	nop
	li 	msize, 0x100000000 
	//4G
	b	9f
	nop
3:	move 	v1, v0
	andi	v1, 0x8 
	beqz	v1, 4f
	nop
	li 	msize, 0x400000000 
	//8G
	b	9f
	nop
4:	move 	v1, v0
	andi	v1, 0x10 
	beqz	v1, 5f
	nop
	li 	msize, 0x800000000 
	//16G
	b	9f
	nop
5:	move 	v1, v0
	andi	v1, 0x20 
	beqz	v1, 6f
	nop
	li 	msize, 0x8000000 
	//128M
	b	9f
	nop
6:	move 	v1, v0
	andi	v1, 0x40 
	beqz	v1, 7f
	nop
	li 	msize, 0x10000000 
	//256M
	b	9f
	nop
7:	move 	v1, v0
	andi	v1, 0x80 
	beqz	v1, 9f
	nop
	li 	msize, 0x20000000 
	//512M
	b	9f
	nop
	
9:

	//sdCfg Format:   4Bit(Row)|4Bit(Col)|3Bit(unused)|1Bit(number of bank)|4Bit(CS)

	/* read Number of DIMM Ranks*/
	PRINTSTR("Read Number of DIMM Ranks at 0x5\r\n")
    move    a0,t5  
	li	a1,5
	bal	i2cread
	nop
	andi	v0, 0xf
	move 	sdCfg, v0
	addi	sdCfg, 1
	mul	msize, sdCfg
	nop

	/* read Row Number of DIMM Ranks*/
	PRINTSTR("Read Row Number of DIMM Ranks at 0x3\r\n")
   	move    a0,t5  
	li	a1,3
	bal	i2cread
	nop
	andi	v0, 0xf
	sll		v0, v0,12
	or		sdCfg, v0
	nop
	
	/* read Col Number of DIMM Ranks*/
	PRINTSTR("Read Col Number of DIMM Ranks at 0x4\r\n")
    move    a0,t5  
	li	a1,4
	bal	i2cread
	nop
	andi	v0, 0xf
	sll		v0, v0, 8
	or		sdCfg, v0
	nop

	/* read Number of Banks*/
	PRINTSTR("Read Number of Banks at 17\r\n")
    move    a0,t5  
	li	a1, 0x11
	bal	i2cread
	nop
	andi	v0, 0xf
	srl		v0, v0, 3
	sll		v0, v0, 4
	or		sdCfg, v0
	nop

	andi	v0, 0x8
	beqz	v0, 1f
	nop
	li		v0, 0x10
	or		sdCfg, v0
1:	

	PRINTSTR("\r\nDDR Cfg = ")
	move	a0, sdCfg
	bal 	hexserial
	nop
	PRINTSTR("\r\n")

#####################################################
	PRINTSTR("Memory Size = ")
	move	a0, msize
	bal 	hexserial
	nop
	PRINTSTR("\r\n")

	
/*	Start write MAX8713 value */

	li	a0, 0x12
	li	a1, 0x14	//ChargeCurrent
	li 	t0, 0x07e0			

	bal i2cwrite
	nop

	li	a0, 0x12
	li	a1,	0x15	//ChargeVoltage
	li 	t0, 0x3130

	bal i2cwrite
	nop
	

	
	jr t6
	nop
END(ii2c_cfg)

LEAF(i2cread)
        /* set device address */
        li  v0, 0xbfd00000 + SMBUS_HOST_ADDRESS

        sb  a0, 0(v0);

        /* store register offset */
        li  v0, 0xbfd00000 + SMBUS_HOST_COMMAND
        sb  a1, 0(v0);

        /* read byte data protocol */
        li  v0, 0x08
        li  v1, 0xbfd00000 + SMBUS_HOST_CONTROL
        sb  v0, 0(v1);

        /* make sure SMB host ready to start, important!--zfx */
        li  v1, 0xbfd00000 + SMBUS_HOST_STATUS
        lbu v0, 0(v1)
        andi v0,v0, 0x1f
        beqz  v0,1f
        nop
        sb  v0, 0(v1)
        lbu v0, 0(v1)   #flush the write
1:

        /* start */
        li  v1, 0xbfd00000 + SMBUS_HOST_CONTROL
        lbu v0, 0(v1)
        ori v0, v0, 0x40
        sb  v0, 0(v1);

        /* wait */
        li  v1, 0xbfd00000 + SMBUS_HOST_STATUS
1:

#if 0
        /* delay */
        li a0, 0x1000
2:
        bnez    a0,2b
        addiu   a0, -1
#endif

        lbu  v0, 0(v1)
        andi v0, SMBUS_HOST_STATUS_BUSY
        bnez  v0, 1b  #IDEL ?
        nop

        li  v1, 0xbfd00000 + SMBUS_HOST_STATUS
        lbu v0, 0(v1)
        andi v0,v0, 0x1f
        beqz  v0,1f
        nop
        sb  v0, 0(v1)   #reset
        lbu v0, 0(v1)   #flush the write
1:

        li  v1, 0xbfd00000 + SMBUS_HOST_DATA0
        lbu  v0, 0(v1)

        jr      ra
        nop
END(i2cread)


LEAF(i2cwrite)
		/* set value 0 address */
		li	v0, 0xbfd00000 + SMBUS_HOST_DATA0
		sb	t0, 0(v0);
		srl	t0, t0, 8
		
		/* set value 1 address */
		li	v0, 0xbfd00000 + SMBUS_HOST_DATA1
		sb	t0, 0(v0);

        /* set device address */
        li  v0, 0xbfd00000 + SMBUS_HOST_ADDRESS

        sb  a0, 0(v0);

        /* store register offset */
        li  v0, 0xbfd00000 + SMBUS_HOST_COMMAND
        sb  a1, 0(v0);

        /* write word data protocol */
        li  v0, 0x0c
        li  v1, 0xbfd00000 + SMBUS_HOST_CONTROL
        sb  v0, 0(v1);

        /* make sure SMB host ready to start, important!--zfx */
        li  v1, 0xbfd00000 + SMBUS_HOST_STATUS
        lbu v0, 0(v1)
        andi v0,v0, 0x1f
        beqz  v0,1f
        nop
        sb  v0, 0(v1)
        lbu v0, 0(v1)   #flush the write
1:

        /* start */
        li  v1, 0xbfd00000 + SMBUS_HOST_CONTROL
        lbu v0, 0(v1)
        ori v0, v0, 0x40
        sb  v0, 0(v1);

        /* wait */
        li  v1, 0xbfd00000 + SMBUS_HOST_STATUS
1:
#if 1
        /* delay */
        li a0, 0x1000
2:
        bnez    a0,2b
        addiu   a0, -1
#endif
        lbu  v0, 0(v1)
        andi v0, SMBUS_HOST_STATUS_BUSY
        bnez  v0, 1b  #IDEL ?
        nop

        li  v1, 0xbfd00000 + SMBUS_HOST_STATUS
        lbu v0, 0(v1)
        andi v0,v0, 0x1f
        beqz  v0,1f
        nop
        sb  v0, 0(v1)   #reset
        lbu v0, 0(v1)   #flush the write
1:

        jr      ra
        nop
END(i2cwrite)

211:
#undef i2cread
######################################################################################################
