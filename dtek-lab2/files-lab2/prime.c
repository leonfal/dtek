/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <math.h>

int is_prime(int n){
  // base case (1 and numbers less than 1 is not a prime number)
  if (n <= 1)
  {
    return 0;
  }

  for (int i = 2; i <= sqrt(n); i++)
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
