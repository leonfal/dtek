#include <stdio.h>
#include <stdlib.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

// list1: .space 80
int list1[20];
// list2: .space 80
int list2[20];

// count : .word 0 (32 bits)
int count = 0;

void copycodes(char *p, int *l, int *c)
{
  //beq t0, 0, done
  while (*p != 0)
  {
    // lb t0, 0(a0)
    int tmp = *p;
    // sw t0, 0(a1)
    *l = tmp;
    // addi a0, a0, 1
    p++;
    // addi a1, a1, 4
    l++;

    *c += 1;
  }
}

void work()
{
  // la a0, text1
  char *t1 = text1;
  // la a1, list1
  int *l1 = list1;
  copycodes(t1, l1, &count);

  // la a0, text1
  char *t2 = text2;
  // la a1, list1
  int *l2 = list2;
  copycodes(t2, l2, &count);

}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));

}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
