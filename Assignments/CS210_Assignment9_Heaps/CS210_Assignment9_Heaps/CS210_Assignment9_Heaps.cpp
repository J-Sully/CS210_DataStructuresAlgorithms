/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  main.cpp
// CS210_Assignment9_Heaps
//
//  Created by Jessie Sully on 4/17/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//#define RUN_TESTS
//#define RUN_INPUT_TEST

#include "PriorityQueue.h"


#ifdef RUN_INPUT_TEST
static const string TEST_INPUT = "input.txt";

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif
#endif /* RUN_INPUT_TEST */


// returns true if memory leak
bool testMemoryLeak();

// helper function to parse index and value from input - with index validation. Returns parse fails or if index < 0.
bool parsePriorityName(const string &input, int &priority, string &name);

// runs tests for the project.
void runTests();

// runs the UI for the project.
void runProgram();

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
#ifdef RUN_INPUT_TEST
  // Override cin with a test input file.
  string testInputFile(__FILE__);
  size_t filePos = testInputFile.rfind(PATH_SEPARATOR);
  testInputFile = testInputFile.erase(filePos + 1, string::npos);
  testInputFile += TEST_INPUT;
  
  ifstream in(testInputFile.c_str());
  cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
#endif /* RUN_INPUT_TEST */
  
#ifdef RUN_TESTS
  runTests();
#else
  runProgram();
#endif /* RUN_TESTS */
  testMemoryLeak();
  
  return 0;
}


// run tests for the project
void runTests() {
  PriorityQueue queue;
  Node node;
  string name = "George";
  queue.penqueue(1, name);
  queue.penqueue(1, name);
  cout << queue << endl;
  
  queue.clearMaxHeap();
  queue.penqueue(1, name);
  queue.penqueue(2, name);
  cout << queue << endl;
  node = queue.pdequeue();
  assert(node.mPriority == 2);
  node = queue.pdequeue();
  assert(node.mPriority == 1);
  assert(queue.isEmpty());
  
  queue.clearMaxHeap();
  queue.penqueue(1, name);
  queue.penqueue(2, name);
  queue.penqueue(3, name);
  cout << queue << endl;
  node = queue.pdequeue();
  assert(node.mPriority == 3);
  node = queue.pdequeue();
  assert(node.mPriority == 2);
  node = queue.pdequeue();
  assert(node.mPriority == 1);
  assert(queue.isEmpty());
  
  queue.clearMaxHeap();
  queue.penqueue(1, name);
  queue.penqueue(2, name);
  queue.penqueue(3, name);
  queue.penqueue(4, name);
  cout << queue << endl;
  node = queue.pdequeue();
  assert(node.mPriority == 4);
  node = queue.pdequeue();
  assert(node.mPriority == 3);
  node = queue.pdequeue();
  assert(node.mPriority == 2);
  node = queue.pdequeue();
  assert(node.mPriority == 1);
  assert(queue.isEmpty());
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

// helper function to parse index and value from input - with index validation. Returns parse fails or if index < 0.
bool parsePriorityName(const string &input, int &priority, string &name) {
  stringstream ss;
  ss.str(input);
  ss >> priority >> name;
  return !ss.fail() && priority >= 1 && priority <= 10;
}

// runs the UI for the project.
void runProgram() {
  PriorityQueue queue;
  string input, name;
  int priority = 0;
  cout << "Please enter data as <priority> <name>, enter '-1' to exit: " << endl;
  getline(cin, input);
  while (input != "-1") {
    if (parsePriorityName(input, priority, name)) {
      queue.penqueue(priority, name);
    }
    getline(cin, input);
  }
  while (!queue.isEmpty()) {
    cout << queue.pdequeue() << endl;
  }
}
