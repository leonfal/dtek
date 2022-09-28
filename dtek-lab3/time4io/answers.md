# LAB 3

## questions for assignment 1

### Test pressing BTN3 and BTN2 at the same time. What happens? Why?

- Båda värderna ändras samtidigt. Eftersom den går igenom alla if-statements så kommer bägge fallen med btn2 och btn3 bli sanna.

### Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR. Their functions are related. How? What are the differences?

- TRISE sätter om portE är input eller output. TRISET är samma sak som att göra |= TRISE. TRISECLR är samma som att invers bitmaska med TRISE dvs &= ~

### In the generated assembly code, in which MIPS register will the return values from functions getbtns and getsw be placed in. You should be able to answer this question without debugging the generated assembly code.

- In $v0, cause the return register is v0 in assembly.

### In this exercise, we explained which bits that should be used in Port D and Port E. How can you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate how to find this information in the manuals.

- Söker först upp hårdvarans UNO32 pin i chipkit basic io shield ref manual. Med den pinen söker vi i chipkit uno32 board ref manual efter raden med den vårt pin nummer. Ser att det exempelvis står "RD5" vilket innebär att Port D bit 5 ska användas för att initalisera det som input eller output.
