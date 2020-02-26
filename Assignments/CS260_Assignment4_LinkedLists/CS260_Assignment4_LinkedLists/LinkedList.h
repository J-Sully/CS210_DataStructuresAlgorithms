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



class LinkedList {
public:
  LinkedList(){}
  LinkedList(const string &filename) { loadData(filename); }
private:
  bool loadData(const string& filename);
  bool saveData(const string& filename);
  bool logData(const string& filename, const string &op);
  void writeData(stringstream&);
  Node* head = new Node;
  unsigned int opNumber = 0;
};

bool LinkedList::loadData(const string& filename) {
  ifstream fopen(filename);
  string fname,lname = "";
  unsigned int accNum = 0;
  int accBalance = 0;
  head = new Node;

  if(fopen) {
    while(fopen >> accNum >> fname >> lname >> accBalance) {
      Node *newNode = new Node(accNum, fname, lname, accBalance);
      if (head->nextNode == head) { //if empty list
        head->nextNode = newNode;
        head->prevNode = newNode;
        newNode->nextNode = head;
        newNode->prevNode = head;
      }
      else {
        head->prevNode->nextNode = newNode;
        newNode->prevNode = head->prevNode->nextNode;
        newNode->nextNode = head;
        head->prevNode->prevNode = newNode;
      }
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

bool LinkedList::logData(const string& filename, const string &op = "") {
  fstream fmanip(filename, ios::in | ios::app);
  stringstream ss;
  string test = "";
  bool success = false;
  
  if(fmanip) {
    success = true;
    if (!getline(fmanip,test)) {
      fmanip << "List at Start:" << endl;
      writeData(ss);
      fmanip << ss.str();
    }
    else {
      fmanip << "Update #" << opNumber << endl;
      fmanip << op << endl << endl;
      fmanip << "List after Update #" << opNumber << ':' << endl;
      writeData(ss);
      fmanip << ss.str();
    }
  }
  else {
    success = false;
  }
  return success;
}

void LinkedList::writeData(stringstream& ss) {
  Node *current = head->nextNode;
  while (current != head) {
    ss << current->mAccNum << ' ' << current->mFname << ' '
    << current->mLname << ' ' << current->mAccBalance << endl;
  }
  ss << endl;
}



#endif /* LINKEDLIST_H */
