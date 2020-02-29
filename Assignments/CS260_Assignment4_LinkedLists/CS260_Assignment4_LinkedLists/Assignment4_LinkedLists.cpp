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
#include <fstream>
using namespace std;

#include "AccountManager.h"

static const string MASTER_FILENAME = "master.txt";
static const string TRANSACTION_FILENAME = "tran.txt";
static const string LOG_FILENAME = "log.txt";
static const string TEMP_NEWMASTER = "temp_master.txt";

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

enum StatusCode {
  STATUS_OK = 0,
  ERR_LOG_FILE,
  ERR_TRANS_FILE,
  ERR_INPUT_ACCOUNTS,
  ERR_OUTPUT_ACCOUNTS,
  ERR_MEMORY_LEAK
};

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

int UpdateAccounts(const string& inputAccountsFile, const  string& outputAccountsFile, const string& transactionsFile, const string& logFile) {
  ofstream log(logFile);
  if (!log) {
    cerr << "Unable to open log file: " << logFile << endl;
    return ERR_LOG_FILE;
  }
  //ostream& log(cout); // debug; log to stdout for now instead of log file
  
  AccountManager manager;
  if (!manager.loadFromFile(inputAccountsFile)) {
    cerr << "Error while loading accounts file: " << inputAccountsFile << endl;
    return ERR_INPUT_ACCOUNTS;
  }
  log << "List At Start:" << endl;
  manager.writeToStream(log);
  log << endl;
  if (!manager.applyTransactions(transactionsFile, log)) {
    cerr << "Error while processing transaction in file: " << transactionsFile << endl;
    return ERR_TRANS_FILE;
  }
  if (!manager.saveToFile(outputAccountsFile)) {
    cerr << "Error while saving accounts to file: " << outputAccountsFile << endl;
    return ERR_OUTPUT_ACCOUNTS;
  }
  return STATUS_OK;
}

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  //RunTests();
  
  string sourceFile(__FILE__);
  string sourceDir;
  size_t filePos = sourceFile.rfind(PATH_SEPARATOR);
  if (filePos != string::npos) {
    sourceDir = sourceFile.erase(filePos + 1, string::npos);
  }
  string inputAccountsFile(sourceDir + MASTER_FILENAME);
  string outputAccountsFile(sourceDir + TEMP_NEWMASTER);
  string transactionsFile(sourceDir + TRANSACTION_FILENAME);
  string logFile(sourceDir + LOG_FILENAME);
  int result = UpdateAccounts(inputAccountsFile, outputAccountsFile, transactionsFile, logFile);
  // Sanity check that no node leaked
  if (LinkedList::Node::sNumObjects != 0) {
    cout << "Leaked nodes: " << LinkedList::Node::sNumObjects << endl;
    result = ERR_MEMORY_LEAK;
  }
  
  return result;
  
  
  
}
