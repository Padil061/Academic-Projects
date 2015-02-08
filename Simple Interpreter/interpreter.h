#ifndef INTERPRETER_H
#define INTERPRETER_H

using namespace std;

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
#endif
