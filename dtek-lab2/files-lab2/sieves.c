#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define COLUMNS 6
int columncount = 0;
// function to print a number n
int distance_counter = 0;
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
  char sieve[n]; // allocate n bytes for the array (char is 1 byte)
  memset(sieve, 1, sizeof(sieve));

  // Sieves algorithm, according to the linked material in lab instructions.
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

  char primes[n];
  int k = 1;
  // loop to print out the prime numbers (containing a 1 in sieve[])
  for (int i = 2; i < n; i++)
  {
    if (sieve[i])
    {
      print_number(i);
      primes[k] = i;
      if ((primes[k] - primes[k-1]) == 4)
      {
        distance_counter++;
      }
      k++;
    }
  }
  printf("\n %10d distances of 4 between prime numbers up to %d", distance_counter, n);
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
