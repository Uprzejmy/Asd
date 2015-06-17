#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double functionF(double t);
double functionG(double t);

int main()
{
  //dane
  double deltaT;
  double maxT;
  int n;

  //pomocnicze
  double f0;
  double f1;
  double f2;

  printf("Podaj delta t\n");
  scanf("%lf",&deltaT);

  printf("Podaj max t\n");
  scanf("%lf",&maxT);

  printf("Podaj n\n");
  scanf("%d",&n);

  return 0;
}

double functionF(double t)
{
  if(t == 0)
    return 1.0;
  
  return t*t;
}

double functionG(double t)
{
  return 1+t;
}