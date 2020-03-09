/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  NODE.h
//  CS260_Assignment4_LinkedLists
//
//  Created by Jessie Sully on 2/25/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef NODE_H
#define NODE_H

#include <string>
#include <cfloat>
using namespace std;

// static - keeps track of number of instances to check for memory leak
// Not part of template, to keep track of all variants.
static int sNumNodeObjects = 0;

template <typename T>
class Node {
public:
  Node() { sNumNodeObjects++; }; // update memory leak tracking number
  Node(T object) : mObject(object) { sNumNodeObjects++; } // update memory leak tracking number
  ~Node();
  
  template <typename U> // all instantiations of this template are my friends
  friend ostream& operator<<(ostream& ostr, const Node<U>* node);
  
  T& getObject() { return mObject; }
  const T& getObject() const { return mObject; }
  Node* getNext() { return mNextNode; }
  const Node* getNext() const { return mNextNode; }
  Node* getPrev() { return mPrevNode; }
  const Node* getPrev() const { return mPrevNode; }
  
  void linkNext(Node<T>* next);
  void linkPrev(Node<T>* prev);
  void unlink();
  
private:
  T mObject;
  Node* mNextNode = nullptr;
  Node* mPrevNode = nullptr;
};


template <typename T>
Node<T>::~Node() {
  unlink();
  // update memory leak tracking number
  sNumNodeObjects--;
}

template <typename T>
void Node<T>::linkNext(Node<T>* next) {
  mPrevNode = next->mPrevNode;
  mNextNode = next;
  if (mPrevNode != nullptr) {
    mPrevNode->mNextNode = this;
  }
  mNextNode->mPrevNode = this;
}

template <typename T>
void Node<T>::linkPrev(Node<T>* prev) {
  mNextNode = prev->mNextNode;
  mPrevNode = prev;
  if (mNextNode != nullptr) {
    mNextNode->mPrevNode = this;
  }
  mPrevNode->mNextNode = this;
}

template <typename T>
void Node<T>::unlink() {
  // unlink node
  if (mNextNode != nullptr) {
    mNextNode->mPrevNode = mPrevNode;
  }
  if (mPrevNode != nullptr) {
    mPrevNode->mNextNode = mNextNode;
  }
  mPrevNode = nullptr;
  mNextNode = nullptr;
}

template<typename T>
ostream& operator<<(ostream& ostr, const Node<T>* node)
{
  ostr << node->mObject;
  return ostr;
}

#endif /* NODE_H */
