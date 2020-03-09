//
//  Queue.h
//  CS210_Assignment5_StackQueue
//
//  Created by Donald Kjer on 3/8/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include "Deque.h"

template <typename T>
class Queue {
public:
  Queue() {}
  void enqueue(const T& element) { mDeque.push_back(element); }
  T dequeue() { return mDeque.pop_front_val(); }
  bool isEmpty() const { return mDeque.isEmpty(); }
  void display(ostream& output) const { mDeque.display(output); }
  int getSize() const { return mDeque.getSize(); }
  const T& getRear() const { return mDeque.back(); }
  const T& getFront() const { return mDeque.front(); }
  
private:
  Deque<T> mDeque;

};

#endif /* Queue_h */
