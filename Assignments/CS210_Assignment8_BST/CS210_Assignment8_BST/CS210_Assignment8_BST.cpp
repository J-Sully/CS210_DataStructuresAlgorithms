/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  main.cpp
//  CS260_Assignment7_SortingAlgorithms
//
//  Created by Jessie Sully on 3/31/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#define RUN_TESTS
//#define RUN_INPUT_TEST

#include "BST.h"

const int SIZE =15;

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
  BST tree;
  assert(tree.getRoot() == nullptr);
  tree.insert(5);
  assert(tree.getRoot() != nullptr);
  assert(tree.getRoot()->mValue == 5);
  assert(tree.getRoot()->mLeft == nullptr);
  assert(tree.getRoot()->mRight == nullptr);
  tree.remove(5);
  assert(tree.getRoot() == nullptr);
  
  tree.insert(5);
  tree.insert(5);
  assert(tree.getRoot() != nullptr);
  assert(tree.getRoot()->mValue == 5);
  assert(tree.getRoot()->mLeft == nullptr);
  assert(tree.getRoot()->mRight == nullptr);
  
  tree.insert(2);
  assert(tree.getRoot()->mLeft != nullptr);
  assert(tree.getRoot()->mRight == nullptr);
  assert(tree.getRoot()->mLeft->mValue == 2);
  assert(tree.getRoot()->mLeft->mLeft == nullptr);
  assert(tree.getRoot()->mLeft->mRight == nullptr);
  tree.remove(5);
  assert(tree.getRoot() != nullptr);
  assert(tree.getRoot()->mValue == 2);
  assert(tree.getRoot()->mLeft == nullptr);
  assert(tree.getRoot()->mRight == nullptr);
  tree.clearTree(tree.getRoot());
  assert(tree.getRoot() == nullptr);
  
  tree.insert(5);
  tree.insert(12);
  assert(tree.getRoot()->mRight != nullptr);
  assert(tree.getRoot()->mLeft == nullptr);
  assert(tree.getRoot()->mRight->mValue == 12);
  assert(tree.getRoot()->mRight->mLeft == nullptr);
  assert(tree.getRoot()->mRight->mRight == nullptr);
  tree.remove(5);
  assert(tree.getRoot() != nullptr);
  assert(tree.getRoot()->mValue == 12);
  assert(tree.getRoot()->mLeft == nullptr);
  assert(tree.getRoot()->mRight == nullptr);
  tree.clearTree(tree.getRoot());
  
  tree.insert(5);
  tree.insert(12);
  tree.insert(2);
  tree.remove(5);
  assert(tree.getRoot()->mValue == 12);
  assert(tree.getRoot()->mRight == nullptr);
  assert(tree.getRoot()->mLeft != nullptr);
  
  tree.clearTree(tree.getRoot());
  tree.insert(5);
  tree.insert(12);
  tree.insert(2);
  tree.insert(9);
  tree.insert(21);
  tree.insert(19);
  tree.insert(25);
  tree.remove(12);
  assert(tree.getRoot()->mRight->mValue == 19);
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

// runs the UI for the project.
void runProgram() {
  BST bst;
  int values[SIZE] = {5, 2, 12, -4, 3, 9, 21, -7, 19, 25, -8, -6, -4, 3, 12};
  for (int i = 0; i < SIZE; i++)
    bst.insert(values[i]);
  
  bst.preOrderTraversal(); /// should be 5 2 -4 -7 -8 -6 3 12 9 21 19 25
                                      // 5 2 -4 -7 -8 -6 3 12 9 21 19 25
  bst.inOrderTraversal(); /// should be -8 -7 -6 -4 2 3 5 9 12 19 21 25
                                      //-8 -7 -6 -4 2 3 5 9 12 19 21 25
  bst.postOrderTraversal(); /// should be -8 -6 -7 -4 3 2 9 19 25 21 12 5
  //                                    -8 -6 -7 -4 3 2 9 19 25 21 12 5
  bst.remove(3); /// Node 3 has 0 children --> delete the node and make it NULL;
  bst.inOrderTraversal();
  bst.remove(-4); /// Node -4 has 1 children --> Link parent to child --> delete the node and make it NULL;
  bst.inOrderTraversal();
  bst.remove(12); /// Node 12 has 2 children --> findMin for the right subtree --> swap value -> delete
  bst.inOrderTraversal();

  bst.preOrderTraversal(); /// should be 5 2 -7 -8 -6 19 9 21 25
                                       //5 2 -7 -8 -6 19 9 21 25
  bst.inOrderTraversal(); /// should be -8 -7 -6 2 5 9 19 21 25
                                      //-8 -7 -6 2 5 9 19 21 25
  bst.postOrderTraversal(); /// should be -8 -6 7 2 9 25 21 19 5
                                        //-8 -6 -7 2 9 25 21 19 5
  bst.remove(bst.getRoot()->mValue);
  bst.preOrderTraversal(); /// should be 5 2 -7 -8 -6 19 9 21 25
  //5 2 -7 -8 -6 19 9 21 25
  bst.inOrderTraversal(); /// should be -8 -7 -6 2 5 9 19 21 25
  //-8 -7 -6 2 5 9 19 21 25
  bst.postOrderTraversal(); /// should be -8 -6 7 2 9 25 21 19 5
  //-8 -6 -7 2 9 25 21 19 5
  
  return;
}
