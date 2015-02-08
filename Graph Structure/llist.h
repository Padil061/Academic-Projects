#ifndef LLIST_H
#define LLIST_H
//*********************************************************************
//  CS311 Linked List HW3P1 - by Nathan Padilla
//  Complier:  g++ compiler
//  Linked List Header File  llist.h
//*********************************************************************
#include <iostream>
using namespace std;

typedef char el_t ;

// list node is defined here as a struct Node
struct Node
{
  el_t elem;   // elem is the element stored
  Node   *Next;  // next is the pointer to the next node
};

class llist
{
 protected:
  Node *Front;       // front  pointer 
  Node *Rear;        // rear   pointer
  int  count;        // counter for the number of elements

 public:  
  // exception classes
  class Underflow{};
  class OutOfRange{};
    
  llist (); // constructor  
  ~llist(); // destructor
  
  // PURPOSE: returns true if queue is empty, otherwise false
  bool isEmpty();
  
  // PURPOSE: display everything in the queue from front to rear
  //  enclosed in []
  //  if empty, displays [ empty ]
  void displayAll();
    
  // PURPOSE: adds a new node to the rear or 'bottom' of the linked list
  // HOW TO CALL: provide the value of the element to be added to the list
  void addRear(el_t NewNum);
  
  // PURPOSE: deletes a node at the front or 'top' of the linked list
  //  and returns the old element value to the parameter
  // HOW TO CALL: provide the variable you want to hold the old element
  void deleteFront(el_t& OldNum);
  
  // PURPOSE: adds a new node to the front or 'top' of the linked list
  // HOW TO CALL: provide the value of the element to be added to the list
  void addFront(el_t NewNum);
    
  // PURPOSE: deletes a node at the rear or 'bottom' of the linked list
  //  and returns the old element value to the parameter
  // HOW TO CALL: provide the variable you want to hold the old element
  void deleteRear(el_t& OldNum);
    
  // PURPOSE: deletes a node at the 'i' position on the linked list. 
  //  Also returns the old element value to the parameter
  // HOW TO CALL: provide the index or position you want to delete and
  //  also the variable you want to hold the old element deleted
  void deleteIth(int I, el_t& OldNum);
    
  // PURPOSE: adds a new node just before the 'i' position on the 
  //  linked list.
  // HOW TO CALL: provide the index or position you want to add an
  // element before and also the variable you want to hold the old 
  // element deleted.
  void addbeforeIth(int I, el_t newNum);    
};
#endif
