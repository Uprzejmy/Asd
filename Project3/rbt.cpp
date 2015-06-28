#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

struct node
{
  struct node* left;
  struct node* right;
  struct node* up;
  int key;
  char color;
};

void addElement(struct node *& tree, int key, struct node* sentinel);
void rotateLeft(struct node* tree, struct node* b, struct node* sentinel);
void rotateRight(struct node* tree, struct node* b, struct node* sentinel);
void printTree(struct node* root, struct node* sentinel);
struct node* search(struct node* tree, int key, struct node* sentinel);
void printNode(struct node* element, struct node* sentinel);
struct node* findSuccesor(struct node* element, struct node* sentinel);
struct node* findMin(struct node* tree, struct node* sentinel);
void removeElement(struct node* tree, struct node* element, struct node* sentinel);
void deleteTree(struct node *& tree, struct node* sentinel);

int main()
{
  int i;
  //these numbers are just for an example
  //we could use random integers, but it's easier to check if functions work properly using always the same values
  int input[] = {5,2,7,3,9,8,6,4,1};
  struct node* tree;
  struct node* p;

  //it's just a null leaf
  struct node sentinel;
  sentinel.color = 'B';
  sentinel.up = &sentinel;
  sentinel.left = &sentinel;
  sentinel.right = &sentinel;

  //initialize the tree with null
  tree = &sentinel;

  for(i=0;i<9;i++)
  {
    addElement(tree,input[i],&sentinel);
  }

  printTree(tree,&sentinel);
  cout << "\n";

  p = search(tree,3,&sentinel);
  printNode(p,&sentinel);
  cout << "\n";
  removeElement(tree,p,&sentinel);
  printTree(tree,&sentinel);

  deleteTree(tree, &sentinel);

  return 0;
}

void addElement(struct node *& tree, int key, struct node* sentinel)
{
  struct node * element;
  struct node * p; 

  element = new struct node;    
  element->left = sentinel;        
  element->right = sentinel;
  element->up = tree;
  element->key = key;
  if (element->up == sentinel) 
    tree = element; //tree is empty
  else
  //find the leaf
  while (true)
  {
    if (key < element->up->key)
    {
      if (element->up->left == sentinel)
      {
        element->up->left = element; 
        break;
      }
      element->up = element->up->left;
    }
    else
    {
      if (element->up->right == sentinel)
      {
        element->up->right = element;
        break;
      }
      element->up = element->up->right;
    }
  }
  element->color = 'R';
  while ((element != tree) && (element->up->color == 'R'))
  {
    if (element->up == element->up->up->left)
    {
      p = element->up->up->right;

      //case 1
      if (p->color == 'R')
      {
        element->up->color = 'B';
        p->color = 'B';
        element->up->up->color = 'R';
        element = element->up->up;
        continue;
      }

      //case 2
      if (element == element->up->right)
      {
        element = element->up;
        rotateLeft(tree,element,sentinel);
      }

      //case 3
      element->up->color = 'B';
      element->up->up->color = 'R';
      rotateRight(tree,element->up->up,sentinel);
      break;
    }
    else
    { 
      //symetrical cases
      p = element->up->up->left;

      //case 1
      if (p->color == 'R')
      {
        element->up->color = 'B';
        p->color = 'B';
        element->up->up->color = 'R';
        element = element->up->up;
        continue;
      }

      //case 2
      if (element == element->up->left)
      {
        element = element->up;
        rotateRight(tree,element,sentinel);
      }

      //case 3
      element->up->color = 'B';
      element->up->up->color = 'R';
      rotateLeft(tree,element->up->up,sentinel);
      break;
    }
  }
  tree->color = 'B';
}

void rotateLeft(struct node* tree, struct node* b, struct node* sentinel)
{
  struct node* a;
  struct node* x;

  x = b->right;
  if(x != sentinel)
  {
    a = b->up;
    b->right = x->left;
    if(b->right != sentinel)
      b->right->up = b;

    x->left = b;
    x->up = a;
    b->up = x;

    if(a != sentinel)
    {
      if(a->left == b)
        a->left = x;
      else
        a->right = x;
    }
    else
      tree = x;
  }
}

void rotateRight(struct node* tree, struct node* b, struct node* sentinel)
{
  struct node * a;
  struct node * x;

  x = b->left;
  if (x != sentinel)
  {
    a = b->up;
    b->left = x->right;
    if (b->left != sentinel) 
      b->left->up = b;

    x->right = b;
    x->up = a;
    b->up = x;

    if (a != sentinel)
    {
      if (a->left == b) 
        a->left = x; 
      else 
        a->right = x;
    }
    else 
      tree = x;
  }
}

