//based on Yoshii  CS311  Notes-6A
//====================================================
//  CS311 Linked List HW3P1 - by Nathan Padilla
//Complier:  g++ compiler
//File type: implementation file llist.cpp
//====================================================

#ifndef LLIST_CPP
#define LLIST_CPP
#include "llist.h" 

//Constructor
llist::llist()
{ Front=NULL;
  Rear=NULL;
  count = 0; }

//Destructor
llist::~llist()
{ el_t X;
  while (!isEmpty()) deleteFront(X); }

// PURPOSE: returns true if queue is empty, otherwise false
bool llist::isEmpty()
{ if ((Front == NULL) && (Rear == NULL)) // if empty
    return true;
  else // otherwise it isn't empty
    return false; }

// PURPOSE: display everything in the queue from front to rear
//  enclosed in []
//  if empty, displays [ empty ]
void llist::displayAll()
{ if (!isEmpty()) // check if the list is empty
    { Node *curr = Front; // temp pointer used for display
      while(curr != Rear -> Next) // display all elements
	{ cout << "[ " << curr -> elem << " ] ";
	  curr = curr -> Next; }
      cout << endl; } //end if
  else // list was empty
    cout << "[ Empty ]" << endl; }

// PURPOSE: adds a new node to the rear or 'bottom' of the linked list
// HOW TO CALL: provide the value of the element to be added to the list
void llist::addRear(el_t NewNum)
{ if(!isEmpty()) // check if the list is empty
    { // add to rear like normal
      Rear -> Next = new Node;
      Rear = Rear -> Next;
      Rear -> elem = NewNum;
      Rear -> Next = NULL;
      count++; }
  else // no list, start new list
    { Rear = Front = new Node;
      Rear -> Next = NULL;
      Rear -> elem = NewNum;
      count++; }}

// PURPOSE: deletes a node at the front or 'top' of the linked list
//  and returns the old element value to the parameter
// HOW TO CALL: provide the variable you want to hold the old element
void llist::deleteFront(el_t& OldNum)
{ if (isEmpty()) // check if no list to delete from 
    throw Underflow();
  else // deletes the front node
    { OldNum = Front -> elem;	
      Node *Second; // temp pointer to the second node
      Second = Front -> Next;
      delete Front; 
      Front = Second;
      count--; }
  if (count == 0) // if no more elements on list, set pointers
    { Front = NULL; 
      Rear = NULL; }}

// PURPOSE: adds a new node to the front or 'top' of the linked list
// HOW TO CALL: provide the value of the element to be added to the list
void llist::addFront(el_t NewNum)
{ if (isEmpty()) // list was empty, start new list
    { Node *x = new Node; // temp pointer to hold the new node
      Front = x;
      Rear  = x;
      Front -> elem = NewNum;
      Front -> Next = NULL;
      count ++; }
  else // make a new front on the current list
    { Node *x = new Node; // temp pointer to hold the new node
      x->Next = Front;
      Front = x;
      Front->elem = NewNum;
      count++; }}

// PURPOSE: deletes a node at the rear or 'bottom' of the linked list
//  and returns the old element value to the parameter
// HOW TO CALL: provide the variable you want to hold the old element
void llist::deleteRear(el_t& OldNum)
{
  if (isEmpty()) // check if there is anything to delete
    throw Underflow();
  else if (count == 1) // if there is only one node
    { OldNum = Front->elem;
      delete Front;
      Rear = Front = NULL;
      count --; }
  else // if there is 2 or more nodes in the list
    { OldNum = Rear->elem;
      Node *p = Front; // temp pointer to point just before rear
      while(p->Next!=Rear) // point to node before rear
	p=p->Next;
      delete Rear;
      Rear = p;
      Rear->Next=NULL;
      count--; }}

// PURPOSE: deletes a node at the 'i' position on the linked list.
//  Also returns the old element value to the parameter
// HOW TO CALL: provide the index or position you want to delete and
//  also the variable you want to hold the old element deleted
void llist::deleteIth(int I, el_t& OldNum)
{
  if (I > count || I < 1) // check if in range
    throw OutOfRange();
  else if (isEmpty()) // check if there is anything to delete
    throw Underflow();
  if (count == 1) // check if only one node
    { deleteFront(OldNum);
      return; } 
  Node *curr = Front; // temp pointer to point just before Ith
  for (int j=1; j < I-1; j++) // point before Ith node
    { curr = curr -> Next; }
  if (curr == Front) // if deleting the front node
    { deleteFront(OldNum);
      return; }
  if ( curr->Next->Next != NULL) // if not deleting last node
    { Node *Secondary = curr -> Next -> Next; // to point just
      // after the node we want to delete
      OldNum = curr -> Next -> elem;
      delete curr -> Next;
      curr -> Next = Secondary;
      count--; }
  else // it was last node, delete last node
    deleteRear(OldNum);
  return; }

// PURPOSE: adds a new node just before the 'i' position on the
//  linked list.
// HOW TO CALL: provide the index or position you want to add an
// element before and also the variable you want to hold the old
// element deleted.
void llist::addbeforeIth(int I, el_t newNum)
{ if (I > count+1 || I < 1) // check if in range
    throw OutOfRange();
  else if (isEmpty()) // check if empty list
    addFront(newNum);
  if (count == 1) // if there is only one node
    { addFront(newNum);
      return; }
  Node *curr = Front; // temp pointer to point just before Ith
  for (int j=1; j<I-1;j++)
    { curr = curr -> Next; }
  if (curr == Front) // if it was the first element
    { addFront(newNum); }
  else if (curr == Rear) // if it was the last element
    { addRear(newNum); }
  else
    { Node *p = new Node; // temp pointer to hold new node
      p -> elem = newNum;
      p -> Next = curr -> Next;
      curr -> Next = p;
      count++; }}
#endif
