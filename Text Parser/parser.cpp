#ifndef PDA_CPP
#define PDA_CPP
// Project 2 PDA simulation
// By Nathan Padilla
// CS421 11/26/14
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

//PURPOSE: function that extracts the input string from file
string extractString();

//exception class for syntactically incorrect sequences
class invalidString{};

int main()
{
  stack<char> theStack; // the stack
  string inputString = extractString(); // retrieve file string
  try // run simulation
    {
      // runs the length of the string
      for (int i = 0; i < inputString.size(); i++)
	{
	  char x = inputString[i];
	  if (x == 'i')
	    {
	      theStack.push('i');
	      i++;
	    }
	  else if ((x == 'e') && !theStack.empty())
	    {
	      theStack.pop();
	      i += 3;
	    }
	  else if ((x == 'e') && theStack.empty())
	    {
	      throw invalidString();
	    }
	}
      cout << "Correct sequence" << endl;
    }
  catch (invalidString)
    {
      cerr << "Sequence is syntactically incorrect" << endl;
    }
  return 0;
}

string extractString()
{
  ifstream fin;
  string input; // the input string
  fin.open("sequence.txt");
  fin >> input;
  fin.close();
  return input;
}

#endif
