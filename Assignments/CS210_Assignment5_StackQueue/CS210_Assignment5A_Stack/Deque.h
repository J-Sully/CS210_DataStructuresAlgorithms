//
//  Deque.h
//  CS210_Assignment5_StackQueue
//

#ifndef Deque_h
#define Deque_h

template <typename T>
class Deque {
public:
  Deque() {}
  ~Deque();
  bool isEmpty() const { return mHead == nullptr; }
  void display(ostream& output) const;
  int getSize() const { return mSize; }
  
  void push_front(const T& element);
  void pop_front();
  void push_back(const T& element);
  void pop_back();
  
  T& front() { return mHead->getObject(); }
  const T& front() const { return mHead->getObject(); }
  T& back() { return mTail->getObject(); }
  const T& back() const { return mTail->getObject(); }

private:
  Node<T>* mHead = nullptr;
  Node<T>* mTail = nullptr;
  int mSize = 0;
};

template <typename T>
Deque<T>::~Deque() {
  while (mHead != nullptr) {
    mHead = mHead->getNext();
    delete mHead->getPrev();
  }
}

template <typename T>
void Deque<T>::push_front(const T& element) {
  Node<T>* newNode = new Node<T>(element);
  if (mHead == nullptr) {
    mHead = newNode;
    mTail = newNode;
  }
  else {
    newNode->linkNext(mHead);
    mHead = newNode;
  }
  mSize++;
}

template <typename T>
void Deque<T>::push_back(const T& element) {
  Node<T>* newNode = new Node<T>(element);
  if (mTail == nullptr) {
    mHead = newNode;
    mTail = newNode;
  }
  else {
    newNode->linkPrev(mTail);
    mTail = newNode;
  }
  mSize++;
}

// Function to pop first element from deque
template <typename T>
void Deque<T>::pop_front() {
  if (isEmpty()) {
    throw out_of_range("Deque<T>::pop_front : Empty deque");
  }
  
  if (mSize == 1) {
    delete mHead;
    mHead = nullptr;
    mTail = nullptr;
  }
  else {
    mHead = mHead->getNext();
    delete mHead->getPrev();
  }
  mSize--;
}

// Function to pop last element from deque
template <typename T>
void Deque<T>::pop_back() {
  if (isEmpty()) {
    throw out_of_range("Deque<T>::pop_back : Empty deque");
  }
  
  if (mSize == 1) {
    delete mTail;
    mHead = nullptr;
    mTail = nullptr;
  }
  else {
    mTail = mTail->getPrev();
    delete mTail->getNext();
  }
  mSize--;
}

template<typename T>
void Deque<T>::display(ostream &output) const {
  for(const Node<T>* cursor = mHead; cursor != nullptr; cursor = cursor->getNext()) {
    output << cursor << endl;
  }
}


#endif /* Deque_h */
