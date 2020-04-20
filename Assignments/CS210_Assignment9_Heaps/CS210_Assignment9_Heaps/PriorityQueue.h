/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  PriorityQueue.h
//  CS210_Assignment9_Heaps
//
//  Created by Jessie Sully on 4/17/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <iostream>
using namespace std;

// static to keep track of instances to check memory leak. Keeps track of all variants.
static int sNumNodeObjects = 0;

// Priority Queue Node
struct Node {
  // increments sNumNodeObjects for memory leak check
  Node() { sNumNodeObjects++; }
  // increments sNumNodeObjects for memory leak check
  Node(const int priority, const string &name) : mPriority(priority), mName(name) { sNumNodeObjects++; }
  // decrements sNumNodeObjects for memory leak check
  ~Node();
  
  // copies member variables
  Node& operator=(const Node& node);
  
  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const Node &node);
  
  int mPriority = 0;
  string mName;
};

Node::~Node() {
  sNumNodeObjects--;
}

Node& Node::operator=(const Node &node) {
  mPriority = node.mPriority;
  mName = node.mName;
  return *this;
}

ostream& operator<<(ostream& ostr, const Node &node) {
  ostr << node.mPriority << ' ' << node.mName;
  return ostr;
}


#ifdef RUN_TESTS
static const int DEFAULT_SIZE = 2;
#else
static const int DEFAULT_SIZE = 10;
#endif /* RUN_TESTS */

// Binary Search Tree
class PriorityQueue {
public:
  PriorityQueue() { mMaxHeap = new Node[DEFAULT_SIZE]; }
  // Runs clearTree to free allocated space
  ~PriorityQueue();
  
  // returns mRoot
  Node* getRoot() const { return mMaxHeap; }
  bool isEmpty() const { return mSize == 0; }
  void penqueue(int priority, const string &mName);
  Node pdequeue();
  void clearMaxHeap();
  
  friend ostream& operator<<(ostream& ostr, const PriorityQueue &queue);
  
private:
  int mCapacity = DEFAULT_SIZE;
  int mSize = 0;
  Node* mMaxHeap = nullptr;
  void increaseCapacity();
  void copyNodes(Node* largerArray) const;
  void swapNodes(int index1, int index2);
  void reheapify(int startIndex);
  void siftDown(int startIndex);
};

PriorityQueue::~PriorityQueue() {
  delete [] mMaxHeap;
}

void PriorityQueue::clearMaxHeap() {
  delete [] mMaxHeap;
  mSize = 0;
  mCapacity = DEFAULT_SIZE;
  mMaxHeap = new Node[DEFAULT_SIZE];
}

void PriorityQueue::copyNodes(Node* largerArray) const {
  for(int i = 0; i < mSize; i++) {
    largerArray[i] = mMaxHeap[i];
  }
}

void PriorityQueue::increaseCapacity() {
  mCapacity += DEFAULT_SIZE;
  Node* largerArray = new Node[mCapacity];
  copyNodes(largerArray);
  delete [] mMaxHeap;
  mMaxHeap = largerArray;
}

void PriorityQueue::swapNodes(int index1, int index2) {
  Node storageNode;
  storageNode = mMaxHeap[index1];
  mMaxHeap[index1] = mMaxHeap[index2];
  mMaxHeap[index2] = storageNode;
}

void PriorityQueue::reheapify(int startIndex) {
  for (int i = startIndex, j = (startIndex - 1) / 2; i > 0;
       i = j, j = (j - 1) / 2) {
    if (mMaxHeap[i].mPriority > mMaxHeap[j].mPriority) {
      swapNodes(i, j);
    }
  }
}

void PriorityQueue::penqueue(int priority, const string &name) {
  if (mSize == mCapacity) {
    increaseCapacity();
  }
  mMaxHeap[mSize].mPriority = priority;
  mMaxHeap[mSize].mName = name;
  reheapify(mSize);
  mSize++;
}

void PriorityQueue::siftDown(int startIndex) {
  for (int i = startIndex, j = 2 * startIndex + 1; j < mSize;
       i = j, j = 2 * i + 1) {
    if (mMaxHeap[j].mPriority < mMaxHeap[j + 1].mPriority ) {
      j++;
    }
    if (mMaxHeap[i].mPriority < mMaxHeap[j].mPriority) {
      swapNodes(i, j);
    }
  }
}

Node PriorityQueue::pdequeue() {
  Node returnNode;
  returnNode = mMaxHeap[0];
  mMaxHeap[0] = mMaxHeap[mSize - 1];
  mMaxHeap[mSize - 1].mPriority = 0;
  mMaxHeap[mSize - 1].mName.clear();
  mSize--;
  siftDown(0);
  return returnNode;
}

ostream& operator<<(ostream& ostr, const PriorityQueue &queue) {
  for (int i = 0; i < queue.mSize; i++) {
    ostr << queue.mMaxHeap[i] << endl;
  }
  return ostr;
}

#endif /* PriorityQueue_h */
