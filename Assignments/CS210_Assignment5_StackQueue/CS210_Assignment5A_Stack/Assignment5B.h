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

#include "Queue.h"

template <typename T>
void displayQueue(const Queue<T>& queue);
string prepMenu();

// runs assignment 5B
int runAssignment5B() {
  int option, data;
  Queue<int> queue;
  string menu = prepMenu();
  cout << menu << endl;
  cin >> option;
  while (option != 7)
  {
    
    switch (option)
    {
      case 1:
        cout << "\nEnter data to enqueue (-99 to stop): ";
        cin >> data;
        while ( data != -99)
        {
          queue.enqueue(data);
          cout << "\nEnter data to enqueue (-99 to stop): ";
          cin >> data;
        }
        
        
        break;
        
      case 2:
        if (queue.isEmpty()) {
          cout << "Queue is empty."<< endl;
        }
        else {
          data = queue.dequeue();
          cout << "Data => " << data << endl;
        }
        
        break;
        
      case 3:
    
        if (queue.isEmpty())
          cout << "Queue is empty."<< endl;
        else
          cout << "Queue size => "<< queue.getSize() << endl;
        
        break;
        
      case 4:
        if (queue.isEmpty()) {
          cout << "Queue is empty." << endl;
        }
        else {
          data = queue.getRear();
          cout << "Rear => " << data << endl;
        }
        
        break;
        
      case 5:
        if (queue.isEmpty()) {
          cout <<"Queue is empty."<< endl;
        }
        else {
          data = queue.getFront();
          cout <<"Front => " << data << endl;
        }
        
        break;
        
      case 6:
        displayQueue(queue);
        break;
        
      default:
        cout <<"Invalid choice, please input number between (0-5).\n";
        break;
    }
    
    cout <<"\n\n";
    cout << menu<< endl;
    cin >> option;
  }
  return STATUS_OK;
}

string prepMenu() {
  string menu = "";
  
#ifndef RUN_INPUT_TEST // Don't display menu in test mode
  menu+= " \n-------------------------------------------------------------------\n";
  menu+= "1.Enqueue 2.Dequeue 3.Size 4.Get Rear 5.Get Front 6.Display 7.Exit\n";
  menu+= "----------------------------------------------------------------------\n";
  menu+= "Select an option: ";
#endif
  return menu;
}

// Function to display elements in queue
template <typename T>
void displayQueue(const Queue<T>& queue) {
  if (!queue.isEmpty()) {
    queue.display(cout);
    cout << endl;
  }
  
  else
    cout << "queue is empty" << endl << endl;
}

#endif /* Assignment5B_h */
