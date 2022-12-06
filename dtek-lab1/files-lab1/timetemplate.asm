  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)	# loading $a1 with the 4 digits representing the time.
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
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
	
	PUSH ($s4)
	PUSH ($s6)
	
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
	
	li $t7, 0x32
	beq $t7, $v0, two
	nop
	sb $v0, 4($s6)
	# null at the end
	li $t3, 0
        sb $t3, 5($s6)
	
	POP ($s6)
	move $ra, $s4
	POP ($s4)
	jr $ra		# the return adress
	nop
	
	 two:
	 	li $t9, 0x54
		sb $t9, 4($s6)
		li $t9, 0x57
		sb $t9, 5($s6)
		li $t9, 0x4f
		sb $t9, 6($s6)
		li $t3, 0
        	sb $t3, 7($s6)
        	move $ra, $s4
        	POP ($s6)
		POP ($s4)
        	jr $ra		# the return adress
		nop
		
	# null in ASCII
	
        
        
	
