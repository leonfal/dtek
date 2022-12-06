.global main
	.text
	
main:
addi $a0, $0, 3 # a0 = n
addi $v0, $0, 1		# result = v0 = 1
addi $a1, $0, 0		

loop:
	beq   $a0, 0, stop	#if (a0=0), return stop
	addi  $a0, $a0, -1		#if (a0!=0), a0--
	add  $a1, $a0, $0		# a1 = a0
	add  $v1, $v0, $0		# v1 = v0

multiply:				#to multiply a1*v1
	beq   $a1, $0, loop	#if (a1=0), go loop
	add   $v0, $v0, $v1	#v0 = v0 + v1
	addi  $a1, $a1, -1	#a1--
	beq   $0, $0, multiply	
	
stop:
	beq $0, $0, stop