#ifndef SLIST_H
#define SLIST_H
//*********************************************************************
//  CS311 Search Linked List HW3P2 & HW3P3 - by Nathan Padilla
//  Complier:  g++ compiler
//  Linked List Header File  slist.h
//*********************************************************************
#include <iostream>
#include "llist.h"

using namespace std;


class slist: public llist
{
 public:

  slist(); // constructor

  // The copy constructor to allow pass by value and return
  // The regular copy constructor does not work well with pointers
  slist(const slist& otherOne);

  // PURPOSE: Search through the list to see if any node
  //  contains Key. If so, return its position (>=1).
  //  Otherwise, return 0.
  // HOW TO CALL: Provide the element you wish to search for
  int search(el_t Key);

  // PURPOSE: Go to the Ith node (I is between 1 and Count)
  //  and replace the element there with Elem. If I was an
  //  illegal value, throw an exception.
  // HOW TO CALL: Provide the element you want to replace
  //  with and the position to replace the previous element
  void replace(el_t Elem, int I);

  // overloading =
  // The operator = does not work well with pointers
  slist& operator=(const slist& otherOne);
  
  // overloading ==
  // The operator == does not work well with pointers
  bool operator==(slist& otherOne) const;
};
#endif
