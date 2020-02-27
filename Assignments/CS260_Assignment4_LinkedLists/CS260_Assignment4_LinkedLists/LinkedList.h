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
#include <sstream>
#include <fstream>
using namespace std;

#include "Node.h"


static const string TEMP_NEWMASTER = "temp_master.txt";

class LinkedList {
public:
  LinkedList() {}
  LinkedList(const string& filename) { loadData(filename); }
  ~LinkedList();
  
  Node* getHead() const { return mHead; }
  bool getNode(unsigned int accNum, Node* foundNode);
  void addNode(Node* addNode);
  void insertNode(Node* addNode, Node* closestNode);
  void deleteNode(Node* delNode);
  void writeData(stringstream&);
  
private:
  bool loadData(const string& filename);
  bool saveData(const string& filename);
  Node* mHead = new Node;
  
};

LinkedList::~LinkedList() {
  Node* nextNode = mHead->nextNode;
  saveData(TEMP_NEWMASTER);
  while(nextNode != mHead) {
    delete nextNode->prevNode;
    nextNode = nextNode->nextNode;
  }  
}

bool LinkedList::loadData(const string& filename) {
  ifstream fopen(filename);
  string fname,lname = "";
  unsigned int accNum = 0;
  double accBalance = 0;
  mHead = new Node;

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

bool LinkedList::saveData(const string& filename) {
  ofstream fsave(filename);
  stringstream ss;
  
  if(fsave) {
    writeData(ss);
    fsave << ss.str();
    fsave.close();
    return true;
  }
  else {
    return false;
  }
}

void LinkedList::writeData(stringstream& ss) {
  Node *current = mHead->nextNode;
  while (current != mHead) {
    ss << current->mAccNum << ' ' << current->mFname << ' '
    << current->mLname << ' ' << current->mAccBalance << endl;
  }
  ss << endl;
}

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
