#ifndef DGRAPH_H
#define DGRAPH_H
//*********************************************************************
//  CS311 Graph HW7 - by Nathan Padilla
//  Complier:  g++ compiler
//  directed graph header file dgraph.h
//*********************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include "slist.h"
using namespace std;

const int SIZE = 20; // the size of the graph table

// this will be in each GTable slot
struct Gvertex
{
  char vertexName;      // the vertex Name
  int outDegree;        // the Out degree
  slist adjacentOnes;   // the adjacent vertices in an slist
  int visit;            // This will hold the visit number in HW7
};

class dgraph
{
 private:
  Gvertex Gtable[SIZE]; // the actual graph table
  int  countUsed; // how many slots of the Gtable are actually used
 public:
  // error checks for client file
  class OverFlow{};
  class UnderFlow{};
  class OutOfRange{};
  class NotFound{};

  dgraph();    // constructor

  ~dgraph();   // destructor but it is not needed

  // PURPOSE: Fills in the graph table with all the vertices
  //  and the vertices information. If the table is full throw
  //  an error.
  void fillTable();

  // PURPOSE: Displays the graph of vertices. If there are no
  //  vertices then return an error.
  void displayGraph();

  // PURPOSE: finds the out degree of a given vertex and
  //  returns the out degree of that given vertex.
  // HOW TO CALL: pass the vertex that you want to know its
  //  out degree.
  int findOutDegree(char); 

  // PURPOSE: finds the adjacent vertices of a given vertex and
  //  returns the adjacent ones of that given vertex.
  // HOW TO CALL: pass the vertex that you want to know its
  //  adjacent vertices.
  slist findAdjacency(char);

  // PURPOSE: Marks the given vertex with the given visit number
  // HOW TO CALL: pass the visit number and vertex name.
  void visit(int, char);

  // PURPOSE: Checks if the given vertex is visited or marked
  // HOW TO CALL: pass the vertex you wish to check if marked
  bool isMarked(char);
};
#endif
