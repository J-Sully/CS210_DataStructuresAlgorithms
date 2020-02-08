//  DYNAMICSTRINGARRAYH
//  CS210_Assignment2_ClassesPointers
//
/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  Created by Jessie Sully on 2/5/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef DYNAMICSTRINGARRAY_H
#define DYNAMICSTRINGARRAY_H

#include <string>
using namespace std;


class DynamicStringArray {
  //This is used in getEntry to allow personalized error strings
  static const string BAD_INPUT;
public:
  //default constructor initializes size to zero and dynamicArray to nullptr
  DynamicStringArray();
  DynamicStringArray(const DynamicStringArray& srcArray);
  ~DynamicStringArray() {delete [] mDynamicArray;}
  
  DynamicStringArray& operator=(const DynamicStringArray& srcArray);
  
  int getSize() const { return mSize; }
  //returns a desired BAD_INPUT string in cases of error - array doesn't exist (null) or is empty or index is out of range
  const string& getEntry(int index) const { return index >= 0 && index < mSize
                                          ? mDynamicArray[index] : BAD_INPUT; };
  
  void addEntry(const string &entry);
  //deleteEntry will delete ALL matching entries. The bool is an error catching mechanism False means that the array doesn't exist (null) or its empty or that there wasn't a match
  bool deleteEntry(const string &entry);
  
  
private:
  int mSize = 0;
  string *mDynamicArray = nullptr;
  
  //helper function to find the number of matches to resize DynamicArray for deleteEntry
  int getNumMatchingEntries(const string& entry) const;
  //helper function to copy all entries in dynamically allocated array returns false if there input array has a size < 0 or size != 0 when DynamicArray = nullptr
  bool copyData(const DynamicStringArray &srcArray);
};







#endif /* DYNAMICSTRINGARRAY_H */

