/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  Account.h
//  CS260_Assignment4_LinkedLists
//
//  Created by Jessie Sully on 2/25/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "Account.h"
#include "LinkedList.h"

class AccountManager {
public:
  AccountManager() {}
  AccountManager(const string& filename) { loadFromFile(filename); }
  
  bool loadFromFile(const string& filename); // returns F if unable to open file
  void writeToStream(ostream&) const; // helper function to write out list data
  bool saveToFile(const string& filename); // returns F if unable to open file
  bool applyTransactions(const string& transactionsFile,  ostream& log);
  
private:
  bool parseOp(const string &op, unsigned int &accNum, string &fname, string &lname, double &transaction);
  
  LinkedList mAccounts;
};

bool AccountManager::loadFromFile(const string& filename) {
  ifstream fopen(filename);
  string fname,lname = "";
  unsigned int accNum = 0;
  double accBalance = 0;

  if (fopen) {
    while(fopen >> accNum >> fname >> lname >> accBalance) {
      Account* account = new Account(accNum, fname, lname, accBalance);
      mAccounts.addNode(account);
    }
    fopen.close();
    return true;
  }
  return false;
  
}

bool AccountManager::saveToFile(const string& filename) {
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

void AccountManager::writeToStream(ostream& ostr) const {
  for (LinkedList::Node* current = mAccounts.getFirst(); current != mAccounts.getHead(); current = current->getNext()) {
    Account* account = dynamic_cast<Account*>(current);
    ostr << account->getAccountNum() << ' ' << account->getFirstName() << ' '
         << account->getLastName()   << ' ' << account->getBalance() << endl;
  }
}

bool AccountManager::parseOp(const string &line, unsigned int &accNum, string &fname,
             string &lname, double &transaction) {
  stringstream ss;
  ss.str(line);
  ss >> accNum >> fname >> lname >> transaction;
  return !ss.fail();
}

bool AccountManager::applyTransactions(const string& transactionsFile,  ostream& log) {
  ifstream ftrans(transactionsFile);
  string fname, lname, line;
  unsigned int accNum;
  double amount;
  int opNumber = 0;
  Account* account;
  
  if (ftrans) {
    while (getline(ftrans,line)) {
      if (parseOp(line, accNum, fname, lname, amount)) {
        opNumber++;
        log << "Update #" << opNumber << endl;
        log << line << endl << endl;
        account = dynamic_cast<Account*>(mAccounts.addNode(new Account(accNum, fname, lname, amount)));
        if (account->getBalance() <= 0.000001) { // TODO: Use a const for this near-zero value
          mAccounts.removeNode(account);
        }
        log << "List After Update #" << opNumber << endl;
        writeToStream(log);
        log << endl;
      }
    }
    
    return true;
  }
  else {
    return false;
  }
}

#endif /* ACCOUNTMANAGER_H */
