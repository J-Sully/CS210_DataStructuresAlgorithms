/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  DynamicArray.h
//  CS210_Assignment10_Graphs
//
//  Created by Jessie Sully on 4/23/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
using namespace std;

#ifdef RUN_TESTS
static const int DEFAULT_SIZE = 2;
#else
static const int DEFAULT_SIZE = 10;
#endif /* RUN_TESTS */

struct Edge;
// Dynamic Array
template <typename T>
class DynamicArray {
public:
  DynamicArray() { mArray = new T[DEFAULT_SIZE]; }
  ~DynamicArray() { delete [] mArray; };
  
  T& operator[](int index) const;
  const DynamicArray<T>& operator=(const DynamicArray<T> &array);
  
  T* getArray() const { return mArray; }
  int getSize() const { return mSize; }
  int getCapacity() const { return mCapacity; }
  void addObject(const T &object);
  bool isEmpty() const { return mSize == 0; }
  void clear();
  bool validateIndex(int index) { return index >= 0 && index < mSize; }
  
  template <typename U>
  friend ostream& operator<<(ostream& ostr, const DynamicArray<T> &array);
  
private:
  int mCapacity = DEFAULT_SIZE;
  int mSize = 0;
  T* mArray = nullptr;
  void increaseCapacity();
  void copyNodes(T* newArray) const;
};

template <typename T>
T& DynamicArray<T>::operator[](int index) const {
  if (index < mSize && index >= 0) return mArray[index];
  throw out_of_range("invalid index");
}

template <typename T>
const DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &array) {
  delete [] mArray;
  mCapacity = array.mCapacity;
  mArray = new T[mCapacity];
  mSize = array.mSize;
  for (int i = 0; i < mSize; i++) {
    mArray[i] = array.mArray[i];
  }
  return *this;
}

template <typename T>
void DynamicArray<T>::clear() {
  delete [] mArray;
  mSize = 0;
  mCapacity = DEFAULT_SIZE;
  mArray = new T[DEFAULT_SIZE];
}

template <typename T>
void DynamicArray<T>::copyNodes(T* newArray) const {
  for(int i = 0; i < mSize; i++) {
    newArray[i] = mArray[i];
  }
}

template <typename T>
void DynamicArray<T>::increaseCapacity() {
  mCapacity += DEFAULT_SIZE;
  T* largerArray = new T[mCapacity];
  copyNodes(largerArray);
  delete [] mArray;
  mArray = largerArray;
}

template <typename T>
void DynamicArray<T>::addObject(const T &object) {
  if (mSize == mCapacity) {
    increaseCapacity();
  }
  mArray[mSize] = object;
  mSize++;
}

template <typename T>
ostream& operator<<(ostream& ostr, const DynamicArray<T> &array) {
  for (int i = 0; i < array.getSize(); i++) {
    ostr << array[i] << endl;
  }
  return ostr;
}

#endif /* DynamicArray_h */
