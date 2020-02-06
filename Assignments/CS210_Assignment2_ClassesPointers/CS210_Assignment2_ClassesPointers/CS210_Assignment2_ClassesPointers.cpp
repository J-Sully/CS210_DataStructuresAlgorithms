/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 Goal: Write a program that will record information about employees
 and will compute their paychecks
 */
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "DynamicStringArray.h"

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  DynamicStringArray names;
  // List of names
  names.addEntry("Frank");
  names.addEntry("Wiggum");
  names.addEntry("Nahasapeemapetilon");
  names.addEntry("Quimby");
  names.addEntry("Flanders");
  
  // Output list
  cout << "List of names:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  // Add and remove some names
  names.addEntry("Spuckler");
  cout << "After adding a name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.deleteEntry("Nahasapeemapetilon");
  cout << "After removing a name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.deleteEntry("Skinner");
  cout << "After removing a name that isn't on the list:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.addEntry("Muntz");
  cout << "After adding another name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  // Remove all of the names by repeatedly deleting the last one
  while (names.getSize() > 0) {
    names.deleteEntry(names.getEntry(names.getSize() - 1));
  }
  
  cout << "After removing all of the names:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.addEntry("Olivia");
  cout << "After adding a name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  cout << "Testing copy constructor" << endl;
  DynamicStringArray names2(names);
  // Remove Olivia from names
  names.deleteEntry("Olivia");
  cout << "Copied names:" << endl;
  for (int i = 0; i < names2.getSize(); i++)
    cout << names2.getEntry(i) << endl;
  cout << endl;
  
  cout << "Testing assignment" << endl;
  DynamicStringArray names3 = names2;
  // Remove Olivia from names2
  names2.deleteEntry("Olivia");
  cout << "Copied names:" << endl;
  for (int i = 0; i < names3.getSize(); i++)
    cout << names3.getEntry(i) << endl;
  cout << endl;
  
  cout << "Enter a character to exit." << endl;
  char wait;
  cin >> wait;
  return 0;
}


/*
// ensures that number input is valid - no whitespace, letters, or negatives
bool validateInput(const string &input, double &value) {
  stringstream ss;
  ss.str(input);
  ss >> value;
  return value >= 0 && !ss.fail();
}

// gets info from users and calls validateInput on numbers inputed
void initialize(Employee *employees) {
  string input, lName = "";
  double hours = -1, wages = -1;
  stringstream ss;
  bool valid = false;
  
  // go through each of the employees to get info
  for (int i = 0; i < NUM_EMPLOYEES; i++) {
    cout << endl << "Enter Last Name of Employee " << i + 1 << ": ";
    getline(cin, lName);
    employees[i].mLName = lName; // no error catching required
    
    // go through each day of the work week
    for (int j = 0; j < NUM_WORKDAYS; j++) {
      do {
        cout << endl << "Enter hours worked on: " << DAYS[j] << " : ";
        getline(cin, input);
        
        //valid makes sure input is valid for hours
        valid = validateInput(input, hours) && hours <= 24;
        if (!valid) {
          cerr << endl << "Error, " << input << " is an invalid input."
          << endl;
          hours = -1;
        }
        input = "";
      } while (!valid);
      
      employees[i].mHours[j] = hours;
      valid = false;
    }
    
    do {
      cout << endl << "Enter hourly wage : $";
      getline(cin, input);
      
      //valid makes sure wages are valid
      valid = validateInput(input, wages);
      if (!valid) {
        cerr << endl << "Error, " << input << " is an invalid input."
        << endl;
        wages = -1;
        input = "";
      }
    } while (!valid);
    
    employees[i].mHourlyWage = wages;
  }
}

// computes wages of employees based on total hours worked and wage rate
void compute(Employee &employee) {
  double totalHours = 0;
  
  for (int i = 0; i < NUM_WORKDAYS; i++) {
    totalHours += employee.mHours[i];
  }
  
  employee.mWages = totalHours > NUM_HOURS_FOR_OVERTIME
  ? NUM_HOURS_FOR_OVERTIME * employee.mHourlyWage
  + (totalHours - NUM_HOURS_FOR_OVERTIME)
  * employee.mHourlyWage * PERCENT_WAGE_OT
  : totalHours * employee.mHourlyWage;
}

//prints out relevant information about employees.
//Passing by value according to the instructions instead of by reference
void result(Employee employee) {
  cout << endl << "Employee Name: " << employee.mLName << endl;
  cout << "Total Wages: $" << fixed << setprecision(2)
  << employee.mWages << endl;
}
*/
