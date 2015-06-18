#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 50

struct node{
  double x;
  struct node* next;
};

struct node* HEAD;
double TAB[N];

double czytaj();

int main()
{
  struct node* p1;
  struct node* p2;
  int i;

  p1 = (struct node*)malloc(sizeof(struct node));
  p1->x = (czytaj()+czytaj()+czytaj())/3;
  HEAD = p1;

  for(i=0;i<(N-1)/3;i++)
  {
    p2 = (struct node*)malloc(sizeof(struct node));
    p2->x = (czytaj()+czytaj()+czytaj())/3;
    p1->next = p2;
    p1 = p1->next;
  }

  int j;

  for(j=0;j<(N/3);j++)
  {
    TAB[j] = (czytaj()+czytaj()+czytaj())/3;
  }


  return 0;
}

double czytaj()
{
  return 1.0;
}