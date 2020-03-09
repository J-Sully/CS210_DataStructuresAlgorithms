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
  void push(T element);
  T pop();
  bool isEmpty() const { return mDeque.isEmpty(); }
  void display(ostream& output) const { mDeque.display(output); }
  int getSize() const { return mDeque.getSize(); }

private:
  Deque<T> mDeque;
};

template <typename T>
void Stack<T>::push(T element) {
  mDeque.push_front(element);
}

//Function to pop element from top of stack.
template <typename T>
T Stack<T>::pop() {
  if (mDeque.isEmpty()) {
    throw out_of_range("Stack<T>::pop() : empty stack");
  }
  
  T element = mDeque.front();
  mDeque.pop_front();
  return element;
}


#endif /* Stack_h */
