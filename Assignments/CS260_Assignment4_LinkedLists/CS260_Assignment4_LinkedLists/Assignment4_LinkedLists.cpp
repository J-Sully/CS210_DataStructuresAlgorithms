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

#include "AccountManager.h"

static const string MASTER_FILENAME = "master.txt";
static const string TRANSACTION_FILENAME = "tran.txt";
static const string LOG_FILENAME = "log.txt";
static const string TEMP_NEWMASTER = "temp_master.txt";

bool parseOp(const string &op, unsigned int &accNum, string &fname,
             string &lname, double &transaction) {
  stringstream ss;
  ss.str(op);
  ss >> accNum >> fname >> lname >> transaction;
  return ss.fail();
}

/*
void updateAccounts(const string& transactionFilename, const string& logFilename, LinkedList &list) {
  ifstream fopenTrans(transactionFilename);
  ofstream flogUpdates(logFilename);
  unsigned int opNumber = 0;
  unsigned int accNum = 0;
  double transaction = 0;
  string fname, lname, op = "";
  Node* current = list.getHead();

  if(fopenTrans && flogUpdates) {
    flogUpdates << "List at Start:" << endl;
    list.writeToStream(flogUpdates);
    
    while(getline(fopenTrans,op)) {
      if(parseOp(op, accNum, fname, lname, transaction)) {
        opNumber++;
        if(list.getNode(accNum, current)) {
          if (!current->updateAccount(transaction)) {
            list.deleteNode(current);
            current = list.getHead();
          }
        }
        else {
          Node* addNode = new Node(accNum, fname, lname, transaction);
          if (current->mAccBalance > 0) {
            list.insertNode(addNode, current);
          }
        }
      }
      opNumber++;
      flogUpdates << "Update #" << opNumber << endl;
      flogUpdates << op << endl << endl;
      flogUpdates << "List after Update #" << opNumber << ':' << endl;
      list.writeToStream(flogUpdates);
    }
  }
}
 */

void RunTests() {
  LinkedList list;
  list.addNode(new Account(42, "John", "Smith", 5000));
  list.addNode(new Account(42, "John", "Smith", 100));
  list.addNode(new Account(2, "Jane", "Doe", 250));
  list.addNode(new Account(4, "Mark", "Marduk", 50));
  list.addNode(new Account(100, "Bill", "Briar", 10));
  list.addNode(new Account(4, "Mark", "Marduk", 300));
  
  for (LinkedList::Node* current = list.getFirst(); current != list.getHead(); current = current->getNext()) {
    Account* account = dynamic_cast<Account*>(current);
    cout << account->getAccountNum() << ' ' << account->getFirstName() << ' '
         << account->getLastName()   << ' ' << account->getBalance() << endl;
  }
}

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  RunTests();
  
  /*
  LinkedList list = LinkedList(MASTER_FILENAME);
  updateAccounts(TRANSACTION_FILENAME, LOG_FILENAME, list);
  saveToFile(TEMP_NEWMASTER, list);*/
  
  
  
  
  
  return 0;
  
  
  
}
