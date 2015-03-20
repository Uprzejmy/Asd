#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int* generatePoint(int xFrom, int xTo, int yFrom, int yTo);
int generateCoordinate(int from, int to);

int main()
{
  srand(time(NULL));

  return 0;
}

/**
 * parameters:
 *  range of x coordinate (xFrom,xTo)
 *  range of y coordinate (yFrom,yTo)
 *
 * return:
 *  int array(2): [0] -> x coordinate
 *                [1] -> y coordinate
 */
int* generatePoint(int xFrom, int xTo, int yFrom, int yTo)
{
  static int point[2];

  point[0] = generateCoordinate(xFrom, xTo);
  point[1] = generateCoordinate(yFrom, yTo);

  return point;
}

/**
 * parameters:
 *  range of a coordinate (from,to)
 *
 * return:
 *  int: coordinate
 *          
 */
int generateCoordinate(int from, int to)
{
  return rand()%(to-from)+from;
}