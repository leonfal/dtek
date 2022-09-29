  # labwork.S
  # Written 2015-2017 by F Lundevall
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

	.globl time2string
	.globl hexasc
	.globl delay
	.globl enable_interrupt
	.text

enable_interrupt:
	ei
	jr $ra
	nop

hexasc:

	andi $a0, $a0, 0xf	# masking the 4 lsb
	addi $v0, $zero, 0x30	# Makes the 0 = 0 in ascii ('0' in ascii is 30 in hex)
	addi $t0, $zero, 0x9	# temporary value to act as a checker for values 0-9

	ble $a0, $t0, ascii	# if the number in $a0 is in between 0-9 the binary to ascii conversion is complete
	nop

	addi $v0, $v0, 0x7	# if the number is greater than 9 we need to increment further 7 steps (between 9 and A in ascii is 7 steps)

ascii:

	add $v0, $a0, $v0	# returns the ascii hex code
	jr $ra
	nop

delay:

    move    $t5, $a0            # Store argument in temp
    li    $t4, 0                # int i    = 0
    nop

    whileloop:
        ble    $t5, $zero, exit    # Exit if ms < 0, and continue while loop if not
        nop
        addi    $t5, $t5, -1         # ms = ms - 1
        li    $t4, 0            # int i    = 0

    forloop:
        beq    $t4, 4000, whileloop    # Check if i = the constant
        nop
        addi    $t4, $t4, 1        # i = i + 1
        j    forloop            # Iterate
        nop

    exit:
        jr    $ra
        nop

time2string:

	PUSH $s4
	PUSH $s6

	move $s4, $ra

	add $s6, $0, $a0

	# first digit in minutes
	andi $a0, $a1, 0x0000F000	# saves the first digit in minutes (1 byte)
	srl $a0, $a0, 12		# shifts it so that is has the adequate format to be put in hexasc
	jal hexasc
	nop

	sb $v0, 0($s6)


	# second digit in minutes
	andi $a0, $a1, 0x00000F00
	srl $a0, $a0, 8
	jal hexasc
	nop

	sb $v0, 1($s6)

	# the comma inbetween minutes and seconds
	li $t3, 58

	sb $t3, 2($s6)


	# first digit in seconds
	andi $a0, $a1, 0x000000F0
	srl $a0, $a0, 4
	jal hexasc
	nop

	sb $v0, 3($s6)


	# second digit in seconds
	andi $a0, $a1, 0x0000000F

	jal hexasc
	nop
	sb $v0, 4($s6)
	# null at the end
	li $t3, 0
        sb $t3, 5($s6)

	POP $s6
	move $ra, $s4
	POP $s4
	jr $ra		# the return adress
	nop

