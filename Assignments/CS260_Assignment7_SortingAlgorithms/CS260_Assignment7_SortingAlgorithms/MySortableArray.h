//
//  MYSORTABLEARRAY.h
//  CS210_Assignment3_TemplatedClass
/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  Created by Jessie Sully on 2/12/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef MYSORTABLEARRAY_H
#define MYSORTABLEARRAY_H

#include <string>
using namespace std;

template <typename T>
class MySortableArray {
public:
  //default constructor initializes size to zero and dynamicArray to nullptr
  MySortableArray();
  MySortableArray(int size);
  MySortableArray(const MySortableArray& srcArray);
  ~MySortableArray() {delete [] mMySortableArray;}
  
  MySortableArray& operator=(const MySortableArray& srcArray);
  
  int getSize() const { return mSize; }
  //returns a desired BAD_INPUT string in cases of error - array doesn't exist (null) or is empty or index is out of range
  const T& getEntry(int index) const { return index >= 0 && index < mSize
    ? mMySortableArray[index] : NULL; };
  void addEntry(const T &entry);
  //deleteEntry will delete ALL matching entries. The bool is an error catching mechanism False means that the array doesn't exist (null) or its empty or that there wasn't a match
  bool deleteEntry(const T &entry);
  void sort(int numElements);
  void setEntry(int index, const T &value);
  bool isEmpty() const { return mSize == 0; }
  
private:
  int mSize = 0;
  T *mMySortableArray = nullptr;
  
  //helper function to find the number of matches to resize MySortableArray for deleteEntry
  int getNumMatchingEntries(const T &entry) const;
  //helper function to copy all entries in dynamically allocated array returns false if there input array has a size < 0 or size != 0 when MySortableArray = nullptr
  bool copyData(const MySortableArray &srcArray);
  void increaseArraySize(int newSize);
  void quickSort(int firstIndex, int last);
  void swap(int firstIndex, int secondIndex);
  int partition(int low, int high);
};

template <typename T>
MySortableArray<T>::MySortableArray() {
  mSize = 0;
  mMySortableArray = nullptr;
}

template <typename T>
MySortableArray<T>::MySortableArray(const MySortableArray &srcArray) {
  copyData(srcArray);
}

template <typename T>
MySortableArray<T>::MySortableArray(int size) {
  if (size > 0) {
    mSize = size;
    mMySortableArray = new T[size];
  }
}

template <typename T>
MySortableArray<T>& MySortableArray<T>::operator=(const MySortableArray &srcArray) {
  copyData(srcArray);
  return *this;
}

template <typename T>
bool MySortableArray<T>::copyData(const MySortableArray &srcArray) {
  mSize = srcArray.mSize;
  if (mSize > 0 && srcArray.mMySortableArray != nullptr) {
    delete [] mMySortableArray; // this is safe, I checked.
    mMySortableArray = new T[mSize];
    for (int i = 0; i < mSize; i++) {
      mMySortableArray[i] = srcArray.mMySortableArray[i];
    }
    return true;
  }
  else {
    mSize = 0;
    mMySortableArray = nullptr;
    return false;
  }
}

template <typename T>
void MySortableArray<T>::increaseArraySize(int newSize) {
  T* sourceArray = mMySortableArray;
  mMySortableArray = new T[newSize]{0};
  if (!isEmpty()) {
    for(int i = 0; i < mSize; i++) {
      mMySortableArray[i] = sourceArray[i];
    }
  }
  delete sourceArray;
}

template <typename T>
void MySortableArray<T>::addEntry(const T &entry) {
  T *tempArray = mMySortableArray;
  mSize++;
  mMySortableArray = new T[mSize];
  // make sure array exists
  if (tempArray != nullptr) {
    for (int i = 0; i < mSize - 1; i++) {
      mMySortableArray[i] = tempArray[i];
    }
    delete [] tempArray;
  }
  mMySortableArray[mSize - 1] = entry;
}

template <typename T>
int MySortableArray<T>::getNumMatchingEntries(const T &entry) const {
  int numEntries = 0;
  if (mSize > 0) {
    for (int i = 0; i < mSize; i++) {
      if (mMySortableArray[i] == entry) {
        numEntries++;
      }
    }
  }
  return numEntries;
}

template <typename T>
bool MySortableArray<T>::deleteEntry(const T &entry) {
  T *tempArray = mMySortableArray;
  int numEntries = getNumMatchingEntries(entry);
  int newSize = mSize - numEntries;
  
  if (newSize == 0 && mSize > 0) {
    mSize = 0;
    delete [] mMySortableArray;
    mMySortableArray = nullptr;
  }
  
  else if (newSize != mSize) {
    mMySortableArray = new T[newSize];
    for (int i = 0, j = 0; j < newSize && i < mSize; i++) {
      if (tempArray[i] != entry) {
        mMySortableArray[j] = tempArray[i];
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

template <typename T>
void MySortableArray<T>::setEntry(int index, const T &value) {
  if (index >= mSize) {
    increaseArraySize(index + 1);
  }
  mMySortableArray[index] = value;
}

template <typename T>
void MySortableArray<T>::sort(int numElements) {
  if (numElements > mSize) {
    increaseArraySize(numElements);
  }
  if (mSize > 0) {
    quickSort(0, numElements - 1);
  }
}

template <typename T>
void MySortableArray<T>::quickSort(int first, int last) {
  int pivotIndex = 0;
  if (last - first >= 1) {
    pivotIndex = partition(first, last);
    quickSort(first, pivotIndex - 1);
    quickSort(pivotIndex + 1, last);
  }
}

template <typename T>
int MySortableArray<T>::partition(int low, int high) {
  int pivotIndex = low;
  T pivot = mMySortableArray[high];
  do {
    while (low < high && mMySortableArray[low] < pivot) {
      low++;
    }
    while (high > low && mMySortableArray[high] > pivot) {
      high--;
    }
    if (low < high) {
      swap(low, high);
    }
  } while (low < high);
  pivotIndex = high;
  return pivotIndex;
}

template <typename T>
void MySortableArray<T>::swap(int firstIndex, int secondIndex) {
  T temp = mMySortableArray[firstIndex];
  mMySortableArray[firstIndex] = mMySortableArray[secondIndex];
  mMySortableArray[secondIndex] = temp;
}

#endif /* MYSORTABLEARRAY_H */
