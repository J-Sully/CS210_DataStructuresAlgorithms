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
#include <iostream>
using namespace std;

// static to keep track of instances to check memory leak. Keeps track of all variants.
static int sNumNodeObjects = 0;

// Element holds an entry's index and value. This allows for greater control and compensation for holes.
template <typename T>
struct Element {
  Element(){ sNumNodeObjects++; } // update sNumNodeObjects
  Element(int index, T value) : mIndex(index), mValue(value) { sNumNodeObjects++; } // update sNumNodeObjects
  ~Element() { sNumNodeObjects--; } // update sNumNodeObjects
  
  // copies member variables
  Element& operator=(const Element& element);
  // makes streaming easier
  template<typename U>
  friend ostream& operator<<(ostream& ostr, const Element<U>* element);
  
  T mValue;
  int mIndex = 0;
};

// copies member variables
template <typename T>
Element<T>& Element<T>::operator=(const Element<T> &element) {
  mValue = element.mValue;
  mIndex = element.mIndex;
  return *this;
}

// makes streaming easier
template<typename U>
ostream& operator<<(ostream& ostr, const Element<U>* element) {
  ostr << element->mIndex << "=>" << element->mValue;
  return ostr;
}


// Sortable array that implements quickSort for sorting
template <typename T>
class MySortableArray {
public:
  //default constructor initializes size to zero and dynamicArray to nullptr
  MySortableArray();
  MySortableArray(const MySortableArray& srcArray);
  ~MySortableArray() { delete [] mMySortableArray; }
  
  MySortableArray& operator=(const MySortableArray& srcArray);
  
  int getSize() const { return mSize; }
  bool isEmpty() const { return mSize == 0; }
  
  // returns desired entry or throws exception - make sure to validate indexes
  const T& getEntry(int index) const;
  
  // insertion sort to add entry by index value, will overwrite index if index is already in use.
  void addEntry(int index, T value);
  
  // error catching mechanism - returns false if index is not in array.
  bool deleteIndex(int index);
  
  // implements quick sort to sort a certain number of elements - note that it is not index based.
  bool sort(int numElements);
  
  // displays contents of array using "<index>=><value>" format separated by spaces.
  void display(ostream &str) const;
  
  // validates that index is in array
  bool validateIndex(int index) const;
  
private:
  int mSize = 0;
  Element<T> *mMySortableArray = nullptr;
  
  // helper function to copy all entries in dynamically allocated array returns false if there input array has a size < 0 or size != 0 when MySortableArray = nullptr
  bool copyData(const MySortableArray &srcArray);
  
  // helper function to find the loc of the correct index or -1 if mSize = 0.
  int getLoc(int index);
  
  // helper function to increase size of the array and leaves a hole for adding an entry.
  void increaseArraySize(int gapIndex);
  
  // These three helper functions help implements the sort function using QuickSort.
  void quickSort(int firstIndex, int last);
  void swap(int firstIndex, int secondIndex);
  int partition(int low, int high);
  
  friend void runTests();
};

template <typename T>
MySortableArray<T>::MySortableArray() {
  mSize = 0;
  mMySortableArray = new Element<T>[mSize];
}

template <typename T>
MySortableArray<T>::MySortableArray(const MySortableArray &srcArray) {
  copyData(srcArray);
}
 
template <typename T>
MySortableArray<T>& MySortableArray<T>::operator=(const MySortableArray &srcArray) {
  copyData(srcArray);
  return *this;
}

template <typename T>
bool MySortableArray<T>::copyData(const MySortableArray &srcArray) {
  mSize = srcArray.mSize;
  delete [] mMySortableArray; // this is safe, I checked.
  mMySortableArray = new Element<T>[mSize];
  for (int i = 0; i < mSize; i++) {
    mMySortableArray[i] = srcArray.mMySortableArray[i];
  }
  return true;
}

template <typename T>
void MySortableArray<T>::increaseArraySize(int gapIndex) {
  Element<T>* sourceArray = mMySortableArray;
  mMySortableArray = new Element<T>[mSize + 1];
  for(int i = 0, j = 0; i < mSize; i++, j++) {
    if (i == gapIndex) {
      j++;
    }
    mMySortableArray[j] = sourceArray[i];
  }
  mSize++;
  delete [] sourceArray;
}

template <typename T>
const T& MySortableArray<T>::getEntry(int index) const {
  for (int i = 0; i < mSize; i++) {
    if (mMySortableArray[i].mIndex == index) {
      return mMySortableArray[i].mValue;
    }
  }
  throw out_of_range("invalid index");
};

template <typename T>
int MySortableArray<T>::getLoc(int index) {
  int locAdd = 0;
  for (; locAdd < mSize && mMySortableArray[locAdd].mIndex < index ; locAdd++);
  return locAdd;
}

template <typename T>
void MySortableArray<T>::addEntry(int index, T value) {
  int locAdd = 0;
  locAdd = getLoc(index);
  if (mMySortableArray[locAdd].mIndex == index) {
    mMySortableArray[locAdd].mValue = value;
    return;
  }
  increaseArraySize(locAdd);
  mMySortableArray[locAdd].mIndex = index;
  mMySortableArray[locAdd].mValue = value;
  /*
  if (mSize > 0) {
    
  }
  else {
    mMySortableArray[0].mIndex = index;
    mMySortableArray[0].mValue = value;
    mSize++;
  }
   */
}

template <typename T>
bool MySortableArray<T>::deleteIndex(int index) {
  if (isEmpty()) return false;
  Element<T>* tempArray;
  int loc = getLoc(index);
  if (loc >= mSize) return false;
  if (mMySortableArray[loc].mIndex != index) return false;
  
  tempArray = mMySortableArray;
  mMySortableArray = new Element<T>[mSize - 1];
  for(int i = 0, j = 0; i < mSize; i++, j++) {
    if (tempArray[i].mIndex == index) {
      i++;
    }
    mMySortableArray[j] = tempArray[i];
  }

  delete [] tempArray;
  mSize--;
  return true;
}


template <typename T>
bool MySortableArray<T>::sort(int numElements) {
  if (numElements >= 0) {
    if (numElements >= mSize) {
      numElements = mSize;
    }
    quickSort(0, numElements - 1);
    return true;
  }
  return false;
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
  //int pivotIndex = low;
  T pivot = mMySortableArray[high].mValue;
  do {
    while (low < high && mMySortableArray[low].mValue < pivot) {
      low++;
    }
    while (high > low && mMySortableArray[high].mValue > pivot) {
      high--;
    }
    if (low < high) {
      swap(low, high);
    }
  } while (low < high);
  //pivotIndex = high;
  //return pivotIndex;
  return high;
}

template <typename T>
void MySortableArray<T>::swap(int firstIndex, int secondIndex) {
  T temp = mMySortableArray[firstIndex].mValue;
  mMySortableArray[firstIndex].mValue = mMySortableArray[secondIndex].mValue;
  mMySortableArray[secondIndex].mValue = temp;
}

template <typename T>
void MySortableArray<T>::display(ostream &ostr) const {
  for (int i = 0; i < mSize; i++) {
    ostr << &mMySortableArray[i] << ' ';
  }
  ostr << endl;
}

template <typename T>
bool MySortableArray<T>:: validateIndex(int index) const {
  for (int i = 0; i < mSize; i++) {
    if (mMySortableArray[i].mIndex == index) {
      return true;
    }
  }
  return false;
}

#endif /* MYSORTABLEARRAY_H */
