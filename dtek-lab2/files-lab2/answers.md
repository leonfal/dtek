# LAB 2

### questions for assignment 2

- What does it mean when a function does not return a value? How do you state that in a program? How can then the function (or more precisely, the procedure) perform anything useful?

  - It means that the function is only a procedure, by stating it with 'void' instead of i.e 'int'. It only perform what is in the function, and returns no value. It is useful for stuff that does not include altering a variable and returning it, for example printing something.

- How did you implement the side effect that is needed to make print_number behave correctly?
  - implemented an if statement accompanied with a global columncounter that increments everytime the function prints a number.

### questions for assignment 3

- How did you represent the marking of 'prime' and 'not a prime' in the memory array?

  - 1 = prime, 0 = non prime. 1s and 0s being a char (1 byte in memory)

- Which are the main steps in the algorithm? How have you implemented these steps?

  - The main steps is to loop through all numbers from 2 to sqrt(n). Setting the array to all 1s initially, then if sieve[i] = 1 we loop through all elements in the array from i^2 to i^2 + (n-1)\*i and set those numbers to 0.

- printprimes: 10seconds = 11 million, 2seconds = 3.5 million
- sieves: 10seconds = stackoverflow, 2seconds = stackoverflow
- sievesheap: 10seconds = 400 million, 2seconds = 80 million
  The reason why printprimes is the slowest is because it calculates in every iteration. Sieves allocates the array to the stack, and stack has a limit hence the overflow. Seivesheap uses heap which is memory and thus is the fastest.

### Answers for assignment 5

1. m är en lokal variabel i main scope. På rad 76 skickas m in i fun. Om m är 8 när vi skickar in i fun så incrementar vi m med 1. Ger värdet till gv. Eftersom gv är globalt scope får gv värdet 9 efter funktionsanropet, medan m stannar till värdet innan funktionsanropet. Vilket är 8.
2. The size of a pointer is machine dependant. 32 bits in our case for MIPS ISA.
3. String in C i stored as an array of chars, terminated by a null byte. Since we have 8 characters in "Bonjour!" we need a size of 9 of the char array to make room for the terminating null byte.
4. fun adress: 0x9D001180, main adress: 0x9D0011D8. Both stored in the section KSEG0 of virtual memory and of type reserved memory. Datan är instruktion som pekas på.

### Assignment 5 preparation questions

1. in: 0xA0000008. gv: 0xA000000C
   - Located in the RAM of section KSEG1 of virtual memory. Located in RAM because it allows for read and write.
2. p och m är i reserverat minne, addressnummrerna för p och m är större eftersom de är ligger i en annan sektion av minnet än gv o in.
3. adress: 0xA0003FE8
   data: 0xA0003FE4 (adress of m)
   value of p is adress, pointed to the data.
4. same as above but m has incremented its value (same adress still)
5. Det är little-endian för att lsb startar på den lägsta adressen
