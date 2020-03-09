/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  main.cpp
//  CS210_Assignment5_QueueQueue
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <iostream>

#include "Node.h"
#include "Queue.h"

bool testMemoryLeak();
template <typename T>
void display(const Queue<T>& queue);
void runProgram();
string prepMenu();

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  runProgram();
  testMemoryLeak();
  
  return 0;
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}


// Function to display elements in queue
template <typename T>
void display(const Queue<T>& queue) {
  if (!queue.isEmpty()) {
    queue.display(cout);
    cout << endl;
  }
  
  else
    cout << "queue is empty" << endl << endl;
}

void runProgram() {
  int option, data;
  Queue<int> queue;
  string menu = prepMenu();
  cout << menu << endl;
  cin >> option;
  while (option !=7)
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
          cout << "Queue is empty."<< endl;
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
        display(queue);
        break;
        
      default:
        cout <<"Invalid choice, please input number between (0-5).\n";
        break;
    }
    
    cout <<"\n\n";
    cout << menu<< endl;
    cin >> option;
  }
}

string prepMenu() {
  
  string menu = "";
  
  menu+= " \n-------------------------------------------------------------------\n";
  menu+= "1.Enqueue 2.Dequeue 3.Size 4.Get Rear 5.Get Front 6.Display 7.Exit\n";
  menu+= "----------------------------------------------------------------------\n";
  menu+= "Select an option: ";
  return menu;
}
