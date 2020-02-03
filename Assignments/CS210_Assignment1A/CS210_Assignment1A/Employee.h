//  Programmer: Jessica Sullivan
//  Programmer's ID: 1282151
//  Employee.h
//  CS210_Assignment1A
//
//  Created by Jessie Sully on 1/28/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//


#ifndef Employee_h
#define Employee_h

#include <string>
using namespace std;

static const int NUM_WORKDAYS = 5;
static const char* DAYS[] = {"Monday", "Tuesday", "Wednesday",
                             "Thursday", "Friday"};

struct Employee {
  string mLName;
  double mHours[NUM_WORKDAYS];
  double mHourlyWage;
  double mWages;
};

#endif /* Employee_h */
