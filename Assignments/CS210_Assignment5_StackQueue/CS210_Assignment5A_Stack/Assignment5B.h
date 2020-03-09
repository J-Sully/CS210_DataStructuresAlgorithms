//
//  Assignment5B.h
//  CS210_Assignment5_StackQueue
//
//  Created by Donald Kjer on 3/8/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Assignment5B_h
#define Assignment5B_h


#include <iostream>
using namespace std;

#include "Node.h"
#include "Stack.h"

// runs assignment 5B
int runAssignment5B() {
  Stack<int> stack;
  
  while(1)
  {
    /* Menu */
#ifndef RUN_INPUT_TEST // Don't display menu in test mode
    cout <<"------------------------------------\n";
    cout <<" STACK IMPLEMENTATION PROGRAM \n";
    cout <<"------------------------------------\n";
    cout <<"1. Push\n";
    cout <<"2. Pop\n";
    cout <<"3. Size\n";
    cout <<"4. Print Stack\n";
    cout <<"5. Exit\n";
    cout <<"------------------------------------\n";
    cout <<"Enter your choice: ";
#endif /* RUN_INPUT_TEST */
    break;
    
  }
  return STATUS_OK;
}


#endif /* Assignment5B_h */
