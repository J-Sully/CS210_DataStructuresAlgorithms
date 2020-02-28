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
  bool getNode(unsigned int accNum, Node* foundNode); // returns F if unable to find node
  
  void addNode(Node* addNode);
  void insertNode(Node* addNode, Node* closestNode);
  void deleteNode(Node* delNode);
  
  void writeToStream(ostream&) const; // helper function to write out list data
  bool saveToFile(const string& filename); // returns F if unable to open file
  
private:
  bool findNodeAboveInstert(unsigned int accNum);
  bool loadFromFile(const string& filename); // returns F if unable to open file
  void init(); // helper function to initialize mHead
  Node* mHead = nullptr;
  Node* mCurrent = nullptr;
  
};

void LinkedList::init() {
  mHead = new Node;
  mCurrent = mHead;
}

LinkedList::~LinkedList() {
  Node* nextNode = mHead->nextNode;
  while(nextNode != mHead) {
    delete nextNode->prevNode;
    nextNode = nextNode->nextNode;
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
  if (mCurrent->mAccNum > accNum) {
    while(mCurrent->mAccNum <= accNum || mCurrent != mHead) {
      if (mCurrent->mAccNum == accNum) return true;
      mCurrent = mCurrent->prevNode;
    }
  }
  else if (mCurrent->mAccNum < accNum) {
    while(mCurrent->mAccNum > accNum || mCurrent->nextNode == mHead) {
      mCurrent = mCurrent->nextNode;
      if (mCurrent->mAccNum == accNum) {
        return true;
      }
    }
  }
  return false;
}


void LinkedList::insertNode(Node* addNode) {
  if(findNodeAboveInstert(addNode->mAccNum)) {
    mCurrent->combineAccounts(addNode);
    return;
  }
  else {
    addNode->prevNode = mCurrent;
    addNode->nextNode = mCurrent->nextNode;
    mCurrent->nextNode->prevNode = addNode;
    mCurrent->nextNode = addNode;
  }
}

/*
void LinkedList::addNode(Node* addNode) {
  bool found = false;
  Node* current = mHead->nextNode;
  if (mHead->nextNode == mHead) { // empty list
    mHead->nextNode = addNode;
    mHead->prevNode = addNode;
    addNode->nextNode = mHead;
    addNode->prevNode = mHead;
  }
  else {
    while (current->nextNode != mHead) {
      if (current->mAccNum < addNode->mAccNum
          && current->nextNode->mAccNum > addNode->mAccNum) {
        addNode->nextNode = current->nextNode;
        addNode->prevNode = current;
        current->nextNode->prevNode = addNode;
        current->nextNode = addNode;
        found = true;
        break;
      }
      if (!found) {
        current->nextNode = addNode;
        mHead->prevNode = addNode;
        addNode->nextNode = mHead;
        addNode->prevNode = current;
        
      }
    }
  }
}


void LinkedList::insertNode(Node* addNode, Node* closestNode) {
  if (closestNode->mAccNum > addNode->mAccNum) {
    addNode->nextNode = closestNode;
    addNode->prevNode = closestNode->prevNode;
    addNode->prevNode->nextNode = addNode;
    closestNode->prevNode = addNode;
  }
  else if(closestNode->mAccNum < addNode->mAccNum) {
    addNode->prevNode = closestNode;
    addNode->nextNode = closestNode->nextNode;
    closestNode->nextNode = addNode;
    addNode->nextNode->prevNode = addNode;
  }
}
*/

void LinkedList::deleteNode(Node* delNode) {
  delNode->prevNode->nextNode = delNode->nextNode;
  delNode->nextNode->prevNode = delNode->prevNode;
  delete delNode;
}

bool LinkedList::getNode(unsigned int accNum, Node* current) {
  bool success = false;
  if (current->mAccNum == accNum) {
    success = true;
  }
  else if (current->mAccNum < accNum) {
    while(current != mHead) {
      if(current->mAccNum == accNum) {
        success = true;
        break;
      }
      else if(current->mAccNum > accNum) {
        success = false;
        break;
      }
      current = current->nextNode;
    }
  }
  else if (current->mAccNum > accNum) {
    while(current != mHead) {
      if(current->mAccNum == accNum) {
        success = true;
        break;
      }
      else if (current->mAccNum < accNum) {
        success = false;
        break;
      }
      current = current->prevNode;
    }
  }
  return success;
}
#endif /* LINKEDLIST_H */
