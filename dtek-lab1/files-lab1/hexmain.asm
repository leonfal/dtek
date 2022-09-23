  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,17		# change this to test different values, if the value is greater than 15 the program will perform similarly to modulo 16 (because we cut off the 4 lsb and 16 = 10000 and 0 = 0000 masking 4 lsb makes them equal

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here

hexasc: 
	
	andi $a0, $a0, 0xf	# masking the 4 lsb
	addi $v0, $zero, 0x30	# Makes the 0 = 0 in ascii ('0' in ascii is 30 in hex)
	addi $t0, $zero, 9	# temporary value to act as a checker for values 0-9
	
	ble $a0, $t0, ascii	# if the number in $a0 is in between 0-9 the binary to ascii conversion is complete
	
	addi $v0, $v0, 7	# if the number is greater than 9 we need to increment further 7 steps (between 9 and A in ascii is 7 steps)
	
ascii:
	
	add $v0, $a0, $v0	# returns the ascii hex code
	jr $ra
