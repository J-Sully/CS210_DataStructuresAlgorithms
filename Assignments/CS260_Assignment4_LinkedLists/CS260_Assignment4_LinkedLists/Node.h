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
using namespace std;

struct Node {
public:
  Node(){sNumObjects++;};
  Node(unsigned int accNum, const string &fname, const string &lname,
       double accBalance)
  : mFname(fname), mLname(lname), mAccNum(accNum), mAccBalance(accBalance) {sNumObjects++;}
  ~Node();
  
  bool updateAccount(double transaction); //returns false if balance <= 0
  bool combineAccounts(Node* addNode); //returns false if balance <= 0
  
  static int sNumObjects;
  
  string mFname = "";
  string mLname = "";
  unsigned int mAccNum = 0;
  double mAccBalance = 0;
  Node* nextNode = this;
  Node* prevNode = this;
};

//static - keeps track of number of instances to check for memory leak
int Node::sNumObjects = 0;

Node::~Node() {
  nextNode->prevNode = prevNode;
  prevNode->nextNode = nextNode;
  prevNode = this;
  nextNode = this;
  sNumObjects--;
}

bool Node::updateAccount(double transaction) {
  mAccBalance += transaction;
  return mAccBalance > 0;
}

bool Node::combineAccounts(Node* addNode) {
  if (mFname != addNode->mFname || mLname != addNode->mLname) {
    cerr << "Differing names on accounts - defaulting name to: " << mFname
         << ' ' << mLname << endl;
  }
  return updateAccount(addNode->mAccBalance);
}

#endif /* NODE_H */
