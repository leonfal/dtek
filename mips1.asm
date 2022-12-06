  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	addi $t1,$0,0
	li $a0, 1
loop:
lw $s0,4($a1)
lw $s1,8($a1)
and $s0,$s0,$s1
done:
	nop
