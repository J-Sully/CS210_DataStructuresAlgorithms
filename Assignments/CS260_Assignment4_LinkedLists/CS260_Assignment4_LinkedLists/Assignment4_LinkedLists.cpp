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

static const string MASTER_FILENAME = "master.txt";
static const string TRANSACTION_FILENAME = "tran.txt";
static const string LOG_FILENAME = "log.txt";
static const string NEWMASTER = "newmaster.txt";

enum StatusCode {
  STATUS_OK = 0,
  ERR_MEMLEAK,
  ERR_FAILOPENMASTER,
  ERR_FAILOPENLOGTRANS,
  ERR_FAILOPENNEWMASTER
};

// parses an op line into accNum, fname, lname, and transaction amount
bool parseOp(const string &op, long &accNum, string &fname,
             string &lname, double &transaction);
// takes transaction lines from a file, updates account, and logs changes - returns false if fail to open file
bool applyTransactions(const string& transactionFilename,
                       const string& logFilename, LinkedList &list);
// function to run application
int runApplication();
// returns true if memory leak
bool testMemoryLeak();
void runTests();


int main(int argc, const char * argv[]) {
  
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  //runTests();
  
  int result = runApplication();
  
  if (testMemoryLeak()) return ERR_MEMLEAK;
  
  return result;
}

// parses an op line into accNum, fname, lname, and transaction amount
bool parseOp(const string &op, long &accNum, string &fname,
             string &lname, double &transaction) {
  
  stringstream ss;
  ss.str(op);
  ss >> accNum >> fname >> lname >> transaction;
  
  return !ss.fail();
}

// takes transaction lines from a file, updates account, and logs changes - returns false if fail to open file
bool applyTransactions(const string& transactionFilename,
                       const string& logFilename, LinkedList &list) {
  
  ifstream fopenTrans(transactionFilename);
  ofstream flogUpdates(logFilename);
  
  unsigned int opNumber = 0;
  long accNum = 0;
  double transaction = 0;
  
  string fname, lname, op = "";
  
  //checks if files opened properly or write error message
  if (fopenTrans && flogUpdates) {
    
    flogUpdates << "List At Start:" << endl;
    list.writeToStream(flogUpdates);
    
    while (getline(fopenTrans,op)) {
      
      opNumber++;
      
      // check if line parsed correctly or write error message
      if (parseOp(op, accNum, fname, lname, transaction)) {
        list.updateAccount(accNum, fname, lname, transaction);
      }
      else {
        stringstream ss;
        ss << "Error running operation " << opNumber << ": " << op << endl;
        flogUpdates << ss.str();
        cerr << ss.str();
        continue;
      }
      flogUpdates << endl << "Update #" << opNumber << endl;
      flogUpdates << op << endl << endl;
      flogUpdates << "List After Update #" << opNumber << ':' << endl;
      list.writeToStream(flogUpdates);
    }
  }
  else {
    cerr << "Error: could not open file(s)" << endl;
    return false;
  }
  return true;
}

// function to run application
int runApplication() {
  LinkedList list;
  if (!list.loadFromFile(MASTER_FILENAME)) {
    return ERR_FAILOPENMASTER;
  }
  if (!applyTransactions(TRANSACTION_FILENAME, LOG_FILENAME, list)) {
    return ERR_FAILOPENLOGTRANS;
  }
  if (!list.saveToFile(NEWMASTER)) {
    return ERR_FAILOPENNEWMASTER;
  }
  return 0; // can add errors for previous functions later
}

// returns true if memory leak
bool testMemoryLeak() {
  if (Node::sNumObjects != 0) {
    cerr << "Num leaked nodes: " << Node::sNumObjects << endl;
    return true;
  }
  return false;
}

void runTests() {
  LinkedList list;
  list.writeToStream(cout);
  list.addNode(new Node(5, "a", "b", 60));
  list.writeToStream(cout);
  list.addNode(new Node(12, "a", "d", 60));
  list.writeToStream(cout);
}
