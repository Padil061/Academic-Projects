//based on Yoshii  CS311  Notes-6B
//====================================================
//  CS311 Search Linked List HW3P2 - by Nathan Padilla
//Complier:  g++ compiler
//File type: implementation file slist.cpp
//====================================================

#ifndef SLIST_CPP
#define SLIST_CPP
#include "slist.h"

//Constructor
slist::slist()
{ Front=NULL;
  Rear=NULL;
  count = 0; }

// to create a new object this-> as a copy of the Original
slist::slist(const slist& Original)
{
  //  this->'s data members need to be initialized first
  this->Front=NULL;
  this->Rear=NULL;
  this->count = 0;

  //  this-> object has to be built up by allocating new cells
  //  and copying the values from Original into each cell as we did with 
  Node* P = Original.Front;  // local pointer for copying Original
  while (P != NULL)  // copy all of Original
    {
      this->addRear(P->elem);    //P’s element is added to this->
      P = P->Next;               // Go to the next node in OtherOne   
    } 
}


// PURPOSE: Search through the list to see if any node
//  contains Key. If so, return its position (>=1). 
//  Otherwise, return 0.
// HOW TO CALL: Provide the element you wish to search for
int slist::search(el_t Key)
{
  Node *curr = Front; // pointer for traversing the list
  int position=1; // returned integer of position
  while (curr != Rear -> Next) // go through the list
    {
      if (curr -> elem == Key) // found the key
	return position;
      else // move to next element on list
	{ 
	  curr = curr -> Next;
	  position++;
	}
    }
  return 0; // didn't find the key after searching
}

// PURPOSE: Go to the Ith node (I is between 1 and Count)
//  and replace the element there with Elem. If I was an
//  illegal value, throw an exception.
// HOW TO CALL: Provide the element you want to replace
//  with and the position to replace the previous element
void slist::replace(el_t Elem, int I)
{
  Node *curr = Front; // pointer for traversing the list
  if (isEmpty()) // check if the list was empty
    throw Underflow();
  if ((I < 1) || (I > count)) // check if legal value
    throw OutOfRange();
  for (int c=1; c < I; c++) // move pointer to position
    curr = curr -> Next;
  curr -> elem = Elem; // replace element
}


slist& slist::operator=(const slist& otherOne)
{
  el_t oldNum;
  // First make sure this-> and OtherOne are not the same object.
  // To do this, compare the pointers to the objects .
  if (&otherOne != this)  // if not the same
    {
      // this-> object has to be emptied first.
      while (! this->isEmpty() )
	this->deleteRear(oldNum);  
      Node* P;  // local pointer for OtherOne
      P = otherOne.Front;
      while (P != NULL)  // add each element of otherOne 
        {
	  this->addRear(P->elem);    //P’s element is added to this->
	  P = P->Next;               // Go to the next node in OtherOne   
	} 
    }// end of if              
  return *this;    // return the result unconditionally.
}

// overloading ==
// The operator == does not work well with pointers
bool slist::operator==(slist& otherOne) const
{
  Node* ours = this->Front;
  Node* theirs = otherOne.Front;
  if ((this->Front==NULL) && (otherOne.Front==NULL))
    return true;
  while ((ours != NULL) && (theirs != NULL))
    {
      if (ours -> elem != theirs -> elem)
	return false;
      else
	{
	  ours = ours -> Next;
	  theirs = theirs -> Next;
	}
    }
  if ((ours == NULL) && (theirs == NULL))
    return true;
  else
    return false;
}

#endif
