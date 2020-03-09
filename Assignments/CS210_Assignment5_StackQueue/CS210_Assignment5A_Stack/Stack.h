//
//  Stack.h
//  CS210_Assignment5_StackQueue
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include "Deque.h"

template <typename T>
class Stack {
public:
  Stack() {}
  void push(const T& element) { mDeque.push_front(element); }
  T pop() { return mDeque.pop_front_val(); }
  bool isEmpty() const { return mDeque.isEmpty(); }
  void display(ostream& output) const { mDeque.display(output); }
  int getSize() const { return mDeque.getSize(); }

private:
  Deque<T> mDeque;
};

#endif /* Stack_h */
