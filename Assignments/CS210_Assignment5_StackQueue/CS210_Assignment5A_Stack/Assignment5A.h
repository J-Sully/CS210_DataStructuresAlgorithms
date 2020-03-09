//
//  Assignment5A.h
//  CS210_Assignment5_StackQueue
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Assignment5A_h
#define Assignment5A_h

#include <iostream>
using namespace std;

#include "Node.h"
#include "Stack.h"

typedef int NTYPE; // Type to use for Stack Nodes.

template <typename T>
void display(const Stack<T>& stack);

// runs assignment 5A
int runAssignment5A() {
  int choice;
  NTYPE data;
  Stack<NTYPE> stack;
  
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
    
    cin >>choice;
    
    switch(choice)
    {
      case 1:
        cout <<"Enter data to push into stack: ";
        cin >> data;
        
        // Push element to stack
        stack.push(data);
        break;
        
      case 2:
        if (stack.isEmpty()) {
          cerr << "Error, stack is empty." << endl;
        }
        else {
          data = stack.pop();
          cout <<"Data => " << data << endl;
        }
        break;
        
      case 3:
        cout <<"Stack size: " << stack.getSize() << endl;
        break;
      
      case 4:
        display(stack);
        break;
        
        
      case 5:
        cout <<"Exiting from app.\n";
        exit(0);
        break;
        
      default:
        cout <<"Invalid choice, please try again.\n";
    }
    
    cout <<"\n\n";
  }
  return STATUS_OK;
}

// Function to display elements in stack
template <typename T>
void display(const Stack<T>& stack) {
  if (!stack.isEmpty()) {
    stack.display(cout);
    cout << endl;
  }
  
  else
    cout << "stack is empty" << endl << endl;
}


#endif /* Assignment5A_h */
