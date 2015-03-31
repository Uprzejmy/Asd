/**
 * Program liczy całki oznaczone wybranych funkcji matematycznych
 *
 * autor: Łukasz Merynda
 * kontakt: lmerynda@gmail.com
 *
 * kompilowalem gcc -g -Wall calki.c -o calki -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int amountOfIntervals = 10000;
int amountOfSamples = 500000;
double function1(double x);
double function2(double x);
double function3(double x);
double function4(double x);
double rectangleIntegration(double from, double to, double (*function)(double));
double trapeziumIntegration(double from, double to, double (*function)(double));
double monteCarloIntegration(double from, double to, double (*function)(double));
double findLocalMax(double from, double to, double (*function)(double));
double findLocalMin(double from, double to, double (*function)(double));
double* generatePoint(double xFrom, double xTo, double yFrom, double yTo);
double generateCoordinate(double from, double to);

int main()
{
  double from,to;

  srand(time(NULL));

  // printf("Podaj wartosci przedzialow, dla ktorych bedzie liczona calka\n");
  // scanf("%lf %lf",&from,&to);
  // printf("\n");

  printf("Sinus\n");

  from=-20*M_PI;
  to=20*M_PI;

  printf("Przedział całkowania: ( %lf , %lf )\n",from,to);
  printf("Prostokaty: %lf\n",rectangleIntegration(from,to,&function1));
  printf("Trapezy: %lf\n",trapeziumIntegration(from,to,&function1));
  printf("Monte Carlo: %lf\n",monteCarloIntegration(from,to,&function1));


  printf("\n\n\nLogarytm\n");

  from=-1.5;
  to=2.5;

  printf("Przedział całkowania: ( %lf , %lf )\n",from,to);
  printf("Prostokaty: %lf\n",rectangleIntegration(from,to,&function2));
  printf("Trapezy: %lf\n",trapeziumIntegration(from,to,&function2));
  printf("Monte Carlo: %lf\n",monteCarloIntegration(from,to,&function2));


  printf("\n\n\nWielomian\n");

  from=-1.5;
  to=1;

  printf("Przedział całkowania: ( %lf , %lf )\n",from,to);
  printf("Prostokaty: %lf\n",rectangleIntegration(from,to,&function3));
  printf("Trapezy: %lf\n",trapeziumIntegration(from,to,&function3));
  printf("Monte Carlo: %lf\n",monteCarloIntegration(from,to,&function3));

  printf("\n\n\nWymierna\n");

  from=-20.0;
  to=30.0;

  printf("Przedział całkowania: ( %lf , %lf )\n",from,to);
  printf("Prostokaty: %lf\n",rectangleIntegration(from,to,&function4));
  printf("Trapezy: %lf\n",trapeziumIntegration(from,to,&function4));
  printf("Monte Carlo: %lf\n",monteCarloIntegration(from,to,&function4));

  return 0;
}

double rectangleIntegration(double from, double to, double (*function)(double))
{
  double interval = (to-from)/amountOfIntervals;
  double sum = 0;
  double x;

  for(x=from+interval/2;x<to;x+=interval)
  {
    sum+=function(x);
  }

  return sum*interval;
}

double trapeziumIntegration(double from, double to, double (*function)(double))
{
  double interval = (to-from)/amountOfIntervals;
  double sum = 0;
  double x;

  for(x=from;x<to;x+=interval)
  {
    sum+=function(x)+function(x+interval);
  }

  return sum*interval/2;
}

double monteCarloIntegration(double from, double to, double (*function)(double))
{
  int i;
  int hits=0;
  
  double fx;
  double* point;

  double max = findLocalMax(from,to,*function);
  double min = findLocalMin(from,to,*function);

  for(i=0;i<amountOfSamples;i++)
  {
    point = generatePoint(from,to,min,max);
    fx = function(point[0]);
    if(point[1]>0)
    {
      if(point[1]<fx)
        hits++;
    }
    else if(point[1]<0)
    {
      if(point[1]>fx)
        hits--;
    }
  }

  return (to-from)*(max-min)*hits/amountOfSamples;
}

/**
 * parameters:
 *  interval (from,to)
 *  function to find local maximum
 *
 * return:
 *  double: MIN(localMaximum,0)*1,1 (safety reasons!)
 *
 */
double findLocalMax(double from, double to, double (*function)(double))
{
  double interval = (to-from)/amountOfIntervals;
  double max = 0;
  double x,fx;

  for(x=from;x<to;x+=interval)
  {
    fx = function(x);
    if(fx>max) 
      max = fx;
  }

  return max*1.1;
}

/**
 * parameters:
 *  interval (from,to)
 *  function to find local minimum
 *
 * return:
 *  double: MAX(localMinimum,0)*1,1 (safety reasons!)
 *
 */
double findLocalMin(double from, double to, double (*function)(double))
{
  double interval = (to-from)/amountOfIntervals;
  double min = 0;
  double x,fx;

  for(x=from;x<to;x+=interval)
  {
    fx = function(x);
    if(fx<min) 
      min = fx;
  }

  return min*1.1;
}

/**
 * parameters:
 *  range of x coordinate (xFrom,xTo)
 *  range of y coordinate (yFrom,yTo)
 *
 * return:
 *  double array(2): [0] -> x coordinate
 *                   [1] -> y coordinate
 *
 */
double* generatePoint(double xFrom, double xTo, double yFrom, double yTo)
{
  static double point[2];

  point[0] = generateCoordinate(xFrom, xTo);
  point[1] = generateCoordinate(yFrom, yTo);

  return point;
}

/**
 * parameters:
 *  range of a coordinate (from,to)
 *
 * return:
 *  double: coordinate
 *      
 */
double generateCoordinate(double from, double to)
{
  return (double)rand() / RAND_MAX * (to-from) + from;
}

double function1(double x)
{
  return pow(sin(2*x),3)+4;
}

double function2(double x)
{
  return 2*x*log(pow(x,2));
}

double function3(double x)
{
  return 4*pow(x,3)+3*pow(x,2)+2*x+1;
}

double function4(double x)
{
  return 2*x/(pow(x,2)+5);
}