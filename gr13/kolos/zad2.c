#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 50;

struct node{
  double x;
  struct node* next;
};

double allocate();

void printR(struct node* head1,struct node* head2);
void printI(struct node* head);

int main()
{
  struct node* head1,head2;
  struct node* p1,p2;
  int j,i = 0;

  head1 = allocate();

  p1 = head1;
  while(p1->next)
  {
    i++;
    p1 = p1->next;
  }

  head2 = p1;
  p2 = head2;
  i--;
  p1 = head1;

  while(p1 && i>0)
  {
    for(j=0;j<i;j++)
    {
      p1 = p1->next;
    }

    i--;
    p2->next = p1;
    p2 = p2->next;
    p1 = head1;
  }

  printR(head1);
  printI(head1);

  return 0;
}

void printR(struct node* head1,struct node* head2)
{
  if(head1)
  {
    printf("%lf => ",head->x);
    printR(head->next);
  }
  
}

void printI(struct node* head)
{
  struct node* p1 = head;

  while(p1)
  {
    printf("%lf => ",p1->x);
    p1 = p1->next;
  }
}

int fun()
{
  struct node* head1;
  struct node* p1,p2,p3;

  head1 = allocate();

  p1 = head1;
  p2 = p1->next;
  p3 = p2->next;

  while(p3)
  {
    p2->next = p1;
    p1 = p2;
    p2 = p3;
    p3 = p3->next;
  }
  
  p2->next = p1;
}