//in-order
//up->key for root is a "random" integer
void printTree(struct node* tree, struct node* sentinel)
{
  if(tree != sentinel) {
    if(tree->left != sentinel) 
      printTree(tree->left, sentinel);

    cout<< tree->key << " " << tree->color << " up->key: " << tree->up->key << "\n";

    if(tree->right != sentinel) 
      printTree(tree->right, sentinel);

  }
}

void printNode(struct node* element, struct node* sentinel)
{
  if(element != sentinel) {
    cout << "key: "<<element->key << "\n" << "up-key: " << element->up->key << "\n" <<"left-key: "<< element->left->key << "\n" <<"right-key: "<<element->right->key << "\n";
  }
}

struct node* search(struct node* tree, int key, struct node* sentinel)
{
  struct node* p;

  p = tree;

  while ((p != sentinel) && (p->key != key))
  {
    if (key < p->key) 
      p = p->left;
    else
      p = p->right;
  }
  
  if (p == sentinel) return NULL;

  return p;
}

struct node* findSuccesor(struct node* element, struct node* sentinel)
{
  struct node* p;

  if(element != sentinel)
  {
    if(element->right != sentinel)
      return findMin(element->right,sentinel);
    else
    {
      p = element->up;
      while((p != sentinel) && (element == p->right))
      {
        element = p;
        p = p->up;
      }

      return p;
    }
  }

  return sentinel;
}

struct node* findMin(struct node* tree, struct node* sentinel)
{
  struct node* p = tree;

  if(p != sentinel)
    while(p->left != sentinel)
      p = p->left;

  return p;
}

void removeElement(struct node* tree, struct node* element, struct node* sentinel)
{
  struct node* a;
  struct node* b;
  struct node* c;

  if ((element->left == sentinel) || (element->right == sentinel)) 
    b = element;
  else
    b = findSuccesor(element,sentinel);

  if (b->left != sentinel)
    c = b->left;
  else
    c = b->right;

  c->up = b->up;

  if (b->up == sentinel) 
    tree = c;
  else if (b == b->up->left) 
    b->up->left = c;
  else                      
    b->up->right = c;

  if (b != element) 
    element->key = b->key;

  if (b->color == 'B')   // repair the structure
  while ((c != tree) && (c->color == 'B'))
  if (c == c->up->left)
  {
    a = c->up->right;

    if (a->color == 'R')
    {
      //case 1
      a->color = 'B';
      c->up->color = 'R';
      rotateLeft(tree, c->up, sentinel);
      a = c->up->right;
    }

    if ((a->left->color == 'B') && (a->right->color == 'B'))
    { 
      //case 2
      a->color = 'R';
      c = c->up;
      continue;
    }

    if (a->right->color == 'B')
    { 
      //case 3
      a->left->color = 'B';
      a->color = 'R';
      rotateRight(tree, a, sentinel);
      a = c->up->right;
    }

    //case 4
    a->color = c->up->color;
    c->up->color = 'B';
    a->right->color = 'B';
    rotateLeft(tree, c->up, sentinel);
    //end of while after this line
    c = tree;    
  }     
  else  //symetrical cases
  { 
    a = c->up->left;

    if (a->color == 'R')
    { 
      //case 1
      a->color = 'B';
      c->up->color = 'R';
      rotateRight(tree, c->up,sentinel);
      a = c->up->left;
    }

    if ((a->left->color == 'B') && (a->right->color == 'B'))
    { 
      //case 2
      a->color = 'R';
      c = c->up;
      continue;
    }

    if (a->left->color == 'B')
    { 
      //case 3
      a->right->color = 'B';
      a->color = 'R';
      rotateLeft(tree, a, sentinel);
      a = c->up->left;
    }

    //case 4
    a->color = c->up->color;
    c->up->color = 'B';
    a->left->color = 'B';
    rotateRight(tree, c->up, sentinel);
    //end of while after this line
    c = tree;
  }

  c->color = 'B';

  delete b;
}

void deleteTree(struct node *& tree, struct node* sentinel)
{
  if(tree != sentinel)
  {
    deleteTree(tree->left, sentinel);
    deleteTree(tree->right, sentinel);
    delete tree;
  }
  
  return;
}