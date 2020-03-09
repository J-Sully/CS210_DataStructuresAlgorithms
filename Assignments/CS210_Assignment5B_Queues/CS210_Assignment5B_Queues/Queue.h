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
  const T& getRear() const { return mTail->mObject; }
  const T& getFront() const { return mHead->mObject; }
  
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
    T element = T();
    return element;
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
    }
    mSize--;
    return element;
  }
}

template<typename T>
void Queue<T>::display(ostream &output) const {
  for(Node<T>* cursor = mHead; cursor != nullptr; cursor = cursor->nextNode) {
    output << cursor << endl;
  }
}


#endif /* Queue_h */
