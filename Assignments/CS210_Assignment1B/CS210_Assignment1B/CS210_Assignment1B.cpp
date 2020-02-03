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
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  Cylinder cylinder;
  cylinder.init(10, 20);
  
  cout << "The volume is: " << cylinder.getVolume() << endl;
  
  return 0;
}
