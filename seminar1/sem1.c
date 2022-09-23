#include <stdio.h>
#include <string.h>

void subber(const int *x, const int *y, int *z)
{
  *z = (*x - *y);
}

int foo(int a)
{
  const int k = 10;
  int resultat;
  subber(&a, &k, &resultat);
  return resultat;
}

int square_reverse(double *x, double *y, const int len)
{
  int sum = 0;
  for (int i = 0; i < len; i++)
  {
    *(y + (len - 1 - i)) = *(x + i) * *(x + i); // square the numbers of x and revers back them into y.
    sum += *(x+i); // sum all numbers of x
  }

  for (int i = 0; i < len; i++)
  {
    printf("%.1f ", *(y + i));
  }

  return sum;
}

int main(int argc, char const *argv[])
{
  printf("%10d ", foo(7));

  double in[] = {-11.0, 20.0, 100.0};
  double out[3];

  printf("%d ", square_reverse(in, out, 3));
  return 0;
}
