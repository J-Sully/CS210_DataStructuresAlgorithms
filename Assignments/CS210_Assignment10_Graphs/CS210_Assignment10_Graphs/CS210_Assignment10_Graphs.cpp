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

#define RUN_TESTS
//#define RUN_INPUT_TEST

#include "Graph.h"
#include "DynamicArray.h"

static const string TEST_INPUT = "input.txt";
static const string GRAPH_INPUT1 = "MinPath1.txt";
static const string GRAPH_INPUT2 = "MinPath2.txt";

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif /* RUN_INPUT_TEST1 */

// returns true if memory leak
bool testMemoryLeak();

// helper function to parse index and value from input - with index validation. Returns parse fails or if index < 0.
bool parsePriorityName(const string &input, int &priority, string &name);

// runs tests for the project.
void runTests(const string &codePath);

// runs the UI for the project.
void runProgram(const string &codePath);

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  string codePath(__FILE__);
  size_t filePos1 = codePath.rfind(PATH_SEPARATOR);
  codePath = codePath.erase(filePos1 + 1, string::npos);
  
#ifdef RUN_INPUT_TEST
  // Override cin with a test input file.
  string testInputFile = codePath + TEST_INPUT;
  ifstream in(testInputFile.c_str());
  cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
#endif /* RUN_INPUT_TEST */
  
#ifdef RUN_TESTS
  runTests(codePath);
#else
  runProgram(codePath);
#endif /* RUN_TESTS */
  testMemoryLeak();
  
  return 0;
}


// run tests for the project
void runTests(const string &codePath) {
  

  
  
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
  //assert(array1.getCapacity() == 4);
  cout << array1 << endl << endl;
  array1.clear();
  assert(array1.getSize() == 0);
  assert(!array1.validateIndex(1));
  
  Graph graph1;
  graph1.addVertex("SF");
  graph1.addVertex("LA");
  graph1.addEdge(0, 1, 80);
  assert(graph1.getEdge(0).mWeight == 80);
  assert(graph1.getEdge(0).mVertexIdx1 == 0);
  assert(graph1.getEdge(0).mVertexIdx1 == 0);
  assert(graph1.getVertex(0).mEdgeIdxs[0] == 0);
  assert(graph1.getVertex(1).mEdgeIdxs[0] == 0);
  cout << graph1 << endl;
  graph1.addVertex("Chicago");
  cout << graph1 << endl;
  graph1.addEdge(0, 2, 200);
  cout << graph1 << endl;
  graph1.addEdge(1, 2, 230);
  cout << graph1 << endl;
  graph1.addVertex("NY");
  
  Graph graph2(codePath + GRAPH_INPUT1);
  cout << graph2;
  assert(graph2.getMinPath(0, 0, cout) == 0);
  assert(graph2.getMinPath(0, 1, cout) == 80);
  assert(graph2.getMinPath(0, 2, cout) == 200);
  assert(graph2.getMinPath(0, 3, cout) == 300);
  assert(graph2.getMinPath(0, 0, cout) == 630);
  assert(graph2.getMinPath(0, 0, cout) == 770);
  
  
 
  Graph graph3(codePath + GRAPH_INPUT2);
  assert(graph3.getVertex(6).mName == "ST LOUIS");
  cout << graph3;
  
  

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

// runs the UI for the project.
void runProgram(const string &codePath) {
  Graph graph(codePath + GRAPH_INPUT1);
  cout << graph << endl;
  
  
  

}
