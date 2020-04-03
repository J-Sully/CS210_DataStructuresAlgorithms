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
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

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

bool parseIndexValue(const string &input, int &index, int &value) {
  stringstream ss;
  ss.str(input);
  ss >> index >> value;
  return !ss.fail() && index >= 0;
}

bool parseIndex(const string &input, int &num) {
  stringstream ss;
  ss.str(input);
  ss >> num;
  return !ss.fail();
}

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
  cout << "Data entered: " << endl;
  printArray(cout, dataToSort);
  
  do {
    cout << "Number of entries to sort: ";
    getline(cin, input);
    parseIndex(input, numEntries);
    if (numEntries < 0 || cin.fail()) {
      cerr << "Error, please try again." << endl << endl;
    }
  } while (numEntries < 0);
  
  dataToSort.sort(numEntries);
  printArray(cout, dataToSort);
  
  do {
    cout << endl << "Enter an index to view, enter -1 to exit: ";
    getline(cin, input);
    if (parseIndex(input, index)) {
      if (dataToSort.validateIndex(index)) {
        cout << endl << dataToSort.getEntry(index) << endl;
      }
    }
    else {
      if (index != -1) {
        cerr << "Invalid index, please try again." << endl << endl;
      }
    }
  } while (index != -1);
}

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  runProgram();
  testMemoryLeak();
  
  

  

  
  
  return 0;
}


