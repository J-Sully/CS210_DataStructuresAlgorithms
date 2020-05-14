/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  StudentHT.h
//  CS210_Assignment11_Hashing
//
//  Created by Jessie Sully on 5/11/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef StudentHT_h
#define StudentHT_h

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

static int sNumNodeObjects = 0;
static double sNumNodesSearched = 0;
template <typename T>
class StudentHT {
public: 
  StudentHT() {}
  StudentHT(unsigned int size);
  StudentHT(const string &filename) { loadData(filename); }
  ~StudentHT();
  void insert(unsigned int key, const T& value);
  T* search(unsigned int key) const;

private:
  struct NodeType {
    NodeType() { sNumNodeObjects++; }
    NodeType(unsigned int key, const T &value) : mKey(key), mValue(value)
      { sNumNodeObjects++; }
    ~NodeType();
    T mValue;
    unsigned int mKey = 0;
    NodeType* mNextNode = nullptr;
  };
  void loadData(const string& filename);
  void initHashTable();
  // no error checking
  unsigned int getHashIdx(unsigned int val) const { return val % mMax; }
  NodeType** mHashTable = nullptr;
  // size of hash table
  unsigned int mMax = 0;
};

template <typename T>
void StudentHT<T>::initHashTable() {
  for (int i = 0; i < mMax; i++) {
    mHashTable[i] = nullptr;
  }
}

template <typename T>
StudentHT<T>::NodeType::~NodeType() {
  mNextNode = nullptr;
  sNumNodeObjects--;
}

template <typename T>
StudentHT<T>::StudentHT(unsigned int size) : mMax(size) {
  mHashTable = new NodeType*[size];
  initHashTable();
}

template <typename T>
StudentHT<T>::~StudentHT() {
  NodeType* del = nullptr;
  NodeType* next = nullptr;
  if (mHashTable != nullptr) {
    for (int i = 0; i < mMax; i++) {
      next = mHashTable[i];
      while (next != nullptr) {
        del = next;
        next = next->mNextNode;
        delete del;
      }
    }
    delete [] mHashTable;
  }
}

template <typename T>
void StudentHT<T>::loadData(const string& filename) {
  ifstream finputFile(filename);
  stringstream ss;
  string input;
  unsigned int key;
  if (finputFile) {
    finputFile >> mMax;
    mHashTable = new NodeType*[mMax];
    initHashTable();
    getline(finputFile,input);
    getline(finputFile,input);
    while (getline(finputFile, input)) {
      ss.str(input);
      ss >> key;
      insert(key, T(input));
    }
    finputFile.close();
  }
}

template <typename T>
void StudentHT<T>::insert(unsigned int key, const T& value) {
  unsigned int hash = getHashIdx(key);
  NodeType* cur = mHashTable[hash];
  if (cur == nullptr) {
    mHashTable[hash] = new NodeType(key, value);
    return;
  }
  while (cur->mNextNode != nullptr) {
    cur = cur->mNextNode;
  }
  cur->mNextNode = new NodeType(key, value);
}

template <typename T>
T* StudentHT<T>::search(unsigned int key) const {
  unsigned int hash = getHashIdx(key);
  NodeType* cur = mHashTable[hash];
  while (cur != nullptr) {
    sNumNodesSearched++;
    if (cur->mKey == key) {
      return &cur->mValue;
    }
    cur = cur->mNextNode;
  }
  return nullptr;
}

#endif /* StudentHT_h */
