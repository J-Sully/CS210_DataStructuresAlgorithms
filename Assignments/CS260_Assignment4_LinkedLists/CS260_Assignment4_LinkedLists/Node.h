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
  Node(){};
  Node(unsigned int accNum, const string &fname, const string &lname, double accBalance)
  : mFname(fname), mLname(lname), mAccNum(accNum), mAccBalance(accBalance) {}
  
  string mFname = "";
  string mLname = "";
  unsigned int mAccNum = 0;
  double mAccBalance = 0;
  Node* nextNode = this;
  Node* prevNode = this;
};

#endif /* NODE_H */
