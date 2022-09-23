#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define COLUMNS 6
int columncount = 0;
// function to print a number n
void print_number(int n)
{
  if(columncount == COLUMNS)
  {
    printf("\n");
    printf("%10d ", n);
    columncount = 0;
    columncount++;
  }
  else
  {
    printf("%10d ", n);
    columncount++;
  }
}

void print_sieves(int n)
{
  // allocating an array to heap.
  char *sieve = malloc(n*sizeof(char)); // allocate n bytes for the array (char is 1 byte)
  memset(sieve, 1, n*sizeof(char)); // assigns all n bytes to a '1' in sievex

  for (int i = 2; i < sqrt(n); i++)
  {
    if(sieve[i] == 1)
    {
      for (int j = i*i; j < n; j += i)
      {
        sieve[j] = 0;
      }
    }
  }

  // loop to print out the prime numbers (containing a 1 in sieve[])
  for (int i = 2; i < n; i++)
  {
    if (sieve[i])
    {
      print_number(i);
    }
  }
  // return the memory to heap when no longer needed.
  free(sieve);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
