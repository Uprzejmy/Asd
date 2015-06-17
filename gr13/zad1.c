#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double functionG(double t);

int main()
{
  //dane
  double deltaT;
  double maxT;
  double fMinusDeltaT;
  double fZero;
  int n;
  int counter = 0;

  //pomocnicze
  double t;
  double f0,f1,f2;//f(x0),f(x1),f(x2) - wartosci funkcji f dla kolejnych krokow (f(0) != fZero)

  printf("Podaj delta t\n");
  scanf("%lf",&deltaT);

  printf("Podaj max t\n");
  scanf("%lf",&maxT);

  printf("Zdefiniuj f(-delta t)\n");
  scanf("%lf",&fMinusDeltaT);

  printf("Zdefiniuj f(0)\n");
  scanf("%lf",&fZero);

  printf("Podaj n\n");
  scanf("%d",&n);

  f0 = fMinusDeltaT;
  f1 = fZero;

  for(t=deltaT;t<=maxT;t+=deltaT)
  {
    f0 = f1;
    f1 = f2;
    f2 = (f1-f0)/(functionG(t-deltaT)+functionG(t-2*deltaT));

    if(++counter % n == 0)
      printf("Wartosc funkcji f(%lf) wynosi: %lf\n",t,f2);
  }

  return 0;
}

double functionG(double t)
{
  return 1+t;
}