#include <stdio.h>
#include <stdlib.h>
#define N 50;

struct node{
  double x;
  struct node* next;
};

struct node* allocate();

void fun(struct node* head);
void printR(struct node* head);
void printI(struct node* head);

int main()
{
  struct node* head1;
  head1 = allocate();
  fun(head1);

  printR(head1);
  printI(head1);

  return 0;
}

void printR(struct node* head)
{
  if(!head)
    return;
  printf("<= %lf => ",head->x);
  printR(head->next);
  
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

void fun(struct node* head)
{
  struct node* p1;
  struct node* p2;
  struct node* p3;

  p1 = head;
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
