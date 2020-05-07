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

// runs tests for the project.
void runTests(const string &codePath);

// runs the UI for the project.
void runProgram(const string &codePath);

void printMenu(Graph &graph);
void manageMenu(Graph &graph);

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
  
  // testing DynamicArray
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
  
  // small tests for Graph
  Graph graph1;
  graph1.addVertex("SF");
  graph1.addVertex("LA");
  graph1.addEdge(0, 1, 80);
  assert(graph1.getEdge(0)->mWeight == 80);
  assert(graph1.getEdge(0)->mVertexIdx1 == 0);
  assert(graph1.getEdge(0)->mVertexIdx1 == 0);
  assert(graph1.getVertex(0)->mEdgeIdxs[0] == 0);
  assert(graph1.getVertex(1)->mEdgeIdxs[0] == 0);
  cout << graph1 << endl;
  graph1.addVertex("Chicago");
  cout << graph1 << endl;
  graph1.addEdge(0, 2, 200);
  cout << graph1 << endl;
  graph1.addEdge(1, 2, 230);
  cout << graph1 << endl;
  graph1.addVertex("NY");
  
  // file 1 tests for Graph
  Graph graph2(codePath + GRAPH_INPUT1);
  cout << graph2;
  for(int i = 0; i < graph2.getNumVertices(); i++) {
    for (int j = 0; j < graph2.getNumVertices(); j++) {
      assert(graph2.getMinPath(i, j, cout) == graph2.getMinPath(j, i, cout));
    }
  }
  
  // file 2 tests for Graph
  Graph graph3(codePath + GRAPH_INPUT2);
  assert(graph3.getVertex(6)->mName == "ST LOUIS");
  cout << graph3;
  for(int i = 0; i < graph3.getNumVertices(); i++) {
    for (int j = 0; j < graph3.getNumVertices(); j++) {
      assert(graph3.getMinPath(i, j, cout) == graph3.getMinPath(j, i, cout));
    }
  }
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

void printMenu(Graph &graph) {
  for (int i = 0; i < graph.getNumVertices(); i++) {
    cout << i << ": " << graph.getVertex(i)->mName << endl;
  }
  cout << "Please select two vertices separated by a space to find the minimum distance between two points (enter -1 to exit): ";
}

void manageMenu(Graph &graph) {
  string input;
  stringstream ss;
  int index1 = -1, index2 = -1;
  printMenu(graph);
  getline(cin, input);
  while (input != "-1") { 
    ss.str(input);
    ss >> index1 >> index2;
    if (graph.validateVertexIdx(index1) && graph.validateVertexIdx(index2)
        && !ss.fail()) {
      cout << endl;
      graph.getMinPath(index1, index2, cout);
    }
    else {
      cerr << "Error with entry: '" << input << "'" << endl << endl;
    }
    ss.clear();
    index1 = -1;
    index2 = -1;
    printMenu(graph);
    getline(cin, input);
  }
}

// runs the UI for the project.
void runProgram(const string &codePath) {
  Graph graph1(codePath + GRAPH_INPUT1);
  Graph graph2(codePath + GRAPH_INPUT2);
  manageMenu(graph1);
  manageMenu(graph2);
}
