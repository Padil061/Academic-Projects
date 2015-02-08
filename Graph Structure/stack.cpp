#ifndef STACK_CPP
#define STACK_CPP
// =========================================================

//HW1P1 stack
//Your name: Nathan Padilla
//Complier:  g++ compiler
//File type: implementation file stack.cpp

//================================================================
#include <iostream>
#include <vector>
#include "stack.h"
using namespace std;

// PURPOSE: Constructor must initialize top to be -1 to begin with.
stack::stack()
{ 
  // nothing to do
}

// PURPOSE: Destructor does not have to do anything since this is a static array.
stack::~stack()
{ 
  clearIt(); //clear the vector stack
}

// PURPOSE: isEmpty checks top and returns true if empty, false otherwise.
//    In the comment, make sure you define "empty" in terms of top.
bool stack::isEmpty()
{ if (el.size()-1 == -1) //checks if at the bottom of stack 
    return true; 
  else return false;
}
    
// PURPOSE: isFull checks top and returns true if full, false otherwise.
// In the comment, make sure you define "full" in terms of top.
bool stack::isFull()
{ return false;
}

// HOW TO CALL: pass the element to be pushed  
// PURPOSE: push calls isFull and if true, throws an exception (Overflow)
//   Otherwise, adds an element to el after incrementing top.
void stack::push(el_t elem)
{ if (isFull()) //check if full
    { throw Overflow(); }
  else { el.push_back(elem); }}
  
// HOW TO CALL: provide variable to receive the popped element
// PURPOSE: pop calls isEmpty and if true, throws an exception (Underflow)
//  Otherwise, removes an element from el and gives it back.
void stack::pop(el_t& elem)
{ if (isEmpty()) //check if empty
      { throw Underflow(); }
  else { elem = el.back(); el.pop_back(); }}

// HOW TO CALL: provide variable to recieve copy of top
// PURPOSE: topElem calls isEmpty and if true, throws an exception (underflow)
//    Otherwise, gives back the top element from el.
void stack::topElem(el_t& elem)
{ if (isEmpty()) //check if empty
    { throw Underflow(); }
  else { elem = el.back(); }}


// PURPOSE: dislayAll displays all the elements 
//  or if none then displays [ empty ].
//  Otherwise, diplays the elements vertically.
void stack::displayAll()
{  if (isEmpty()) //check if empty
      cout << "[ empty ]" << endl;
  else
    {
      cout << "-----------THE STACK----------" << endl;
      for (int i=0; i < el.size(); i++) //print elements
	{ 
	  cout << "[ " <<  el[i] << " ] "; 
	}
      cout << "<- TOP" << endl;
    }
}
// PURPOSE: clearIt pops all elements from the stack to make it
// empty if it is not empty yet
void stack::clearIt()
{
  while (!isEmpty())
    el.pop_back();
}      
#endif
