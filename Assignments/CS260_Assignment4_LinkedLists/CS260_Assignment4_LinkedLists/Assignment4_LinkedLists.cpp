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

/*
bool parseOp(const string &op, unsigned int &accNum, string &fname,
             string &lname, double &transaction) {
  stringstream ss;
  ss.str(op);
  ss >> accNum >> fname >> lname >> transaction;
  return ss.fail();
}

void updateAccounts(const string& transactionFilename, const string& logFilename, LinkedList &list) {
  ifstream fopenTrans(transactionFilename);
  ofstream flogUpdates(logFilename);
  unsigned int opNumber = 0;
  unsigned int accNum = 0;
  double transaction = 0;
  string fname, lname, op = "";

  if(fopenTrans && flogUpdates) {
    flogUpdates << "List at Start:" << endl;
    list.writeToStream(flogUpdates);
    
    while(getline(fopenTrans,op)) {
      if(parseOp(op, accNum, fname, lname, transaction)) {
        opNumber++;
        if(list.setCurrent(accNum)) {
          if (!current->updateAccount(transaction)) {
            list.deleteNode(current);
            current = list.getHead();
          }
        }
        else {
          Node* addNode = new Node(accNum, fname, lname, transaction);
          if (current->mAccBalance > 0) {
            list.addNode(addNode);
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
int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  stringstream ss;
  
  LinkedList list(TEMP_NEWMASTER);
  list.writeToStream(cout);
  list.addNode(new Node(5, "a", "b", 60));
  list.writeToStream(cout);
  list.addNode(new Node(12, "a", "d", 60));
  list.writeToStream(cout);


  /*
  list.addNode(new Node(10, "a", "b", 20));
  list.writeToStream(cout);

  
  list.addNode(new Node(5, "c", "d", 50));
  list.writeToStream(cout);

  
  list.addNode(new Node(15, "c", "d", 50));
  list.writeToStream(cout);

  
  list.addNode(new Node(1, "c", "d", 50));
  list.writeToStream(cout);
  
  list.addNode(new Node(12, "c", "d", 50));
  list.writeToStream(cout);
  
  list.saveToFile(TEMP_NEWMASTER);
  
*/
  
  
  
  return 0;
  
  
  
}
