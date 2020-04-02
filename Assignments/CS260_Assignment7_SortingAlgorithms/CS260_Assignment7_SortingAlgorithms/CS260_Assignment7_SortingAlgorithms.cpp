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
    for (int i = 0; i < array.getSize(); i++) {
      ostr << i << "=>" << array.getEntry(i) << endl;;
    }
  }
  else {
    ostr << "Array is empty" << endl;
  }
  ostr << endl;
}

void runProgram() {
  MySortableArray<int> array;
  cout << array.getSize() << endl;
  cout << array.addEntry(7, 10) << endl;
  
  
  
  
}

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  runProgram();
  testMemoryLeak();
  
  
  /*
  stringstream ss;
  string input = "";
  int index = 0, value = 0;
  MySortableArray<int> dataToSort;
  MySortableArray<string> stringInputs;
  cout << "Please enter data as '<index> <value>' enter -1 to end: " << endl;
  getline(cin, input);
  while (input != "-1") {
    stringInputs.addEntry(input);
    ss.str(input);
    ss >> index >> value;
    ss.clear();
    dataToSort.setEntry(index, value);
    getline(cin, input);
  }
  dataToSort.sort(dataToSort.getSize());
  cout << "Data Entered: " << endl;
  printArray(cout, dataToSort);
  */
  
  
  return 0;
}


