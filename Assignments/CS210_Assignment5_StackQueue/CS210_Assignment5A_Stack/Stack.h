//
//  Stack.h
//  CS210_Assignment5_StackQueue
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include "Node.h"

template <typename T>
class Stack {
public:
  Stack(){}
  ~Stack();
  void push(T element);
  T pop();
  bool isEmpty() const { return mHead == nullptr; }
  void display(ostream& output) const;
  int getSize() const { return mSize; }
  
  //This is used in getEntry to allow personalized error strings
  static const int EMPTY_STACK_INTELEMENT;
  
private:
  Node<T>* mHead = nullptr;
  int mSize = 0;
};

template <typename T>
Stack<T>::~Stack() {
  while (mHead != nullptr) {
    mHead = mHead->nextNode;
    delete mHead->prevNode;
  }
}

template <typename T>
void Stack<T>::push(T element) {
  Node<T>* newNode = new Node<T>(element);
  if (mHead == nullptr) {
    mHead = newNode;
  }
  else {
    newNode->nextNode = mHead;
    newNode->prevNode = nullptr;
    mHead->prevNode = newNode;
    mHead = newNode;
  }
  mSize++;
}

//Function to pop element from top of stack.
template <typename T>
T Stack<T>::pop() {
  if (isEmpty()) {
    cerr << "Error, stack is empty." << endl;
    return EMPTY_STACK_INTELEMENT;
  }
  else {
    T element = mHead->mObject;
    if (mSize == 1) {
      delete mHead;
      mHead = nullptr;
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
void Stack<T>::display(ostream &output) const {
  for(Node<T>* cursor = mHead; cursor != nullptr; cursor = cursor->nextNode) {
    cursor->writeToStream(output);
  }
}


#endif /* Stack_h */
