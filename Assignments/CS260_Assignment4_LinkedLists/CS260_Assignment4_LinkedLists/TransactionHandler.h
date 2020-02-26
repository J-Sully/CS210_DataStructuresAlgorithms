/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  TRANSACTIONHANDLER.h
//  CS260_Assignment4_LinkedLists
//
//  Created by Jessie Sully on 2/26/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <fstream>
using namespace std;

#include "LinkedList.h"

#ifndef TRANSACTIONHANDLER_H
#define TRANSACTIONHANDLER_H

class TransactionHandler {
public:
  TransactionHandler() {mList = new LinkedList;}
  TransactionHandler(LinkedList* list, const);
  
private:
  LinkedList* mList = nullptr;
  unsigned int opNumber = 0;
};

#endif /* TRANSACTIONHANDLER_H */
