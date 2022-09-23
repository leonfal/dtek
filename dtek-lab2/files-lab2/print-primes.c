/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int columncount = 0; // global variable to count columns

// function to print a number n
void print_number(int n)
{
  if (columncount == COLUMNS)
  {
    printf("\n");
    printf("%10d ", n);
    columncount = 0; // reset column counter.
    columncount++;
  }
  else
  {
    printf("%10d ", n);
    columncount++;
  }
}

int is_prime(int n){
  // base case (1 and numbers less than 1 is not a prime number)
  if (n <= 1)
  {
    return 0;
  }

  for (int i = 2; i <= sqrt(n); i++) //size_t is used just as a counter variable from 0 and above.
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  int t = 2;
  while (t <= n)
  {
    if (is_prime(t))
    {
      print_number(t);
    }
    t++;
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}


