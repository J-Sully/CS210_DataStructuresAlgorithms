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
//#define RUN_INPUT_TEST1
//#define RUN_INPUT_TEST2

#include "Graph.h"
#include "DynamicArray.h"


#ifdef RUN_INPUT_TEST1
static const string TEST_INPUT = "MinPath1.txt";

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif
#endif /* RUN_INPUT_TEST1 */

#ifdef RUN_INPUT_TEST2
static const string TEST_INPUT = "MinPath2.txt";

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif
#endif /* RUN_INPUT_TEST2 */


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
  
#ifdef RUN_INPUT_TEST1
  // Override cin with a test input file.
  string testInputFile(__FILE__);
  size_t filePos = testInputFile.rfind(PATH_SEPARATOR);
  testInputFile = testInputFile.erase(filePos + 1, string::npos);
  testInputFile += TEST_INPUT;
  
  ifstream in(testInputFile.c_str());
  cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
#endif /* RUN_INPUT_TEST1 */
  
#ifdef RUN_INPUT_TEST2
  // Override cin with a test input file.
  string testInputFile(__FILE__);
  size_t filePos = testInputFile.rfind(PATH_SEPARATOR);
  testInputFile = testInputFile.erase(filePos + 1, string::npos);
  testInputFile += TEST_INPUT;
  
  ifstream in(testInputFile.c_str());
  cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
#endif /* RUN_INPUT_TEST2 */
  
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
  DynamicArray<int> array1;
  assert(!array1.validateIndex(0));
  array1.addObject(10);
  array1.addObject(5);
  array1.addObject(7);
  assert(array1.getSize() == 3);
  assert(array1.validateIndex(0));
  assert(array1.validateIndex(1));
  assert(array1.validateIndex(2));
  assert(!array1.validateIndex(3));
  assert(!array1.validateIndex(-1));
  assert(array1[0] == 10);
  assert(array1[1] == 5);
  assert(array1[2] == 7);
  assert(array1.getCapacity() == 4);
  cout << array1 << endl << endl;
  array1.clear();
  assert(array1.getSize() == 0);
  assert(!array1.validateIndex(1));
  
  Graph graph;
  graph.addVertex("SF");
  graph.addVertex("LA");
  assert(graph.getNumVertices() == 2);
  graph.addEdge(0, 1, 10);
  assert((*graph.getVertex(0).mEdges[0]).mWeight == 10);
  assert((*graph.getVertex(1).mEdges[0]).mWeight == 10);
  
  
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumVertexObjects != 0 || sNumEdgeObjects != 0) {
    cerr << "Num leaked vertices: " << sNumVertexObjects << endl;
    cerr << "Num leaked edges: " << sNumEdgeObjects << endl;
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

static const string TEST_INPUT = "MinPath1.txt";
#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

// runs the UI for the project.
void runProgram() {
  Graph graph("MinPath1.txt");
  cout << graph << endl;
  

}
