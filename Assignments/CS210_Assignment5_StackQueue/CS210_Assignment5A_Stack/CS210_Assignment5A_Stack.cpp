//
//  main.cpp
//  CS210_Assignment5_StackQueue
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <iostream>

#include "Node.h"
#include "Stack.h"

template<>
const int Stack<int>::EMPTY_STACK_INTELEMENT = -1;

bool testMemoryLeak();
template <typename T>
void push(T element, Stack<T> &stack);
template <typename T>
void display(const Stack<T>& stack);
void runProgram();

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  runProgram();
  testMemoryLeak();
  
  return 0;
}

// runs program
void runProgram() {
  int choice, data;
  Stack<int> stack;
  
  while(1)
  {
    /* Menu */
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
        data = stack.pop();
        
        /// If stack is not empty
        if (data != Stack<int>::EMPTY_STACK_INTELEMENT)
          cout <<"Data => " << data << endl;
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
}

// returns true if memory leak
bool testMemoryLeak() {
  if (Node<int>::sNumObjects != 0) {
    cerr << "Num leaked nodes: " << Node<int>::sNumObjects << endl;
    return true;
  }
  return false;
}


//Function to push a new element in stack.
template <typename T>
void push(T element, Stack<T> &stack) {
  stack.push(element);
  cout <<"Data pushed to stack.\n";
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
