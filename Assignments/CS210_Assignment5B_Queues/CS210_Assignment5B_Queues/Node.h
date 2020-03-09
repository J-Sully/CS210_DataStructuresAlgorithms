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
struct Node {
public:
  Node() { sNumNodeObjects++; }; // update memory leak tracking number
  Node(T object) : mObject(object) { sNumNodeObjects++; } // update memory leak tracking number tracking number
  ~Node();
  
  template <typename U> // all instantiations of this template are my friends
  friend ostream& operator<<(ostream& ostr, const Node<U>* node);
  
  T mObject;
  Node* nextNode = nullptr;
  Node* prevNode = nullptr;
};

template <typename T>
Node<T>::~Node() {
  // unlink node
  if (nextNode != nullptr) {
    nextNode->prevNode = prevNode;
  }
  if (prevNode != nullptr) {
    prevNode->nextNode = nextNode;
  }
  prevNode = nullptr;
  nextNode = nullptr;
  // update memory leak tracking number
  sNumNodeObjects--;
}

template<typename T>
ostream& operator<<(ostream& ostr, const Node<T>* node)
{
  ostr << node->mObject;
  return ostr;
}

#endif /* NODE_H */
