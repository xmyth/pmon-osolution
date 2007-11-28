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
* a0=0xa1 for slot 0,a0=0xa1 for slot 1
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
       
	/* read DIMM number of rows */
	move	a0,t5	/* #zgj-11-17 */
	li	a1,3
	bal	i2cread
	nop
	li	a0,1
	sll 	tmpsize,a0,v0
	PRINTSTR("read number of rows\r\n")

	/* read DIMM number of cols */
    	move    a0,t5   /* #zgj-11-17 */
	li	a1,4
	bal	i2cread
	nop
   	sll	tmpsize,tmpsize,v0
	PRINTSTR("read number of cols\r\n")

	/* read DIMM number of cols */
    	move    a0,t5   /* #zgj-11-17 */
	li	a1,5
	bal	i2cread
	nop
	andi	v0, 1
	li 	sdCfg, 1
	beq	v0,0x1,1f
	nop
	b 	2f
	nop
1:	li	sdCfg, 3	
2:   	sll	tmpsize,tmpsize,v0
	PRINTSTR("read number of banks\r\n")

	/* read DIMM number of cols */
    	move    a0,t5   /* #zgj-11-17 */
	li	a1,6
	bal	i2cread
	nop
	srl	v0, v0, 1
   	//sll     tmpsize,tmpsize,v0 # multiply by 4M
	mul	tmpsize,v0
#####################################################
	addu	msize,tmpsize
	move	a0, msize
	bal 	hexserial
	nop
	b 1f
	nop
1:
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
211:
#undef i2cread
######################################################################################################
