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
  void moveDisk(unsigned int diskNum, Stack<unsigned int> &source, Stack<unsigned int> &destination, Stack<unsigned int> &temp);
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

void HanoiTower::moveDisk(unsigned int diskNum, Stack<unsigned int> &source, Stack<unsigned int> &destination, Stack<unsigned int> &temp) {
  if (diskNum == 0) {
    return;
  }
  moveDisk(diskNum - 1, source, temp, destination);
  destination.push(source.pop());
  cout << "Move Disk " << diskNum << " from post " << source.getName() << " to post " << destination.getName() << endl;
  printStacks();
  moveDisk(diskNum - 1, temp, destination, source);
}
#endif /* HannoiTower_h */
