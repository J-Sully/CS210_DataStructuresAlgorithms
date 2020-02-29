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
static const string TEMP_NEWMASTER = "temp_master.txt";


bool parseOp(const string &op, unsigned int &accNum, string &fname,
             string &lname, double &transaction) {
  stringstream ss;
  ss.str(op);
  ss >> accNum >> fname >> lname >> transaction;
  return !ss.fail();
}

void updateAccounts(const string& transactionFilename,
                    const string& logFilename, LinkedList &list) {
  ifstream fopenTrans(transactionFilename);
  ofstream flogUpdates(logFilename);
  unsigned int opNumber = 0;
  unsigned int accNum = 0;
  double transaction = 0;
  string fname, lname, op = "";

  if(fopenTrans && flogUpdates) {
    flogUpdates << "List At Start:" << endl;
    list.writeToStream(flogUpdates);
    
    while(getline(fopenTrans,op)) {
      if(parseOp(op, accNum, fname, lname, transaction)) {
        list.updateAccount(accNum, fname, lname, transaction);
      }
      opNumber++;
      flogUpdates << endl << "Update #" << opNumber << endl;
      flogUpdates << op << endl << endl;
      flogUpdates << "List After Update #" << opNumber << ':' << endl;
      list.writeToStream(flogUpdates);
    }
  }
  else {
    cerr << "Error: could not open file(s)" << endl;
  }
}

void Test() {
  LinkedList list(TEMP_NEWMASTER);
  list.writeToStream(cout);
  list.addNode(new Node(5, "a", "b", 60));
  list.writeToStream(cout);
  list.addNode(new Node(12, "a", "d", 60));
  list.writeToStream(cout);
}

void runApplication() {
  LinkedList list(MASTER_FILENAME);
  updateAccounts(TRANSACTION_FILENAME, LOG_FILENAME, list);
  list.saveToFile(TEMP_NEWMASTER);
}

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  runApplication();
  
  if (Node::sNumObjects != 0) {
    cerr << "Num leaked nodes: " << Node::sNumObjects << endl;
    return 1;
  }

  
  
  
  return 0;
  
  
  
}
