/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  main.cpp
// CS210_Assignment11_Hashing
//
//  Created by Jessie Sully on 4/17/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

//#define RUN_TESTS
//#define RUN_INPUT_TEST

#include "StudentHT.h"

static const string TEST_INPUT = "Add-1.txt";
static const string SEARCH_INPUT = "Search-1.txt";

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

// runs searches from file
template <typename T>
void runSearches(const StudentHT<T> &hashTable, const string &codePath, double &numSearches);

struct RecType {
  RecType() {}
  RecType(long studentID, const string &fName = "", const string &lName = "") : mStudentID(studentID), mFname(fName), mLname(lName) {}
  RecType(const RecType &other) : mStudentID(other.mStudentID), mFname(other.mFname), mLname(other.mLname) {}
  RecType(const string &input);
  long mStudentID = -1;
  string mFname;
  string mLname;
};

RecType::RecType(const string &input) {
  stringstream ss;
  ss.str(input);
  ss >> mStudentID;
  mFname = "Student ID as First Name: ";
  mFname += mStudentID;
  mLname = "Student ID as Last Name: ";
  mLname += mStudentID;
}

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
  StudentHT<int> hashTable4(10);
  hashTable4.insert(1, 10);
  hashTable4.insert(101, 10);
  hashTable4.insert(1001, 10);
  hashTable4.insert(10001, 10);
  hashTable4.insert(100001, 10);
  hashTable4.search(100001);
  assert(sNumNodesSearched == 5);
  hashTable4.search(10001);
  assert(sNumNodesSearched == 9);
  hashTable4.search(1251);
  assert(sNumNodesSearched == 14);
  
  StudentHT<int> hashTable1;
  StudentHT<int> hashTable2(10);
  hashTable2.insert(1001, 10);
  assert(hashTable2.search(1) == nullptr);
  assert(*hashTable2.search(1001) == 10);
  hashTable2.insert(101, 5);
  assert(hashTable2.search(1) == nullptr);
  assert(*hashTable2.search(1001) == 10);
  assert(*hashTable2.search(101) == 5);
  
  StudentHT<RecType> hashTable3(codePath + TEST_INPUT);
  assert(hashTable3.search(7995)->mStudentID == 7995);
  double numSearches = 0;
  runSearches(hashTable3, codePath, numSearches);
  assert(numSearches = 50);
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects!= 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

// runs searches from file
template <typename T>
void runSearches(const StudentHT<T> &hashTable, const string &codePath, double &numSearches) {
  ifstream finputFile(codePath + SEARCH_INPUT);
  stringstream ss;
  string input;
  unsigned int key, num;
  numSearches = 0;
  if (finputFile) {
    finputFile >> num;
    getline(finputFile,input);
    getline(finputFile,input);
    while (getline(finputFile, input)) {
      ss.str(input);
      ss >> key;
      numSearches++;
      hashTable.search(key);
    }
    finputFile.close();
  }
}

// runs the UI for the project.
void runProgram(const string &codePath) {
  StudentHT<RecType> hashTable(codePath + TEST_INPUT);
  double numSearches = 0;
  double nodesToSearchRatio = 0;
  runSearches(hashTable, codePath, numSearches);
  cout << "Total Number of ID's searched: " << numSearches << endl;
  cout << "Total Number of Nodes searched: " << sNumNodesSearched << endl;
  nodesToSearchRatio = sNumNodesSearched / numSearches;
  cout << "Average Number of Nodes per ID searched: " << fixed << setprecision(2) << nodesToSearchRatio << endl;
}

