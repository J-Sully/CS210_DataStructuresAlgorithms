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

#include "MySortableArray.h"

#include <iostream>
#include <sstream>
using namespace std;

// returns true if memory leak
bool testMemoryLeak();

// prints array in "<index>=><value>" format separated by spaces.
template <typename T>
void printArray(ostream &ostr, const MySortableArray<T> array);

// helper function to parse index and value from input - with index validation. Returns parse fails or if index < 0.
template <typename T>
bool parseIndexValue(const string &input, int &index, T &value);

// helper function to parse an int from input
bool parseIndex(const string &input, int &num);

// runs the UI for the project.
void runProgram();

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  runProgram();
  testMemoryLeak();
  
  return 0;
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

// prints array in "<index>=><value>" format separated by spaces.
template <typename T>
void printArray(ostream &ostr, const MySortableArray<T> array) {
  if (!array.isEmpty()) {
    array.display(cout);
  }
  else {
    ostr << "Array is empty" << endl;
  }
  ostr << endl;
}

// helper function to parse index and value from input - with index validation. Returns parse fails or if index < 0.
template <typename T>
bool parseIndexValue(const string &input, int &index, T &value) {
  stringstream ss;
  ss.str(input);
  ss >> index >> value;
  return !ss.fail() && index >= 0;
}

// helper function to parse an int from input
bool parseIndex(const string &input, int &num) {
  stringstream ss;
  ss.str(input);
  ss >> num;
  return !ss.fail() && num >= 0;
}

// runs the UI for the project.
void runProgram() {
  string input = "";
  int index = 0, value = 0, numEntries = 0;
  MySortableArray<int> dataToSort;
  
  cout << "Please enter data as '<index> <value>' enter -1 to end: " << endl;
  getline(cin, input);
  while (input != "-1") {
    if (parseIndexValue(input, index, value)) {
      dataToSort.addEntry(index, value);
    }
    else {
      cerr << "Error with entry, please try again: " << endl;
    }
    getline(cin, input);
  }
  cout << endl << "Data entered: " << endl;
  printArray(cout, dataToSort);
  
  do {
    cout << "Number of entries to sort: ";
    getline(cin, input);
    if (!parseIndex(input, numEntries)) {
      cerr << "Error, please try again." << endl << endl;
    }
  } while (numEntries < 0);
  
  dataToSort.sort(numEntries);
  printArray(cout, dataToSort);
  
  do {
    cout << endl << "Enter an index to view, enter -1 to exit: ";
    getline(cin, input);
    if (parseIndex(input, index) && dataToSort.validateIndex(index)) {
      cout << endl << dataToSort.getEntry(index) << endl;
    }
    else {
      if (index != -1) {
        cerr << "Invalid index, please try again." << endl;
      }
    }
  } while (index != -1);
}
