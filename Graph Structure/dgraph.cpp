#ifndef DGRAPH_CPP
#define DGRAPH_CPP
//*********************************************************************
//  CS311 Graph Traversal HW7 - by Nathan Padilla
//  Complier:  g++ compiler
//  directed graph implementation file dgraph.cpp
//*********************************************************************
#include "dgraph.h"

// Constructor
dgraph::dgraph() {
  for (int i=0; i<SIZE; i++)
    {
      Gtable[i].vertexName = ' ';
      Gtable[i].visit = 0;
      Gtable[i].outDegree = 0;
    }
  countUsed = 0;
}

// Destructor (it'll just use the llist.h destructor)
dgraph::~dgraph()
{

}

// PURPOSE: Displays the graph of vertices. If there are no 
//  vertices then return an error.
// ALGORITHM: display header then display each row after
void dgraph::displayGraph() {
  if (countUsed == 0) // empty graph
    cout << "ERROR: graph table is empty" << endl;
  cout << "---------GRAPH TABLE----------" << endl;
  cout << "Name Outdegree Visit# Adjacent" << endl;
  for (int i=0; i < countUsed; i++) // number of list heads
  { 
    cout << Gtable[i].vertexName << "    ";
    cout << Gtable[i].outDegree << "         ";
    cout << Gtable[i].visit << "      ";
    (Gtable[i].adjacentOnes).displayAll();
  }
}

// PURPOSE: Fills in the graph table with all the vertices
//  and the vertices information. If the table is full throw
//  an error.
// ALGORITHM: Check if table is full, then Open the file and
//  insert all vertices. Increment the count of vertices for
//  each added vertex.
void dgraph::fillTable() {
  if (countUsed == SIZE) // graph table is full
    throw OverFlow();
  ifstream fin; // open the table file
  fin.open("table.txt");
  char x; // the ajacant vertex if any exists
  int slot = 0; // to hold the index of each list head
  while (fin >> Gtable[slot].vertexName) // if I can read the name
    { 
      countUsed++; // increment the countUsed;
      fin >> Gtable[slot].outDegree;
      // Then for the outDegree times do the following:
      for (int i=0; i < Gtable[slot].outDegree; i++)
	{
	  fin >> x; // reads in the adjacent vertex
       	  // this uses a slist function from HW3
	  (Gtable[slot].adjacentOnes).addRear(x);
	}
      slot++; // increment to next list head
    } // end while
  fin.close(); // close the table file
}

// PURPOSE: finds the out degree of a given vertex and 
//  returns the out degree of that given vertex.
// HOW TO CALL: pass the vertex that you want to know its 
//  out degree.
// ALGORITHM: If passed parameter is invalid or not found, 
//  return error. Otherwise search for list head then return
//  the found out degree.
int dgraph::findOutDegree(char v) {
  if (countUsed == 0) // graph table is empty
    throw UnderFlow();
  v = toupper(v); // uppercase any lowercased search parameter
  if ((v < 'A') || (v > 'Z')) // value is invalid
    throw OutOfRange();
  for (int i=0; i< countUsed; i++) // search through list head
    {
      if (v == Gtable[i].vertexName) // matches vertex
	{
	  return Gtable[i].outDegree; // return out degree
	}
    }
  throw NotFound(); // vertex is not on the graph
}

// PURPOSE: finds the adjacent vertices of a given vertex and
//  returns the adjacent ones of that given vertex.
// HOW TO CALL: pass the vertex that you want to know its
//  adjacnet vertices.
// ALGORITHM: If passed parameter is invalid or not found,
//  return error. Otherwise search for list head then return
//  the found slist with the adjacent vertices.
slist dgraph::findAdjacency(char v) {
  if (countUsed == 0) // graph table is empty
    throw UnderFlow();
  v = toupper(v); // uppercase any lowercased search parameter
  if ((v < 'A') || (v > 'Z')) // value is invalid
    throw OutOfRange();
  for (int i=0; i< countUsed; i++) // search through list head
    {
      if (v == Gtable[i].vertexName) // matches vertex
        {
          return Gtable[i].adjacentOnes; // return adjacent vertices
        }
    }
  throw NotFound(); // vertex is not on the graph
}

// PURPOSE: Marks the given vertex with the given visit number
// HOW TO CALL: pass the visit number and vertex name.
// ALGORITHM:  If passed parameter is invalid or not found,
//  return error. Otherwise search for given list head then
//  mark the visit number as the given visit number parameter.
void dgraph::visit(int vis, char v) {
  if (countUsed == 0) // graph table is empty
    throw UnderFlow();
  v = toupper(v); // uppercase any lowercased search parameter
  if ((v < 'A') || (v > 'Z')) // value is invalid
    throw OutOfRange();
  for (int i=0; i< countUsed; i++) // search through list head
    {
      if (v == Gtable[i].vertexName) // matches vertex
	{
	  Gtable[i].visit = vis;
	  return;
	}
    }
  throw NotFound(); // vertex is not on the graph
}

// PURPOSE: Checks if the given vertex is visited or marked
// HOW TO CALL: pass the vertex you wish to check if marked
// ALGORITHM:  If passed parameter is invalid or not found,
//  return error. Otherwise search for the given list head 
//  and check if it is marked or not.  If it is return true
//  otherwise return false.
bool dgraph::isMarked(char v) {
  if (countUsed == 0) // graph table is empty
    throw UnderFlow();
  v = toupper(v); // uppercase any lowercased search parameter
  if ((v < 'A') || (v > 'Z')) // value is invalid
    throw OutOfRange();
  for (int i=0; i< countUsed; i++) // search through list head
    {
      if ((v == Gtable[i].vertexName) && (Gtable[i].visit > 0)) // matches vertex
        {
          return true;
        }
    }
  return false;
}

#endif
