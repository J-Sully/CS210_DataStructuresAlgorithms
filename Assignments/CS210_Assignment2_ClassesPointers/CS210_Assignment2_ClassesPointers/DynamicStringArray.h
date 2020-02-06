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
public:
  DynamicStringArray();
  DynamicStringArray(const DynamicStringArray &srcArray);
  ~DynamicStringArray() {delete [] mDynamicArray;}
  DynamicStringArray& operator=(const DynamicStringArray &srcArray);
  string getEntry(int index) const {return mSize > 0 ? mDynamicArray[index] : "";};
  int getSize() const {return mSize;}
  void addEntry(const string &entry);
  bool deleteEntry(const string &entry);
  int getNumMatchingEntries(const string &entry) const;
  
private:
  int mSize = 0;
  string *mDynamicArray = nullptr;
};







#endif /* DYNAMICSTRINGARRAY_H */

