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
  
private:
  LinkedList mAccounts;
};

bool AccountManager::loadFromFile(const string& filename) {
  ifstream fopen(filename);
  string fname,lname = "";
  unsigned int accNum = 0;
  double accBalance = 0;

  if(fopen) {
    while(fopen >> accNum >> fname >> lname >> accBalance) {
      Account* account = new Account(accNum, fname, lname, accBalance);
      mAccounts.addNode(account);
    }
    fopen.close();
    return true;
  }
  else {
    return false;
  }
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

#endif /* ACCOUNTMANAGER_H */
