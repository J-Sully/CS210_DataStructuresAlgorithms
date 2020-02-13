//
//  DYNAMICARRAY.h
//  CS210_Assignment3_TemplatedClass
/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  Created by Jessie Sully on 2/12/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <string>
using namespace std;

template <typename T>
class DynamicArray {
public:
  //default constructor initializes size to zero and dynamicArray to nullptr
  DynamicArray();
  DynamicArray(const DynamicArray& srcArray);
  ~DynamicArray() {delete [] mDynamicArray;}
  
  DynamicArray& operator=(const DynamicArray& srcArray);
  
  int getSize() const { return mSize; }
  //returns a desired BAD_INPUT string in cases of error - array doesn't exist (null) or is empty or index is out of range
  const T& getEntry(int index) const { return index >= 0 && index < mSize
    ? mDynamicArray[index] : NULL; };
  void addEntry(const T &entry);
  //deleteEntry will delete ALL matching entries. The bool is an error catching mechanism False means that the array doesn't exist (null) or its empty or that there wasn't a match
  bool deleteEntry(const T &entry);
  
private:
  int mSize = 0;
  T *mDynamicArray = nullptr;
  
  //helper function to find the number of matches to resize DynamicArray for deleteEntry
  int getNumMatchingEntries(const T &entry) const;
  //helper function to copy all entries in dynamically allocated array returns false if there input array has a size < 0 or size != 0 when DynamicArray = nullptr
  bool copyData(const DynamicArray &srcArray);
};

template <typename T>
DynamicArray<T>::DynamicArray() {
  mSize = 0;
  mDynamicArray = nullptr;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &srcArray) {
  copyData(srcArray);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray &srcArray) {
  copyData(srcArray);
  return *this;
}

template <typename T>
bool DynamicArray<T>::copyData(const DynamicArray &srcArray) {
  mSize = srcArray.mSize;
  if (mSize > 0 && srcArray.mDynamicArray != nullptr) {
    delete [] mDynamicArray; // this is safe, I checked.
    mDynamicArray = new T[mSize];
    for (int i = 0; i < mSize; i++) {
      mDynamicArray[i] = srcArray.mDynamicArray[i];
    }
    return true;
  }
  else {
    mSize = 0;
    mDynamicArray = nullptr;
    return false;
  }
}

template <typename T>
void DynamicArray<T>::addEntry(const T &entry) {
  T *tempArray = mDynamicArray;
  mSize++;
  mDynamicArray = new T[mSize];
  // make sure array exists
  if (tempArray != nullptr) {
    for (int i = 0; i < mSize - 1; i++) {
      mDynamicArray[i] = tempArray[i];
    }
    delete [] tempArray;
  }
  mDynamicArray[mSize - 1] = entry;
}

template <typename T>
int DynamicArray<T>::getNumMatchingEntries(const T &entry) const {
  int numEntries = 0;
  if (mSize > 0) {
    for (int i = 0; i < mSize; i++) {
      if (mDynamicArray[i] == entry) {
        numEntries++;
      }
    }
  }
  return numEntries;
}

template <typename T>
bool DynamicArray<T>::deleteEntry(const T &entry) {
  T *tempArray = mDynamicArray;
  int numEntries = getNumMatchingEntries(entry);
  int newSize = mSize - numEntries;
  
  if (newSize == 0 && mSize > 0) {
    mSize = 0;
    delete [] mDynamicArray;
    mDynamicArray = nullptr;
  }
  
  else if (newSize != mSize) {
    mDynamicArray = new T[newSize];
    for (int i = 0, j = 0; j < newSize && i < mSize; i++) {
      if (tempArray[i] != entry) {
        mDynamicArray[j] = tempArray[i];
        j++;
      }
    }
    delete [] tempArray;
    mSize = newSize;
  }
  
  else {
    return false;
  }
  return true;
}

#endif /* DYNAMICARRAY_H */
