/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  BST.H
//  CS210_Assignment8_BST
//
//  Created by Jessie Sully on 4/10/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

// static to keep track of instances to check memory leak. Keeps track of all variants.
static int sNumNodeObjects = 0;

// Binary Search Tree Node
struct BSTNode {
  // increments sNumNodeObjects for memory leak check
  BSTNode() { sNumNodeObjects++; }
  // increments sNumNodeObjects for memory leak check
  BSTNode(const int value) : mValue(value) { sNumNodeObjects++; }
  // decrements sNumNodeObjects for memory leak check
  ~BSTNode();
  
  // copies member variables
  BSTNode& operator=(const BSTNode& node);
  
  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const BSTNode* node);
  
  int mValue = 0;
  BSTNode* mLeft = nullptr;
  BSTNode* mRight = nullptr;
};

BSTNode::~BSTNode() {
  mLeft = nullptr;
  mRight = nullptr;
  sNumNodeObjects--;
}

BSTNode& BSTNode::operator=(const BSTNode &node) {
  mLeft = node.mLeft;
  mRight = node.mRight;
  mValue = node.mValue;
  return *this;
}

ostream& operator<<(ostream& ostr, const BSTNode* node) {
  ostr << node->mValue;
  return ostr;
}

// Binary Search Tree
class BST {
public:
  BST() {}
  // Runs clearTree to free allocated space
  ~BST();
  
  // returns mRoot
  BSTNode* getRoot() const { return mRoot; }
  // inserts a value into the Tree, does nothing if value is already in Tree
  void insert(int value);
  // removes a value from the Tree, does nothing if value is not found
  void remove(int value);
  // helper function to clear entire tree
  void clearTree();
  // helper function to clear subtree starting at cur
  void clearSubTree(BSTNode* cur);
  // returns pointer to node containing minimum value in tree - or nullptr if empty
  BSTNode* findMin() const;
  // returns pointer to node containing maximum value in tree - or nullptr if empty
  BSTNode* findMax() const;
  // prints out tree's contents in preOrder - uses private functions for recursive calls
  void preOrderTraversal() const;
  // prints out tree's contents in inOrder - uses private functions for recursive calls
  void inOrderTraversal() const;
  // prints out tree's contents in postOrder - uses private functions for recursive calls
  void postOrderTraversal() const;
  
private:
  BSTNode* mRoot = nullptr;
  // helper function to find the parent node for an insert or remove
  BSTNode* findParent(int value) const;
  // helper function to print preOrder recursively
  void preOrderTraversal(BSTNode* node) const;
  // helper function to print inOrder recursively
  void inOrderTraversal(BSTNode* node) const;
  // helper function to print postOrder recursively
  void postOrderTraversal(BSTNode* node) const;
};

BST::~BST() {
  clearTree();
}

void BST::clearTree() {
  clearSubTree(mRoot);
}

void BST::clearSubTree(BSTNode* cur) {
  if (cur == nullptr) return;
  clearSubTree(cur->mLeft);
  clearSubTree(cur->mRight);
  if (cur == mRoot) {
    mRoot = nullptr;
  }
  delete cur;
  return;
}

void BST::insert(int value) {
  BSTNode* branch = mRoot;
  if (mRoot == nullptr) {
    mRoot = new BSTNode(value);
    return;
  }
  branch = findParent(value);
  assert(branch != nullptr);
  if (branch->mValue > value && branch->mLeft == nullptr) {
    branch->mLeft = new BSTNode(value);
    return;
  }
  if (branch->mValue < value && branch->mRight == nullptr) {
    branch->mRight = new BSTNode(value);
    return;
  }
  return;
}

BSTNode* BST::findParent(int value) const {
  if (mRoot == nullptr) return mRoot;
  BSTNode* parent = mRoot;
  BSTNode* cur = mRoot;
  
  for(;;) {
    if (cur->mValue == value) return parent;
    parent = cur;
    if (cur->mValue < value) {
      if (cur->mRight == nullptr) {
        return parent;
      }
      cur = cur->mRight;
    }
    else if (cur->mValue > value) {
      if (cur->mLeft == nullptr) {
        return parent;
      }
      cur = cur->mLeft;
    }
  }
}

void BST::remove(int value) {
  BSTNode* parent = findParent(value);
  BSTNode* cur = nullptr;
  BSTNode** parentPtr;

  if (parent == nullptr) return;
  
  // get address of parent node's pointer to node to delete
  if (parent->mLeft != nullptr && parent->mLeft->mValue == value) {
    parentPtr = &parent->mLeft;
  }
  else if (parent->mRight != nullptr && parent->mRight->mValue == value) {
    parentPtr = &parent->mRight;
  }
  else if (mRoot->mValue == value) {
    parentPtr = &mRoot;
  }
  else {
    return;
  }
  cur = *parentPtr;

  // two children case
  if (cur->mLeft!= nullptr && cur->mRight != nullptr) {
    BSTNode* replaceNode = cur;
    parentPtr = &cur->mRight;
    cur = cur->mRight;
    while (cur->mLeft != nullptr) {
      parentPtr = &cur->mLeft;
      cur = cur->mLeft;
    }
    // swap values
    replaceNode->mValue = cur->mValue;
    *parentPtr = nullptr;
  }
  // one or zero children case
  else {
    if (cur->mLeft != nullptr) {
      *parentPtr = cur->mLeft;
    }
    else {
      *parentPtr = cur->mRight;
    }
  }
  delete cur;
  return;
}

BSTNode* BST::findMin() const {
  BSTNode* cur = mRoot;
  while(cur->mLeft != nullptr) {
    cur = cur->mLeft;
  }
  return cur;
}

BSTNode* BST::findMax() const {
  BSTNode* cur = mRoot;
  while(cur->mRight != nullptr) {
    cur = cur->mRight;
  }
  return cur;
}

void BST::preOrderTraversal() const {
  cout << "preOrderTraversal: ";
  preOrderTraversal(mRoot);
  cout << endl;
}

void BST::preOrderTraversal(BSTNode* node) const {
  if (node != NULL) {
    cout << node->mValue << " ";
    preOrderTraversal(node->mLeft);
    preOrderTraversal(node->mRight);
  }
}

void BST::inOrderTraversal() const {
  cout << "inOrderTraversal: ";
  inOrderTraversal(mRoot);
  cout << endl;
}

void BST::inOrderTraversal(BSTNode* node) const {
  if (node != NULL) {
    inOrderTraversal(node->mLeft);
    cout << node->mValue << " ";
    inOrderTraversal(node->mRight);
  }
}

void BST::postOrderTraversal() const {
  cout << "postOrderTraversal: ";
  postOrderTraversal(mRoot);
  cout << endl;
}

void BST::postOrderTraversal(BSTNode* node) const {
  if (node != NULL) {
    postOrderTraversal(node->mLeft);
    postOrderTraversal(node->mRight);
    cout << node->mValue << " ";
  }
}

#endif /* BST_H */
