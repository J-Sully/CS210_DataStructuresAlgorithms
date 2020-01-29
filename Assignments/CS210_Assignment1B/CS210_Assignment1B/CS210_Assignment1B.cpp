/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 Goal: Write a program that will record information about employees
 and will compute their paychecks
 */

#include <iostream>
using namespace std;

#include "Cylinder.h"

int main(int argc, const char * argv[]) {
  Cylinder cylinder;
  cylinder.init(10, 20);
  cout << "The volume is: " << cylinder.getVolume();
  return 0;
}
