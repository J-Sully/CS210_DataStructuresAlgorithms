/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  LINKEDLIST.h
//  CS260_Assignment4_LINKEDLISTs
//
//  Created by Jessie Sully on 2/25/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <fstream>
using namespace std;

#include "Node.h"

class LinkedList {
public:
  LinkedList() { init(); }
  LinkedList(const string& filename) { loadFromFile(filename); }
  ~LinkedList();
  
  Node* getHead() const { return mHead; }
  bool setCursor(unsigned int accNum); // returns F if unable to find node
  
  void addNode(Node* addNode);
  void deleteNode(Node* delNode);
  
  void writeToStream(ostream&) const; // helper function to write out list data
  bool saveToFile(const string& filename); // returns F if unable to open file
  
private:
  bool findNodeAboveInstert(unsigned int accNum);
  bool loadFromFile(const string& filename); // returns F if unable to open file
  void init(); // helper function to initialize mHead
  Node* mHead = nullptr;
  Node* mCursor = nullptr;
  
};

void LinkedList::init() {
  mHead = new Node;
  mCursor = mHead;
}

LinkedList::~LinkedList() {
  Node* nextNode = mHead->nextNode;
  while(nextNode != mHead) {
    nextNode = nextNode->nextNode;
    delete nextNode->prevNode;
  }
  delete mHead;
}

bool LinkedList::loadFromFile(const string& filename) {
  ifstream fopen(filename);
  string fname,lname = "";
  unsigned int accNum = 0;
  double accBalance = 0;
  
  init();

  if(fopen) {
    while(fopen >> accNum >> fname >> lname >> accBalance) {
      Node *newNode = new Node(accNum, fname, lname, accBalance);
      addNode(newNode);
    }
    fopen.close();
    return true;
  }
  else {
    return false;
  }
}

bool LinkedList::saveToFile(const string& filename) {
  ofstream fsave(filename);
  
  if(fsave) {
    writeToStream(fsave);
    fsave.close();
    return true;
  }
  else {
    return false;
  }
}

void LinkedList::writeToStream(ostream& ostr) const {
  for(Node* current = mHead->nextNode; current != mHead; current = current->nextNode) {
    ostr << current->mAccNum << ' ' << current->mFname << ' '
    << current->mLname << ' ' << current->mAccBalance << endl;
    current = current->nextNode;
  }
}

bool LinkedList::findNodeAboveInstert(unsigned int accNum) {
  while(mCursor != mHead && mCursor->mAccNum > accNum) {
    mCursor = mCursor->prevNode;
  }
  while(mCursor->nextNode != mHead && mCursor->nextNode->mAccNum < accNum) {
    mCursor = mCursor->nextNode;
  }
  return mCursor->mAccNum == accNum;
}


void LinkedList::addNode(Node* addNode) {
  if(findNodeAboveInstert(addNode->mAccNum)) {
    mCursor->combineAccounts(addNode);
  }
  else {
    addNode->prevNode = mCursor;
    addNode->nextNode = mCursor->nextNode;
    mCursor->nextNode->prevNode = addNode;
    mCursor->nextNode = addNode;
  }
}

void LinkedList::deleteNode(Node* delNode) {
  delNode->prevNode->nextNode = delNode->nextNode;
  delNode->nextNode->prevNode = delNode->prevNode;
  delete delNode;
}


bool LinkedList::setCursor(unsigned int accNum) {
  return findNodeAboveInstert(accNum);
}

#endif /* LINKEDLIST_H */
