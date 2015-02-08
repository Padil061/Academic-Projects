#ifndef STACK_H
#define STACK_H
// =======================================================

// HW1P1
// Your name: Nathan Padilla
// Compiler:  g++ compiler
// File type: header file for stack.h

//=======================================================
#include <vector>
using namespace std;

typedef char el_t;      // the el_t type is int for now
                      // el_t is unknown to the client

class stack
  { 
   private: // to be hidden from the client
        vector <el_t> el;       // el is a vector of el_t's

   public: // prototypes to be used by the client

        // exception handling classes  
        class Overflow{};
        class Underflow{};

      	stack();   // constructor
      	~stack();  // destructor  

        // HOW TO CALL: pass the element to be pushed
        // PURPOSE: if not full, enters an element at the top;
        //          otherwise throws an exception - Overflow
        void push(el_t);

        // HOW TO CALL: provide variable to receive the popped element
        // PURPOSE: if not empty, removes and gives back the top element;
        //          otherwise throws an exception - Underflow
        void pop(el_t&);

        // HOW TO CALL: provide variable to recieve copy of top
        // PURPOSE: if not empty, gives the top element without removing it;
        //          otherwise, throws an exception - Underflow
        void topElem(el_t&);

        // PURPOSE: to determine if the stack is empty or not;
        //          true if empty, false otherwise.
      	bool isEmpty();

	// PURPOSE: returns true if stack is full, otherwise false
      	bool isFull();

	// PURPOSE: display everything in the queue from front to rear
	//          enclosed in []
	//          if empty, displays [ empty ]
        void displayAll();

	// clearIt pops all elements from the stack to make it empty if it is not empty yet
        void clearIt();
        
  };  

// Note: semicolon is needed at the end of the header file
#endif
