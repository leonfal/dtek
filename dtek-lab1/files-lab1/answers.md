# LAB 1

### Questions for assignment 1

- Which lines of code had to be changed? Why?
  - Change Line 14, to get every third character we write a 3 instead of 1. Change Line 16 to the third next character after 'Z' which is 0x5d instead of 0x5b.

### Questions for assignment 2

- Your subroutine hexasc is called with an integer-value as an argument in register $a0, and
  returns a return-value in register $v0. If the argument is 17, what is the return-value? Why?

  - if the value is greater than 15 the program will perform similarly to modulo 16 (because we cut off the 4 lsb and 17 = 10001 and 1 = 0001, bitmasking 4 lsb makes them equal

- If your solution contains a conditional-branch instruction: which input values cause the
  instruction to actually branch to another location? This is called a taken branch.
  - if the number in $a0 is greater than 9 (not equal to) the code branches to another location.

### Questions for assignment 3

- Which registers are saved and restored by your subroutine? Why?

  - Saves the $ra into $t6 to be able to jump back after time2string was called in main. We do this because the register $ra is altered everytime in hexasc.

- Which registers are used but not saved? Why are these not saved?

  - $a3 is used to mainpulate the nbcd coded bits from $a1. Then $a3 is not saved. Nor is the $t6 register after jr is performed at the end of time2string.

- Assume the time is 16:53. Which lines of your code handle the '5'?
  - lines 145-150 handles the first digit in seconds (the 5 in this case)

### Questions for assignment 4

- If the argument value in register $a0 is zero, which instructions in your subroutine are executed? How many times each? Why?

  - does not perform any of the code inside the loops, exits directly on the condition of ble.

- Repeat the previous question for a negative number: -1.

  - same as above

### Questions for assignment 6

- What is the effect of the assembler directive .global? Why is the directive particularly important in this assignment? The teachers will help you with this if necessary.
  - The assembler assumes every function is local. We have to specify that the functions are global. Important because we want to be able to run it on the chipKIT.
