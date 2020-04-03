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

template <typename T>
struct Element {
  Element(){ sNumNodeObjects++; }
  Element(int index, T value) : mIndex(index), mValue(value) { sNumNodeObjects++; }
  ~Element() { sNumNodeObjects--; }
  
  Element& operator=(const Element& element);
  template<typename U>
  friend ostream& operator<<(ostream& ostr, const Element<U>* element);
  
  T mValue;
  int mIndex = 0;
};

template <typename T>
Element<T>& Element<T>::operator=(const Element<T> &element) {
  mValue = element.mValue;
  mIndex = element.mIndex;
  return *this;
}

template<typename U>
ostream& operator<<(ostream& ostr, const Element<U>* element) {
  ostr << element->mIndex << "=>" << element->mValue;
  return ostr;
}

template <typename T>
class MySortableArray {
public:
  //default constructor initializes size to zero and dynamicArray to nullptr
  MySortableArray();
  MySortableArray(int size);
  MySortableArray(const MySortableArray& srcArray);
  ~MySortableArray() { delete [] mMySortableArray; }
  
  MySortableArray& operator=(const MySortableArray& srcArray);
  
  //inititalizes the array
  void init() { mMySortableArray = new Element<T>[0]; }
  int getSize() const { return mSize; }
  //returns desired entry or throws exception
  const T& getEntry(int index) const;
  // insertion sort to add entry by index value, overwrites same index
  void addEntry(int index, T value);
  //deleteEntry will delete ALL matching entries. The bool is an error catching mechanism False means that the array doesn't exist (null) or its empty or that there wasn't a match
  bool deleteIndex(int index);
  bool sort(int numElements);
  bool isEmpty() const { return mSize == 0; }
  void display(ostream &str) const;
  bool validateIndex(int index) const;
  
private:
  int mSize = 0;
  Element<T> *mMySortableArray = nullptr;
  
  //helper function to copy all entries in dynamically allocated array returns false if there input array has a size < 0 or size != 0 when MySortableArray = nullptr
  bool copyData(const MySortableArray &srcArray);
  //helper function to find the loc of the right index, returns -1 if not found.
  int getLoc(int index);
  void increaseArraySize(int newSize, int gapIndex);
  void quickSort(int firstIndex, int last);
  void swap(int firstIndex, int secondIndex);
  int partition(int low, int high);
};

template <typename T>
MySortableArray<T>::MySortableArray() {
  mSize = 0;
  init();
}

template <typename T>
MySortableArray<T>::MySortableArray(const MySortableArray &srcArray) {
  copyData(srcArray);
}

template <typename T>
MySortableArray<T>::MySortableArray(int size) {
  if (size > 0) {
    mSize = size;
    mMySortableArray = new Element<T>[size];
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
    mMySortableArray = new Element<T>[mSize];
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
void MySortableArray<T>::increaseArraySize(int newSize, int gapIndex) {
  Element<T>* sourceArray = mMySortableArray;
  mMySortableArray = new Element<T>[newSize];
  if (!isEmpty()) {
    for(int i = 0, j = 0; i < mSize; i++, j++) {
      if (i == gapIndex) {
        j++;
      }
      mMySortableArray[j] = sourceArray[i];
    }
  }
  mSize = newSize;
  delete [] sourceArray;
}

template <typename T>
const T& MySortableArray<T>::getEntry(int index) const {
  for (int i = 0; i < mSize; i++) {
    if (mMySortableArray[i].mIndex == index) {
      return mMySortableArray[i].mValue;
    }
  }
  throw logic_error("invalid index");
};

template <typename T>
int MySortableArray<T>::getLoc(int index) {
  int locAdd = -1;
  int i = 0;
  if (mSize > 0) {
    for (; i < mSize && mMySortableArray[i].mIndex < index ; i++);
    locAdd = i;
  }
  return locAdd;
}

template <typename T>
void MySortableArray<T>::addEntry(int index, T value) {
  int locAdd = 0;
  if (mSize > 0) {
    locAdd = getLoc(index);
    increaseArraySize(mSize + 1, locAdd);
    mMySortableArray[locAdd].mIndex = index;
    mMySortableArray[locAdd].mValue = value;
  }
  else {
    mMySortableArray[0].mIndex = index;
    mMySortableArray[0].mValue = value;
    mSize++;
  }
}

template <typename T>
bool MySortableArray<T>::deleteIndex(int index) {
  Element<T>* tempArray = nullptr;
  int loc = getLoc(index);
  if (loc != -1) {
    if (mSize - 1 > 0) {
      tempArray = mMySortableArray;
      mMySortableArray = new Element<T>[mSize - 1];
      for(int i = 0, j = 0; i < mSize; i++, j++) {
        if (tempArray[i].mIndex == index) {
          i++;
        }
        mMySortableArray[j] = tempArray[i];
      }
    }
    else {
      mMySortableArray = nullptr;
    }
    delete [] tempArray;
    mSize--;
    return true;
  }
  return false;
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
