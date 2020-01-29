//
//  Employee.h
//  CS210_Assignment1A
//
//  Created by Jessie Sully on 1/28/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Employee_h
#define Employee_h

struct Employee {
  static const int NUM_WORKDAYS = 5;
  string mLName;
  double mHours[NUM_WORKDAYS];
  double mHourlyWage;
  double mWages;
};

#endif /* Employee_h */
