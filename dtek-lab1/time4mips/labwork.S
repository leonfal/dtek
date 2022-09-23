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

	.text
hexasc: 
	
	andi $a3, $a3, 0xf	# masking the 4 lsb
	addi $v0, $zero, 0x30	# Makes the 0 = 0 in ascii ('0' in ascii is 30 in hex)
	addi $t0, $zero, 0x9	# temporary value to act as a checker for values 0-9
	
	ble $a3, $t0, ascii	# if the number in $a0 is in between 0-9 the binary to ascii conversion is complete
	nop
	
	addi $v0, $v0, 0x7	# if the number is greater than 9 we need to increment further 7 steps (between 9 and A in ascii is 7 steps)
	
ascii:
	
	add $v0, $a3, $v0	# returns the ascii hex code
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
        beq    $t4, 70, whileloop    # Check if i = the constant // 70 for MARS 4000 for MCB32
        nop
        addi    $t4, $t4, 1        # i = i + 1
        j    forloop            # Iterate
        nop

    exit:
        jr    $ra
        nop
	
time2string:
	
	move $t6, $ra
	
	# first digit in minutes
	andi $a3, $a1, 0x0000F000	# saves the first digit in minutes (1 byte)
	srl $a3, $a3, 12		# shifts it so that is has the adequate format to be put in hexasc
	jal hexasc
	nop
	
	sb $v0, 0($a0)			
	
	
	# second digit in minutes
	andi $a3, $a1, 0x00000F00
	srl $a3, $a3, 8
	jal hexasc
	nop
	
	sb $v0, 1($a0)
	
	# the comma inbetween minutes and seconds
	li $t3, 58
	
	sb $t3, 2($a0)
	
	
	# first digit in seconds
	andi $a3, $a1, 0x000000F0
	srl $a3, $a3, 4
	jal hexasc
	nop
	
	sb $v0, 3($a0)
	
	
	# second digit in seconds
	andi $a3, $a1, 0x0000000F
	jal hexasc
	nop
	
	sb $v0, 4($a0)
	
	# null in ASCII
	li $t3, 0
        sb $t3, 5($a0)
        
        
	jr $t6		# the return adress
	nop

