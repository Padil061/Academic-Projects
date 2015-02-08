#include<string>
#include<iostream>
#include<fstream>
#include"interpreter.h"
using namespace std;
/*****************************************************************/
/* PURPOSE: A pseudo code interpreter that translates pseudo code*/
/* IMPLEMENTED BY: Nathan Padilla                                */
/* EMAIL: padil061@cougars.csusm.edu                             */
/* COURSE: CS351                                                 */
/* INSTRUCTOR: Shaun-inn Wu                                      */
/* DATE: 2/1/2014                                                */
/* INPUT: Integer pseudo code from PseudoCodeTestProgram.txt     */
/* OUTPUT: Output data to screen                                 */
/*****************************************************************/

/*
class Interpreter
{
private:
  int memoryArray[2000];
  int initializedMem;
  int accumulator;
public:
  Interpreter();
  void printStatus(int position) const;
  void ProcessPseudoCode();
  void ExecutePseudoCode();
};
*/
Interpreter::Interpreter()
{
  accumulator = initializedMem = 0;
  for (int i = 0; i < 2000; i++)
    {
      memoryArray[i] = 0;
    }
}

int main()
{
  Interpreter PseudoInterpreter;
  PseudoInterpreter.ProcessPseudoCode();
  return 0;
}

/*****************************************************************/
/* PURPOSE: Reads in the psuedo code data from the input file    */
/* RATIONAE: hiding of data implementation by restricting access */
/* RETURN: Return after completion of program                    */
/*****************************************************************/
void Interpreter::ProcessPseudoCode()
{
  int cmd; //the pseudo code data and commands
  int count = 1000; //points to memory location for commands.
  ifstream fin; //used to open the file
  fin.open("PseudoCodeTestProgram.txt");
  if (!fin) //if file has no data, then show ERROR
    {
      cout << "ERROR: Transaction file does not exist" << endl;
      return;
    }
  while ((fin >> cmd) && (cmd != 9999)) //inputs the psuedo data
    {
      memoryArray[initializedMem] = cmd;
      initializedMem++;
    }
  while ((fin >> cmd) && (cmd != 9999)) //inputs the psuedo commands
    {
      if ((cmd >= 1000) && (cmd < 7000)) //check if a real command
	{ 
	  memoryArray[count] = cmd;
	  count++;
	}
    }
  fin.close();
  ExecutePseudoCode(); //all pseudo code taken from file, now translate
  return;
}

/***********************************************************************/
/* PURPOSE: interprets the commands from the command section in memory */
/* RATIONALE: First we read the commands in, now we interpret          */
/* RETURN: exits program                                               */
/***********************************************************************/
void Interpreter::ExecutePseudoCode()
{
  int cmd, data; //The pseudo code command and data used by the commands
  for (int pCount = 1000; pCount < 2000; pCount++) //check each command
    {
      cmd = data = memoryArray[pCount];
      if ((cmd >= 1000) && (cmd < 7000)) //check if real command
	{
	  cmd /= 1000;
	  data = data % 1000;
	  if (cmd == 1) //load data into accumulator
	    {
	      printStatus(pCount);
	      accumulator = data;
	    }	  
	  else if (cmd == 2) //move accumulator into data
	    {
	      printStatus(pCount);
	      memoryArray[data] = accumulator;
	    }
	  else if (cmd == 3) //add data into accumulator
	    {
	      printStatus(pCount);
	      accumulator += data;
	    }
	  else if (cmd == 4) //subtract data from accumulator
	    {
	      printStatus(pCount);
	      accumulator -= data;
	    }
	  else if (cmd == 5) //branch to other pseudo code command
	    {
	      printStatus(pCount);
	      if (accumulator > 0)
		{
		  pCount = data + 999; //branch to psuedo code at position data
		}
	    }
	  else if (cmd == 6) //exit the program
	    {
	      printStatus(pCount);
	      return;
	    }
	}	  
    }
}

/*****************************************************************/
/* PURPOSE: Prints all relevant data in the interpreter to screen*/
/* RATIONALE: seperate so it cannot edit values, only print them */
/* INPUT PARAMETERS: position means the current command in the   */
/* memory the interpreter is looking at                          */
/* OUTPUT PARAMETERS: outputs all relevant data from memory      */
/* RETURN: Returns to execute function for other commands        */
/*****************************************************************/
void Interpreter::printStatus(int position) const
{
  int codeCount = position - 1000; //the current position of the interpreter in the command memory
  cout << "ACC = " << accumulator;
  cout << " PC = " << codeCount;
  cout << " Next Instruction = " << memoryArray[position] << endl;
  cout << "Initialized Memory =";
  for (int i = 0; i < initializedMem; i++) //print out the data memory
    {
      cout << " " << i << ":" << memoryArray[i] << ",";
    }
  cout << endl;
}
