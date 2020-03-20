/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  HannoiTower.h
//  CS210_Assignment6_Recursion
//
//  Created by Jessie Sully on 3/19/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef HannoiTower_h
#define HannoiTower_h

struct HanoiTower {
  HanoiTower(int numDisks);
  Stack<unsigned int> mFirst;
  Stack<unsigned int> mSecond;
  Stack<unsigned int> mThird;
  void printStacks();
  void moveStack(Stack<unsigned int> &source, Stack<unsigned int> &destination, Stack<unsigned int> &temp, unsigned int numDisks);
};

HanoiTower::HanoiTower(int numDisks) : mFirst("A"), mSecond("B"), mThird("C") {
  for (int i = numDisks; i > 0; i--) {
    mFirst.push(i);
  }
}

void HanoiTower::printStacks() {
#ifdef VERBOSE
  mFirst.display(cout);
  mSecond.display(cout);
  mThird.display(cout);
#endif // VERBOSE
}

void HanoiTower::moveStack(Stack<unsigned int> &source, Stack<unsigned int> &destination, Stack<unsigned int> &temp, unsigned int numDisks) {
  if (numDisks == 0) {
    return;
  }
  else {
    for (int k = 1; k <= numDisks; k++) {
      moveStack(destination, temp, source, k - 1);
      destination.push(source.pop());
      cout << "Move Disk " << k << " from post " << source.getName() << " to post " << destination.getName() << endl;
      printStacks();
      moveStack(temp, destination, source, k - 1);
    }
  }
}
#endif /* HannoiTower_h */
