	# enable_interrupt.S
	# Based on a file written 2015-2017 by F Lundevall.
	# Edited 2018-11- by M. Wesslén and A. Elmarsson.
	# For copyright and licensing, see file COPYING.
	# The macros PUSH and POP are in the public domain.

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
.globl enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop
