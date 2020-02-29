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
#include <cfloat>
using namespace std;

#include "Node.h"

class LinkedList {
public:
  LinkedList() { init(); }
  LinkedList(const string& filename) { init(); loadFromFile(filename); }
  ~LinkedList();
  
  Node* getHead() const { return mHead; }
  
  void addNode(Node* addNode);
  void deleteNode(Node* delNode);
  
  void writeToStream(ostream&) const; // helper function to write out list data
  bool saveToFile(const string& filename); // returns F if unable to open file
  bool loadFromFile(const string& filename); // returns F if unable to open file
  
  void updateAccount(long accNum, const string &fname, const string &lname, double transaction);
  
private:
  bool findNodeAboveInsert(long accNum); // returns true if exact match accNum found
  void init(); // shared/common constructor code
  Node* mHead = nullptr;
  // "global" pointer
  Node* mCursor = nullptr;
};

// shared/common constructor code
void LinkedList::init() {
  mHead = new Node;
  mCursor = mHead;
}

LinkedList::~LinkedList() {
  Node* nextNode = mHead->nextNode;
  while (nextNode != mHead) {
    nextNode = nextNode->nextNode;
    delete nextNode->prevNode;
  }
  delete mHead;
}

bool LinkedList::loadFromFile(const string& filename) {
  ifstream fopen(filename);
  string fname,lname = "";
  long accNum = 0;
  double accBalance = 0;

  if (fopen) {
    while (fopen >> accNum >> fname >> lname >> accBalance) {
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
  
  if (fsave) {
    writeToStream(fsave);
    fsave.close();
    return true;
  }
  else {
    return false;
  }
}

void LinkedList::writeToStream(ostream& ostr) const {
  for (Node* current = mHead->nextNode; current != mHead; current = current->nextNode) {
    ostr << current->mAccNum << ' ' << current->mFname << ' '
    << current->mLname << ' ' << current->mAccBalance << endl;
  }
}

bool LinkedList::findNodeAboveInsert(long accNum) {
  // move upwards list until found or head
  while (mCursor != mHead && mCursor->mAccNum > accNum) {
    mCursor = mCursor->prevNode;
  }
  // move downwards list until found or head
  while (mCursor->nextNode != mHead && mCursor->nextNode->mAccNum <= accNum) {
    mCursor = mCursor->nextNode;
  }
  return mCursor != mHead && mCursor->mAccNum == accNum;
}


void LinkedList::addNode(Node* addNode) {
  // move cursor - if match combine
  if (findNodeAboveInsert(addNode->mAccNum)) {
    mCursor->combineAccounts(addNode);
    delete addNode;
  }
  // else make new account at cursor position
  else {
    addNode->prevNode = mCursor;
    addNode->nextNode = mCursor->nextNode;
    mCursor->nextNode->prevNode = addNode;
    mCursor->nextNode = addNode;
  }
}

void LinkedList::deleteNode(Node* delNode) {
  mCursor = mHead; // move cursor in case it points at delNode
  delete delNode; // unlinking in destructor
}

void LinkedList::updateAccount(long accNum, const string &fname, const string &lname, double transaction) {
  // move cursor - if found update account
  if(findNodeAboveInsert(accNum)) {
    // if updated account balance <= 0 delete
    if(!mCursor->updateAccount(transaction)) {
      deleteNode(mCursor);
    }
  }
  // else add new account only if transaction > 0
  else {
    if (transaction >= DBL_EPSILON) {
      addNode(new Node(accNum, fname, lname, transaction));
    }
  }
}

#endif /* LINKEDLIST_H */
