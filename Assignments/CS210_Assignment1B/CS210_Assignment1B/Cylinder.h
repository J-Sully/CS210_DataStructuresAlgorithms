//
//  Cylinder.h
//  CS210_Assignment1B
//
//  Created by Jessie Sully on 1/28/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Cylinder_h
#define Cylinder_h

#include <cmath>

class Cylinder {
private:
  int radius;
  int height;
public:
  void init(int, int);
  double getVolume() {return M_PI * radius * radius * height;}
};

void Cylinder::init(int r, int h) {
  radius = r;
  height = h;
}

#endif /* Cylinder_h */
