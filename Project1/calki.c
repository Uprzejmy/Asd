#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double* generatePoint(double xFrom, double xTo, double yFrom, double yTo);
double generateCoordinate(double from, double to);

int main()
{
  srand(time(NULL));

  double* point;
  int i;

  for(i=0;i<50;i++)
  {
    point = generatePoint(0,2,0,5);

    printf("x = %lf, y = %lf \n",point[0],point[1]);
  }

  return 0;
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