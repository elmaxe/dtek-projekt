  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Edited 2018-09-04 by M Wesslén
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.text
.globl hexasc
.globl delay
.globl time2string
.globl enable_interrupt
hexasc:
	li 	$t0,9		# store the number which divides between numbers and letters
	andi 	$t1,$a0,0xf	# zeroes the 24 most significant bits
	ble 	$t1,$t0,number	# jump to 'number' if argument <= $t0
	nop
	j 	letter		# else jump to letter
	nop
number:
	addi 	$v0,$t1,0x30	# add 0x30 for the arguments 0-9 to become ASCII-codes for 0-9
	jr 	$ra		# jump back to caller position
	nop
letter:
	addi 	$v0,$t1,0x37	# add 0x37 for the arguments 10-15 to become ASCII-codes for A-F
	jr 	$ra		# jump back to caller position
	nop

delay:
	ble	$a0,$zero,delayend
	addi	$a0,$a0,-1
	li	$t0,0
msloop:
	addi	$t0,$t0,1
	slti	$t1,$t0,6630
	bne	$t1,$zero,msloop
	nop
	j	delay
	nop
delayend:
	jr	$ra
	nop

time2string:
	# save registers
	PUSH	$ra
	PUSH	$s0
	PUSH	$s1

	# store the arguments
	move	$s0,$a0
	move	$s1,$a1

	# store the first minute digit
	srl	$a0,$s1,12
	jal	hexasc
	nop
	sb	$v0,0($s0)

	# store the second minute digit
	srl	$a0,$s1,8
	jal	hexasc
	nop
	sb	$v0,1($s0)

	# store the colon character
	li	$t0, 0x3A
	sb	$t0,2($s0)

	# store the first second digit
	srl	$a0,$s1,4
	jal	hexasc
	nop
	sb	$v0,3($s0)

	# store the second second digit
	srl	$a0,$s1,0
	jal	hexasc
	nop
	sb	$v0,4($s0)

	# store the last nullbyte
	li	$t0, 0x00
	sb	$t0,5($s0)

	# restore registers
	POP	$s1
	POP	$s0
	POP	$ra
	jr	$ra
	nop
enable_interrupt:
	ei
	jr $ra
	nop
