/**
 * Program sortuje wygenerowane zbiory
 *
 * autor: Łukasz Merynda
 * kontakt: lmerynda@gmail.com
 *
 * kompilowalem g++ -g -Wall sortowanie.cpp -o sortowanie
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 20

void quicksort(int array[], int p, int k);
int partition(int array[], int p, int k);

void heapsort(int array[], int n);
void buildHeap(int array[], int n);
void destroyHeap(int array[], int n);

void shellsort(int array[], int n);

void bubblesort(int array[], int n);

void insertsort(int array[], int n);

void selectsort(int array[], int n);

void printArray(int array[], int p, int k);
void swap(int &a,int &b);
void copyArray(int from[], int to[]);
void fillArrayFromFile(int array[], int n);
void writeDataToFile(int n);

int main()
{

  int array[N+1];
  int i;

  srand(time(NULL));

  writeDataToFile(N);
  fillArrayFromFile(array, N);


  printf("Poczatkowa tablica\n");
  printArray(array,0,N-1);


  //quicksort
  printf("Quicksort\n");
  fillArrayFromFile(array, N);
  quicksort(array,0,N-1);
  printArray(array,0,N-1);


  //heapsort
  printf("Heapsort\n");
  fillArrayFromFile(array, N);
  for(i=N;i>0;i--)//it's easier to use indexes from 1 to N rather than from 0 to N-1 in heapsort
  {
    array[i] = array[i-1];
  }
  heapsort(array,N);
  printArray(array,1,N);


  //shellsort
  printf("Shellsort\n");
  fillArrayFromFile(array, N);
  shellsort(array,N);
  printArray(array,0,N-1);
  

  //bubblesort
  printf("Bubblesort\n");
  fillArrayFromFile(array, N);
  bubblesort(array,N);
  printArray(array,0,N-1);


  //insertsort
  printf("Insertsort\n");
  fillArrayFromFile(array, N);
  insertsort(array,N);
  printArray(array,0,N-1);


  //selectsort
  printf("Selectsort\n");
  fillArrayFromFile(array, N);
  selectsort(array,N);
  printArray(array,0,N-1);


  return 0;
}

void selectsort(int array[], int n)
{
  int i,j,min;

  for(i=0;i<n;i++)
  {
    min = i;

    for(j=i+1;j<n;j++)
    {
      if(array[j]<array[min])
        min = j;
    }

    swap(array[min],array[i]);
  }
}

void insertsort(int array[], int n)
{
  int i,j,x;

  for(i=n-2;i>=0;i--)
  {
    x = array[i];
    j = i+1;

    while((j<n) && (x>array[j]))
    {
      array[j-1] = array[j];
      j++;
    }

    array[j-1] = x;
  }

  return;
}

void bubblesort(int array[], int n)
{
  int i,j,f;

  for(i=n-1;i>0;i--)
  {
    f = 1;
    for(j=0;j<i;j++)
    {
      if(array[j]>array[j+1])
      {
        f = 0;
        swap(array[j],array[j+1]);
      }
    }

    if(f)
      return;
  }

  return;
}

void heapsort(int array[], int n)
{
  //parent(i) = i/2
  //left(i) = 2*i
  //right(i) = 2*i + 1

  buildHeap(array,n);
  destroyHeap(array,n);

  return;
}

void buildHeap(int array[], int n)
{
  int i,j,k,x;

  for(i=2;i<=n;i++)//it's easier to use indexes from 1 to n rather than from 0 to n-1
  {
    j = i;
    k = j/2;
    x = array[i];

    while(k>0 && array[k]<x)
    {
      array[j] = array[k];
      j = k;
      k /= 2;
    }

    array[j] = x;
  }

  return;
}

void destroyHeap(int array[], int n)
{
  int i,j,k,c;

  for(i=n;i>=2;i--)
  {
    swap(array[1],array[i]);
    j=1;
    k=2;
    while(k<i)
    {
      if((k+1<i) && (array[k+1]>array[k]))
        c = k+1;
      else
        c = k;

      if(array[c]<=array[j])
        break;//break the while

      swap(array[c],array[j]);
      j = c;
      k = 2*j;
    }
  }

  return;
}

void quicksort(int array[], int p, int k)
{
  int s = partition(array,p,k);
  if(p<s-1)
    quicksort(array,p,s-1);
  if(s+1<k)
    quicksort(array,s+1,k);

  return;
}

int partition(int array[], int p, int k)
{
  int x;//pivot
  int i,j;//j first index with higher element than pivot

  x = array[(p+k)/2];
  array[(p+k)/2] = array[k];

  j = p;

  for(i=p;i<k;i++)
  {
    if(array[i]<x)
    {
      swap(array[i],array[j]);
      j++;
    }
  }

  array[k] = array[j];
  array[j] = x;

  return j;
}

void shellsort(int array[], int n)
{

  int i,j,tmp,interval;

  for (interval = n/2;interval>0;interval /= 2)
  {
    for (i = interval; i < n; ++i)
    {
      tmp = array[i];
      for (j=i; j>=interval && tmp<array[j-interval]; j -= interval)
      {
        array[j] = array[j-interval];
      }
      array[j] = tmp;
    } 
  }
}

void printArray(int array[], int p, int k)
{
  int i;

  for(i=p;i<=k;i++)
  {
    printf("%d ",array[i]);
  }

  printf("\n");

  return;
}

void swap(int &a, int &b)
{
  int tmp = a;
  a = b;
  b = tmp;

  return;
}

void copyArray(int from[], int to[])
{
  int i;

  for(i=0;i<N+1;i++)
  {
    to[i] = from[i];
  }

  return;
}

void writeDataToFile(int n)
{
  int i;

  FILE* fop;

  fop=fopen("dane.txt", "w");

  for(i=0;i<n;i++)
  {
    fprintf(fop, "%d\n", rand()%201-100);
  }

  fclose(fop);

  return;
}

void fillArrayFromFile(int array[], int n)
{
  int i;

  FILE* fip;

  fip=fopen("dane.txt", "r");

  for(i=0;i<n;i++)
  {
    fscanf(fip, "%d\n", &array[i]);
  }

  fclose(fip);

  return;
}