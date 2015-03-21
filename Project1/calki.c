#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int amountOfIntervals = 10000;
int amountOfSamples = 500000;
double* generatePoint(double xFrom, double xTo, double yFrom, double yTo);
double generateCoordinate(double from, double to);
double function1(double x);
double rectangleIntegration(double from, double to, double (*function)(double));
double trapeziumIntegration(double from, double to, double (*function)(double));
double monteCarloIntegration(double from, double to, double (*function)(double));
double findLocalMax(double from, double to, double (*function)(double));
double findLocalMin(double from, double to, double (*function)(double));

int main()
{
  double from,to;

  srand(time(NULL));

  printf("Podaj wartosci przedzialow, dla ktorych bedzie liczona calka\n");
  scanf("%lf %lf",&from,&to);
  printf("\n");

  printf("%lf\n",rectangleIntegration(from,to,&function1));
  printf("%lf\n",trapeziumIntegration(from,to,&function1));
  printf("%lf\n",monteCarloIntegration(from,to,&function1));


  return 0;
}

double rectangleIntegration(double from, double to, double (*function)(double))
{
  double interval = (to-from)/amountOfIntervals;
  double sum = 0;
  double x;

  for(x=from;x<to;x+=interval)
  {
    sum+=interval*function((x+interval)/2);
  }

  return sum;
}

double trapeziumIntegration(double from, double to, double (*function)(double))
{
  double interval = (to-from)/amountOfIntervals;
  double sum = 0;
  double x;

  for(x=from;x<to;x+=interval)
  {
    sum+=interval/2*(function(x)+function(x+interval));
  }

  return sum;
}

double monteCarloIntegration(double from, double to, double (*function)(double))
{
  int i,hits;
  double fx;
  double* point;

  double max = findLocalMax(from,to,*function);
  double min = findLocalMin(from,to,*function);

  for(i=0;i<amountOfSamples;i++)
  {
    point = generatePoint(from,to,min,max);
    fx = function(point[0]);
    if(fx>0)
    {
      if(point[1]<fx)
        hits++;
    }
    else if(fx<0)
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
  return (double)rand()/RAND_MAX * (to-from) + from;
}

double function1(double x)
{
  return pow(sin(2*x),3)+4;
}