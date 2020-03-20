/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  main.cpp
//  CS210_Assignment6_Recursion
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <iostream>

#define VERBOSE

#include "Node.h"
#include "Stack.h"
#include "HannoiTower.h"

void runProgram();
bool testMemoryLeak();

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
  int numDisks = 0;
  cout << "TOWERS of Hanoi\nEnter a number of disks to play. I'll give necessary moves." << endl;
  cin >> numDisks;
  HanoiTower tower(numDisks);
  tower.printStacks();
  tower.moveStack(tower.mFirst, tower.mSecond, tower.mThird, numDisks);
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}




