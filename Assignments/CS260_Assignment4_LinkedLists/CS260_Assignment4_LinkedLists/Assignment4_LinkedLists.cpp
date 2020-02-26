/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  main.cpp
//  CS260_Assignment4_LinkedLists
//
//  Created by Jessie Sully on 2/25/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "Node.h"
#include "LinkedList.h"
//#include "TransactionHandler.h"

static const string MASTER_FILENAME = "master.txt";
static const string TRANSACTION_FILENAME = "tran.txt";
static const string LOG_FILENAME = "log.txt";

bool parseOp(const string &op, unsigned int &accNum, string &fname,
             string &lname, double &transaction) {
  
  stringstream ss;
  ss.str(op);
  ss >> accNum >> fname >> lname >> transaction;
  return ss.fail();
}

bool logData(const string& filename, LinkedList* list, const int &opNumber, const string &op = "") {
  fstream fmanip(filename, ios::in | ios::app);
  stringstream ss;
  string test = "";
  bool success = false;
  
  if(fmanip) {
    success = true;
    if (!getline(fmanip,test)) {
      fmanip << "List at Start:" << endl;
      list->writeData(ss);
      fmanip << ss.str();
    }
    else {
      fmanip << "Update #" << opNumber << endl;
      fmanip << op << endl << endl;
      fmanip << "List after Update #" << opNumber << ':' << endl;
      list->writeData(ss);
      fmanip << ss.str();
    }
  }
  else {
    success = false;
  }
  return success;
}

bool updateAccounts(const string& filename) {
  ifstream fopenTrans(TRANSACTION_FILENAME);
  ofstream fLogData;
  unsigned int opNumber = 0;
  unsigned int accNum = 0;
  string fname, lname = "";
  bool success = false;
  
  if(fopenTrans) {
    
  }
  
  return success;
}







int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  
  LinkedList* list = new LinkedList(MASTER_FILENAME);
  Node* current = list->getHead();
  
  
  
  
  return 0;
  
  
  
}
