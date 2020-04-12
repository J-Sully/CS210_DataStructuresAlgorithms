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
  
  

  
  
  /*
   
  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.display(cout);
    assert(array.getSize() == 1);// sometimes fails
    assert(array.getEntry(1) == 2);
    array.addEntry(1, 5);
    assert(array.getSize() == 1);
    assert(array.getEntry(1) == 5);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.deleteIndex(1);
    array.addEntry(2, 3);
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.deleteIndex(5);
    array.addEntry(2, 3);
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.addEntry(2, 3);
    array.deleteIndex(5);
    array.addEntry(3, 4);
    array.display(cout);
  } // FIXME: This sometimes crashes on destructor.
  
  {
    MySortableArray<int> array;
    assert(array.getLoc(0) == 0);
    array.addEntry(0, 5);
    assert(array.getLoc(0) == 0);
    array.addEntry(1, 5);
    array.addEntry(2, 4);
    array.addEntry(4, 6);
    array.display(cout);
    assert(array.getLoc(0) == 0);
    assert(array.getLoc(4) == 3); //sometimes crashes
    assert(array.getLoc(100) == 4);
    assert(array.getEntry(2) == 4);
    assert(array.getEntry(0) == 5);
    bool caught = false;
    try {
      array.getEntry(100);
    } catch (out_of_range) {  // FIXME: getEntry should raise an out_of_range exception
      caught = true;
    }
    assert(caught == true);
  }
  
  {
    MySortableArray<int> source;
    
    MySortableArray<int> dest1(source);
    assert(dest1.isEmpty());
    dest1.addEntry(1, 2);     // FIXME: This crashes.
    assert(dest1.getEntry(1) == 2);
    
    MySortableArray<int> dest2;
    dest2.copyData(source);
    assert(dest2.isEmpty());
    
    source.addEntry(1, 2);
    source.addEntry(2, 3);
    
    MySortableArray<int> dest3(source);
    assert(dest3.getSize() == 2); // FIXME: This sometimes fails
    assert(dest3.getEntry(1) == 2);
    assert(dest3.getEntry(2) == 3); // FIXME: This somtimes fails
    
    MySortableArray<int> dest4;
    dest4.copyData(source);
    assert(dest4.getSize() == 2);  // FIXME: This sometimes fails
    assert(dest4.getEntry(1) == 2);
    assert(dest4.getEntry(2) == 3);  // FIXME: This sometimes fails
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(0, 2);
    array.addEntry(1, 2);
    array.sort(2);
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(0, 2);
    array.sort(1);
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(4, 0);
    array.addEntry(2, 1);
    array.addEntry(0, 4);
    array.addEntry(1, 2);
    array.display(cout);
    array.sort(0);
    array.display(cout);
    array.sort(1);
    array.display(cout);
    array.sort(2);
    assert(array.getEntry(0) == 2); //sometimes crashes
    assert(array.getEntry(1) == 4);
    assert(array.getEntry(2) == 1);
    assert(array.getEntry(4) == 0);
    array.display(cout);
    array.sort(3);
    assert(array.getEntry(0) == 1);
    assert(array.getEntry(1) == 2);// crash
    assert(array.getEntry(2) == 4);
    assert(array.getEntry(4) == 0);
    array.display(cout);
    array.sort(4);
    assert(array.getEntry(0) == 0);
    assert(array.getEntry(1) == 1);
    assert(array.getEntry(2) == 2);
    assert(array.getEntry(4) == 4);
    array.display(cout);
    array.sort(5);
    array.display(cout);
  }
   */
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
  bst.remove(-4); /// Node -4 has 1 children --> Link parent to child --> delete the node and make it NULL;
  bst.remove(12); /// Node 12 has 2 children --> findMin for the right subtree --> swap value -> delete

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
