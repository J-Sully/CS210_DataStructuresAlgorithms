//
//  main.cpp
//  CS210_Assignment5_StackQueue
//
//  Created by Donald Kjer on 3/8/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//#define RUN_INPUT_TEST 1

enum StatusCode {
  STATUS_OK = 0,
  ERR_MEMORY_LEAK
};

//#include "Assignment5A.h"
#include "Assignment5B.h"

#ifdef RUN_INPUT_TEST
  static const string TEST_INPUT = "test_input_5b.txt";

  #if defined(WIN32) || defined(_WIN32)
    #define PATH_SEPARATOR "\\"
  #else
    #define PATH_SEPARATOR "/"
  #endif
#endif /* RUN_INPUT_TEST */


bool testMemoryLeak();

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
  
  int status = runAssignment5B();
  
  if (testMemoryLeak()) {
    return ERR_MEMORY_LEAK;
  }
  
  return status;
}


// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

