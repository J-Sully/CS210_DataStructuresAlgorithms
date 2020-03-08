/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  Queue.h
//  CS210_Assignment5_Queue
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include "Node.h"

template <typename T>
class Queue {
public:
  Queue(){}
  ~Queue();
  void enqueue(T element);
  T dequeue();
  bool isEmpty() const { return mHead == nullptr; }
  void display(ostream& output) const;
  int getSize() const { return mSize; }
  const T& getRear() const { return mTail != nullptr ? mTail->mObject : EMPTY_QUEUE_INTELEMENT; }
  const T& getFront() const { return mHead != nullptr ? mHead->mObject : EMPTY_QUEUE_INTELEMENT; }
  
  //This is used in getEntry to allow personalized error strings
  static const int EMPTY_QUEUE_INTELEMENT;
  
private:
  Node<T>* mHead = nullptr;
  Node<T>* mTail = nullptr;
  int mSize = 0;
};

template <typename T>
Queue<T>::~Queue() {
  while (mHead != nullptr) {
    mHead = mHead->nextNode;
    delete mHead->prevNode;
  }
}

template <typename T>
void Queue<T>::enqueue(T element) {
  Node<T>* newNode = new Node<T>(element);
  if (mHead == nullptr) {
    mHead = newNode;
    mTail = newNode;
  }
  else {
    newNode->nextNode = nullptr;
    newNode->prevNode = mTail;
    mTail->nextNode = newNode;
    mTail = newNode;
  }
  mSize++;
}

//Function to dequeue element from top of stack.
template <typename T>
T Queue<T>::dequeue() {
  if (isEmpty()) {
    return EMPTY_QUEUE_INTELEMENT;
  }
  else {
    T element = mHead->mObject;
    if (mSize == 1) {
      delete mHead;
      mHead = nullptr;
      mTail = nullptr;
    }
    else {
      mHead = mHead->nextNode;
      delete mHead->prevNode;
      mHead->prevNode = nullptr;
    }
    mSize--;
    return element;
  }
}

template<typename T>
void Queue<T>::display(ostream &output) const {
  for(Node<T>* cursor = mHead; cursor != nullptr; cursor = cursor->nextNode) {
    cursor->writeToStream(output);
  }
}


#endif /* Queue_h */
