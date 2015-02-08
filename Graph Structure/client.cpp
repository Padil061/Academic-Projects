#ifndef CLIENT_CPP
#define CLIENT_CPP
//*********************************************************************
//  CS311 Graph HW6 - by Nathan Padilla
//  Complier:  g++ compiler
//  directed graph client file client.cpp
//  PURPOSE: to be able to find different properties of vertices on a 
//           directed graph 
//  TO COMPILE/RUN: g++ client.cpp llist.cpp slist.cpp dgraph.cpp
//                  ./a.out
//  ALGORITHM: check the users desired choice in a menu then run
//             the given method to display properties of the graph
//*********************************************************************
#include "dgraph.h"

int main()
{
  dgraph G;              // the directed graph
  slist l1;              // tempt list for holding adjacent vertices
  char charChoice = 'A'; // user choice for vertex
  int intChoice = 0;     // user choice for menu options
  int degree = 0;        // the returned out degree of a vertex
  G.fillTable();         // read from file and fill graph
  G.displayGraph();      // displays the graph
  while (intChoice != 9) // while not exiting the program, run it
    {
      cout << "======DIRECTED GRAPH======" << endl;
      cout << " 1. Find an Out Degree" << endl;
      cout << " 2. Find Adjacency " << endl;
      cout << " 9. Exit Program" << endl;
      cout << " Enter a number command: ";
      cin >> intChoice;
      try 
	{
	  switch(intChoice)
	    {
	    case 1: // find the out degree of a vertex
	      cout << "Enter vertex name for its out degree: ";
	      cin >> charChoice;
	      degree = G.findOutDegree(charChoice); // search
	      cout << "The degree of " << charChoice << " is " << degree << endl;
	      break;
	    case 2: // find the adjacent vertices
	      cout << "Enter vertex name for Adjacent vertices: ";
	      cin >> charChoice;
	      l1 = G.findAdjacency(charChoice); // search
	      cout << "The adjacent ones of vertex " << charChoice << " are: ";
	      l1.displayAll();
	      break;
	    default: // user entered invalid choice
	      cout << "OUTOFRANGE ERROR: entered value was invalid" << endl;
	    } // end switch
	} // end try
      // catchs for user errors
      catch(dgraph::UnderFlow)
	{
	  cerr << "UNDERFLOW ERROR: table is empty" << endl;
	}
      catch(dgraph::OverFlow)
	{
	  cerr << "OVERFLOW ERROR: table is already full" << endl;
	}
      catch(dgraph::OutOfRange)
	{
	  cerr << "OUTOFRANGE ERROR: entered value was invalid" << endl;
	}
      catch(dgraph::NotFound)
	{
	  cerr << "NOTFOUND ERROR: entered value wasn't found" << endl;
	}
    } // end while loop
  return 1; // exit program
}
#endif
