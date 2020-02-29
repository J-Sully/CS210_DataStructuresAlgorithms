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

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

#include "LinkedList.h"

class Account : public LinkedList::Node {
public:
  Account(){};
  Account(unsigned int accNum, const string &fname, const string &lname, double accBalance)
  : Node(accNum), mFname(fname), mLname(lname), mAccBalance(accBalance) {}
  
  bool updateAccount(double transaction);
  bool combineAccounts(Node* addNode);

  virtual bool merge(Node*);
  
  const string& getFirstName() const { return mFname; }
  const string& getLastName() const { return mLname; }
  double getBalance() const { return mAccBalance; }
  unsigned int getAccountNum() const { return getKey(); }
  
private:
  string mFname = "";
  string mLname = "";
  double mAccBalance = 0;
};

bool Account::updateAccount(double transaction) {
  mAccBalance += transaction;
  return mAccBalance > 0;
}

/*virtual */
bool Account::merge(Node* otherNode) {
  Account* other = dynamic_cast<Account*>(otherNode);
  if (mLname != other->mLname || mFname != other->mFname) {
    cerr << "Warning: Transaction with mismatched account name:  '" << mFname << " " << mLname
         << "' != '" << other->mFname << " " << other->mLname << "'" << endl;
  }
  mAccBalance += other->mAccBalance;
  return mAccBalance > 0.000001; // TODO: Use a const for this near-zero value.
}

#endif /* ACCOUNT_H */
