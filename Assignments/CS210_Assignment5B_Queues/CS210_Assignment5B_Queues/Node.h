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

template <typename T>
struct Node {
public:
  Node() { sNumObjects++; }; // update memory leak tracking number
  Node(T object) : mObject(object) { sNumObjects++; } // update memory leak tracking number
  ~Node();
  
  void writeToStream(ostream &output);
  
  static int sNumObjects;
  
  T mObject;
  Node* nextNode = nullptr;
  Node* prevNode = nullptr;
};

// static - keeps track of number of instances to check for memory leak
template <typename T>
int Node<T>::sNumObjects = 0;

template <typename T>
Node<T>::~Node() {
  // unlink node
  if (nextNode != nullptr) {
    nextNode->prevNode = prevNode;
    prevNode = nullptr;
  }
  if (prevNode != nullptr) {
    prevNode->nextNode = nextNode;
    nextNode = nullptr;
  }
  // update memory leak tracking number
  sNumObjects--;
}

template<>
void Node<int>::writeToStream(ostream &output) {
  output << mObject << endl;
}

template<typename T>
void Node<T>::writeToStream(ostream &output) {
  mObject->writeToStream(output);
}

#endif /* NODE_H */
