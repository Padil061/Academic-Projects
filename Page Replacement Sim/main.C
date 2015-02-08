/******************************************************************************
NAME: Jimmy Joseph & Nathan Padilla
CS433 ASSIGNMENT-5
Description: We allow the users to enter the size of the page and the physical
memory size then we used different replacement policies while getting the conent
from the reference file.
No none assumptions.
Run the program by doing ./ass5 8 32 for <page size> <physical memory size>
******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sys/time.h>

using namespace std;

bool isARGValid(int argc, char * argv[]);//sees if command line argumetn is valid
bool issizeValid(char * s); //checks page size
bool isPhyMemSizeValid(char * s); //checks for valid memory
void Run(int size, int memSize); //runs the simulation

const string correctParams = "./ass5 <page size> <physical memory size>"; // correct parameter message
const int MEGABYTE = 1048576; //1 megabytes to 1,048,576 bytes

//represents the frame
struct Frame
{
  bool isFree; //true for free. false for taken.
  int Page; //the memory that owns this page
  Frame();
};

// represents a page table
struct ptEntry
{
  int isValid; //tells if its in physical memory
  int isDirty; //to tell if its a write
  int physFrame; //frame number
  int vMEM_pg; //reference page number
  ptEntry();
};

// deals with page replacement
class Page
{
protected:
  int size; //holds page size
  int phyMEM_sze; //holds physical size
  int memREF; //total num of memeory in reference
  int total_pageFaults; //total page faults
  int total_pageFlushes; //counts dirty pages
  unsigned int alloc_Frames; //keeps count of frames used
  vector <Frame> aval_frames; //known free frames
  vector <ptEntry> pT; //simulation of page table

  void insertPage(int first, int last, ptEntry pg); //puts page into table
  void prt_results(double beg, double end); //prints the results
  bool is_pg_virtual(int first, int last ,int pg);  //checks if a page is in the virtual memory or not
  void grantFrame(int & frameNum, int page); //assigns frame to page
  int get_pg_byNUM(int first, int last ,int pg);  //finds a pages index and returns it
  bool isOpenFrames(); //checks for any available frames
  virtual void handel_REF(int new_ref, bool write) = 0; //handles ref.
  virtual int dealloc_frame() = 0; //frees up a frame

 public:
  Page(int pSize, int memSize, int frameNum);
  void startSIM(); //begins replacement algorithm of pages
  virtual ~Page(){}; //destructor
};

// deals with the random
class RandomALG: public Page
{
 protected:
  virtual void handel_REF(int new_ref, bool write); //handles the ref.
  virtual int dealloc_frame(); //frees some frame

 public:
  RandomALG(int pSize, int memSize, int frameNum);
  virtual ~RandomALG(){}; //destructor
};

// deals with least recently used
class LRU: public Page
{
 protected:
  vector <int> lru_stk; //holds some least recently used frames
  virtual void handel_REF(int new_ref, bool write); // it handles the ref.
  virtual int dealloc_frame(); //frees some frame

 public:
  LRU(int pSize, int memSize, int frameNum);
  virtual ~LRU(){}; //destructor
};

// deals with first in first out
class Fifo: public Page
{
 protected:
  vector <int> fifo_que; //keeps track a page that will be replaced
  virtual void handel_REF(int new_ref, bool write); //it handles the ref.
  virtual int dealloc_frame(); //frees some frame

 public:
  Fifo(int pSize, int memSize, int frameNum);
  virtual ~Fifo(){};//destructor
};


int main(int argc, char * argv[])
{
  if (!isARGValid(argc, argv)) //arguments not valid then
    return 0; //stop program

  cout << "Jimmy Joseph & Nathan Padilla \n";
  cout << "#########   Fabulous II ###########\n";

  Run((int)pow(2.00, atoi(argv[1])), atoi(argv[2]) * MEGABYTE);
  return 0; 
}

// contents of a page
Frame::Frame()
{
  isFree = true; //free is free first
  Page = -1; //no ownership of frame
}

// checks if arguments valid
bool isARGValid(int argc, char * argv[])
{
  if (argc < 3) //if there aren't enough arguments
    {
      cout << "not enough arguments\n" << correctParams << endl;
      return false;
    }

  if (argc > 3) //if there are too many arguments
    {
      cout << "too many arguments\n" << correctParams << endl;
      return false;
    }

  if (!issizeValid(argv[1])) //wrong size display
    {
      cout << "invalid argument found\n" << correctParams << endl;
      cout << "*page size must be an int from 8 <--> 13, inclusive" << endl;
      return false;
    }


  if (!isPhyMemSizeValid(argv[2])) //wrong size
    {
      cout << "invalid argument found\n" << correctParams << endl;
      cout << "*physical memory choices: 4, 16, 32, or 64 megabytes" << endl;
      return false;
    }
  return true;
}

// check valid size
bool issizeValid(char * s)
{
  int i = 0; //get through char 
  while (s[i] != (char)NULL)
    {
      if (!isdigit(s[i])) //if its not a number
        return false;
      i++;
    }

  if (atoi(s) <= 0) //check for 0
    return false;
 
  if (atoi(s) < 8 || atoi(s) > 13) //if wrong size
    return false;

  return true;
}

// check physical size
bool isPhyMemSizeValid(char * s)
{
  int i = 0; //go through char
  while (s[i] != (char)NULL)
    {
      if (!isdigit(s[i])) //not a number check
	return false;
      i++;
    }
  
  if (atoi(s) <= 0) //check for 0
    return false;

  if (atoi(s) != 4 && atoi(s) != 16 && atoi(s) != 32
      && atoi(s) != 64)
    return false;

  return true;
}

//runs all different kinds of page replacement
void Run(int size, int memSize)
{
  int avFrames = memSize/size; //number of frames
  cout << "Page Size: " << size << " bytes\t"
     << "MEM Size: " << memSize << " bytes\t" 
       << "AV Frames: " << avFrames << endl;

  Page * p; //page pointer

  cout << "\nRandom Page SIM\n";
  cout << "############################################\n";
  RandomALG randomPaging(size, memSize, avFrames);
  p = &randomPaging;
  p->startSIM();

  cout << "\nFIFO Page SIM\n";
  cout << "############################################\n";
  Fifo fPage(size, memSize, avFrames);
  p = &fPage;
  p->startSIM();
 
  cout << "\n LRU Page SIM\n";
  cout << "############################################\n";
  LRU lruPaging(size, memSize, avFrames);
  p = &lruPaging;
  p->startSIM();
}

// constructor
ptEntry::ptEntry()
{
  isValid = 0; // valid bit
  isDirty = 0; // write check
  physFrame = -1;// not valid at first
  vMEM_pg = -1; //doesn't have page number
}

// constructor
RandomALG::RandomALG(int pSize, int memSize, int frameNum): 
  Page(pSize, memSize, frameNum){}

// frees a frame
int RandomALG::dealloc_frame()
{
  srand(time(NULL) + memREF);
  int frameNum; // frame number holder
  frameNum = rand() % aval_frames.size();

  
  int page; // holds page
  aval_frames[frameNum].isFree = true;
  page = aval_frames[frameNum].Page;
  aval_frames[frameNum].Page = -1;
  alloc_Frames--;

  // page that will occupy
  int victimIndex = get_pg_byNUM(0, (pT.size() - 1),page);

  if (pT[victimIndex].isDirty)// if dirty
    total_pageFlushes++;


  pT[victimIndex].isDirty = 0;
  pT[victimIndex].isValid = 0;
  pT[victimIndex].physFrame = -1;

  return frameNum;
}

// handles the references from the file
void RandomALG::handel_REF(int new_ref, bool write)
{
  memREF++;
  // if its already there
  if (is_pg_virtual(0, (pT.size() - 1), new_ref))
    {
      int index; //index of page
      index = get_pg_byNUM(0, (pT.size() - 1), new_ref);

      if (write) //if write then set dirty
        pT[index].isDirty = 1;

      // check for page fault
      if (pT[index].isValid)
        return;

      else if (!pT[index].isValid) //if valid then page fault
        {
          total_pageFaults++;
          pT[index].isValid = 1;
          grantFrame(pT[index].physFrame, new_ref);
          handel_REF(new_ref, write);
	  return;
        }
    }

  else
    {
      
      ptEntry newPage; // new page
      newPage.isValid = 1; 
      if (write) // set dirty bit
        newPage.isDirty = 1;
      newPage.vMEM_pg = new_ref;
	  total_pageFaults++;
      
      grantFrame(newPage.physFrame, new_ref);

      
      insertPage(0, (pT.size() - 1), newPage);
      handel_REF(new_ref, write);
    }
}

// constructor for least recently used
LRU::LRU(int pSize, int memSize, int frameNum):
  Page(pSize, memSize, frameNum)
{
  lru_stk.clear();
}

// frees a frame for use
int LRU::dealloc_frame()
{
  int frameNum = lru_stk[0]; // insert into first spot
  lru_stk.erase(lru_stk.begin() + 0);

  int page; // holds page
  aval_frames[frameNum].isFree = true;
  page = aval_frames[frameNum].Page;
  aval_frames[frameNum].Page = -1;
  alloc_Frames--;

  // get page that is to be replaced
  int victimIndex = get_pg_byNUM(0, (pT.size() - 1), page);

  if (pT[victimIndex].isDirty) // if dirty
    total_pageFlushes++;

  pT[victimIndex].isDirty = 0;
  pT[victimIndex].isValid = 0;
  pT[victimIndex].physFrame = -1;

  return frameNum;
}

// handles the reference in least recently used
void LRU::handel_REF(int new_ref, bool write)
{
  memREF++;
  
  // if its in virtual memory already
  if (is_pg_virtual(0, (pT.size() - 1), new_ref))
    {
      int index;
      index = get_pg_byNUM(0, (pT.size() - 1), new_ref);

      // if it writes
      if (write)
        pT[index].isDirty = 1; 

      // check for page fault
      if (pT[index].isValid)
	{
	  int framePosInStack = -1;
	  for (unsigned int i = 0; i < lru_stk.size(); i++)
	    {
	      if (lru_stk[i] == pT[index].physFrame)
		{
		  framePosInStack = i;
		  break;
		}
	    }
	  lru_stk.erase(lru_stk.begin() + framePosInStack); 
	  lru_stk.push_back(pT[index].physFrame);
	  return;
	}

      else if (!pT[index].isValid)
        {
          total_pageFaults++;
          pT[index].isValid = 1;
          grantFrame(pT[index].physFrame, new_ref);
	
	  lru_stk.push_back(pT[index].physFrame);
	  handel_REF(new_ref, write);
          return;
        }
    }

  else
    {
      total_pageFaults++;

      ptEntry newPage;
      newPage.isValid = 1;

      //if write
      if (write)
        newPage.isDirty = 1;
      newPage.vMEM_pg = new_ref;

      grantFrame(newPage.physFrame, new_ref);

      lru_stk.push_back(newPage.physFrame);

      insertPage(0, (pT.size() - 1), newPage);
      handel_REF(new_ref, write);
    }
}

// page constructor
Page::Page(int pSize, int memSize, int frameNum)
{
  size = pSize; 
  phyMEM_sze = memSize;
  memREF = 0; 
  total_pageFaults = 0;
  total_pageFlushes = 0;
  alloc_Frames = 0; 
  pT.clear(); 
  

  Frame newFrame; // makes new frame
  for (int i = 0; i < frameNum; i++)
    aval_frames.push_back(newFrame);
}

// page replacement simulation
void Page::startSIM()
{
  ifstream input; //variable for input
  int reference; //buffer for input
  input.open("references.txt");

  if (input.fail()) //make sure file opens
    {
      cout << "references file could not be opened!!!" << endl;
      return;
    }

  struct timeval timeBS; // time keeping
  struct timeval timeAS; // time keeping
  int i = 0;
  gettimeofday(&timeBS, NULL);
  while (input >> reference)// while another reference
    {      
      if ((reference % 2) == 0) // even ref
	handel_REF(reference/size, false);
     
      else 
	{
	handel_REF(reference/size, true);
	}
      i++;
    }
  input.close();
  gettimeofday(&timeAS, NULL);

  double beg = timeBS.tv_sec + (timeBS.tv_usec/1000000.0);
  double end = timeAS.tv_sec + (timeAS.tv_usec/1000000.0);
  prt_results(beg, end);
}

// assigns free frame
void Page::grantFrame(int & frameNum, int page)
{
  if (!isOpenFrames()) // check if frame available
    {  
      int freeIndex; 
      freeIndex = dealloc_frame(); 
      frameNum = freeIndex;
      aval_frames[freeIndex].isFree = false;
      aval_frames[freeIndex].Page = page; 
      alloc_Frames++;
      return;
    }

  // finds a frame
  for (unsigned int i = 0; i < aval_frames.size(); i++)
    {
      if (aval_frames[i].isFree)
        {
          frameNum = i; 
          aval_frames[i].isFree = false;
          aval_frames[i].Page = page; 
          alloc_Frames++;
          break; 
        }
    }
}

// printing the results
void Page::prt_results(double beg, double end)
{
  cout << "Total Memory Referances: " << memREF << endl
       << "Total Page Faults: " << total_pageFaults << endl
       << "Total Flushes: " << total_pageFlushes << endl
       << "Run Time: " << end-beg << " seconds" << endl;
}

// checing for open frames
bool Page::isOpenFrames()
{ 
  if (alloc_Frames == aval_frames.size()) // check if all frames are full
    return false; 
  else 
    return true; 
}

// inserts a new page.
void Page::insertPage(int first, int last,
					    ptEntry pg)
{
  if (pT.empty()) //check if the table is empty
    {
      pT.push_back(pg);
      return;
    }

  int midIndex = 0;
  while (first <= last)
    {
      midIndex = (first + last) / 2;
      if (pg.vMEM_pg > pT[midIndex].vMEM_pg)
        first = midIndex + 1;
      else if (pg.vMEM_pg < pT[midIndex].vMEM_pg)
        last = midIndex - 1; 
    }
  
  if (last < 0)
    {
      pT.insert(pT.begin() + 0, pg);
      return;
    }

  if (first > (int)(pT.size() - 1))
    {
      pT.push_back(pg);
      return;
    }

  pT.insert(pT.begin() + (last + 1), pg);
}

// check if page is in memory
bool Page::is_pg_virtual(int first, int last ,int pg) 
{
  int midIndex = 0; //holds the index for the middle
  while (first <= last)
    {
      midIndex = (first + last) / 2;
      if (pg > pT[midIndex].vMEM_pg)
        first = midIndex + 1;
      else if (pg < pT[midIndex].vMEM_pg)
        last = midIndex - 1;
      else
        return true;
    }
  return false;
}

// gets the index of a page and returns it
int Page::get_pg_byNUM(int first, int last, int pg)
{
  int midIndex = 0; //hold mid index
  while (first <= last)
    {
      midIndex = (first + last) / 2;
      // check where key is
      if (pg > pT[midIndex].vMEM_pg)
	first = midIndex + 1;
      else if (pg < pT[midIndex].vMEM_pg)
	last = midIndex - 1;
      else
	return midIndex;
    }
  return -1;
}

// constructor for first in first out
Fifo::Fifo(int pSize, int memSize, int frameNum):
  Page(pSize, memSize, frameNum)
{
  fifo_que.clear();
}

// frees up a frame
int Fifo::dealloc_frame()
{
  int frameNum = fifo_que[0]; // get first element in que
  fifo_que.erase(fifo_que.begin() + 0);

  int page; // holds the page
  aval_frames[frameNum].isFree = true;
  page = aval_frames[frameNum].Page;
  aval_frames[frameNum].Page = -1;
  alloc_Frames--;

  // get the page
  int victimIndex = get_pg_byNUM(0, (pT.size() - 1), page);

  if (pT[victimIndex].isDirty) // if its dirty then flush
    total_pageFlushes++;

  pT[victimIndex].isDirty = 0;
  pT[victimIndex].isValid = 0;
  pT[victimIndex].physFrame = -1;

  return frameNum;
}

// handles fifo references from the files
void Fifo::handel_REF(int new_ref, bool write)
{
  memREF++;
  
  //check if page is already in memory
  if (is_pg_virtual(0, (pT.size() - 1), new_ref))
    {
      int index;
      index = get_pg_byNUM(0, (pT.size() - 1), new_ref);

      if (write)// check if its a write
        pT[index].isDirty = 1;

      if (pT[index].isValid)// check if its in memory
        return;

      else if (!pT[index].isValid)// its invalid so fault
        {
          total_pageFaults++;
          pT[index].isValid = 1;
          grantFrame(pT[index].physFrame, new_ref);
	  fifo_que.push_back(pT[index].physFrame);
	  handel_REF(new_ref, write);
          return;
        }
    }

  else 
    {
      total_pageFaults++; 

      ptEntry newPage; // new page
      newPage.isValid = 1;
      if (write) 
        newPage.isDirty = 1;
      newPage.vMEM_pg = new_ref;

      grantFrame(newPage.physFrame, new_ref);

      insertPage(0, (pT.size() - 1), newPage);
      fifo_que.push_back(newPage.physFrame);
      handel_REF(new_ref, write);
    }
}
