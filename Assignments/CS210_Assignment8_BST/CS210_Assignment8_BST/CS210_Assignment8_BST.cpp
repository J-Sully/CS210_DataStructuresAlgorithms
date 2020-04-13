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
using namespace std;

//#define RUN_TESTS

#include "BST.h"

const int SIZE =15;

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
  tree.clearTree();
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
  tree.clearTree();
  
  tree.insert(5);
  tree.insert(12);
  tree.insert(2);
  tree.remove(5);
  assert(tree.getRoot()->mValue == 12);
  assert(tree.getRoot()->mRight == nullptr);
  assert(tree.getRoot()->mLeft != nullptr);
  
  tree.clearTree();
  tree.insert(5);
  tree.insert(12);
  tree.insert(2);
  tree.insert(9);
  tree.insert(21);
  tree.insert(19);
  tree.insert(25);
  tree.remove(12);
  assert(tree.getRoot()->mRight->mValue == 19);
  
  tree.clearTree();
  tree.insert(5);
  tree.insert(2);
  tree.insert(-4);
  tree.remove(2);
  assert(tree.getRoot()->mLeft->mValue == -4);
  
  tree.clearTree();
  tree.insert(5);
  tree.insert(12);
  tree.insert(21);
  tree.remove(12);
  assert(tree.getRoot()->mRight->mValue == 21);
  
  tree.clearTree();
  tree.insert(5);
  tree.insert(12);
  tree.insert(2);
  tree.insert(9);
  tree.insert(21);
  tree.remove(12);
  assert(tree.getRoot()->mRight->mValue == 21);
  
  tree.clearTree();
  tree.insert(5);
  tree.insert(2);
  tree.insert(12);
  tree.insert(-4);
  tree.insert(9);
  tree.insert(21);
  tree.remove(5);
  assert(tree.getRoot()->mValue == 9);
  
  tree.clearTree();
  tree.insert(5);
  tree.insert(2);
  tree.insert(3);
  tree.remove(2);
  assert(tree.getRoot()->mLeft->mValue == 3);
  
  tree.clearTree();
  tree.insert(5);
  tree.remove(4);
  assert(tree.getRoot() != nullptr);
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
  bst.inOrderTraversal(); /// should be -8 -7 -6 -4 2 3 5 9 12 19 21 25
  bst.postOrderTraversal(); /// should be -8 -6 -7 -4 3 2 9 19 25 21 12 5
  
  bst.remove(3); /// Node 3 has 0 children --> delete the node and make it NULL;
  bst.remove(-4); /// Node -4 has 1 children --> Link parent to child --> delete the node and make it NULL;
  bst.remove(12); /// Node 12 has 2 children --> findMin for the right subtree --> swap value -> delete

  bst.preOrderTraversal(); /// should be 5 2 -7 -8 -6 19 9 21 25
  bst.inOrderTraversal(); /// should be -8 -7 -6 2 5 9 19 21 25
  bst.postOrderTraversal(); /// should be -8 -6 7 2 9 25 21 19 5
  
  return;
}
