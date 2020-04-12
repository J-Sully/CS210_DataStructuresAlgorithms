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

struct BSTNode /// BinarySearchTreeNode
{
  BSTNode() { sNumNodeObjects++; }
  BSTNode(const int value) : mValue(value) { sNumNodeObjects++; }
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

class BST // BinarySearchTree
{
private:
  BSTNode* mRoot = nullptr;
  
  void inOrderTraversal(BSTNode* node) const;
  void preOrderTraversal(BSTNode* node) const;
  void postOrderTraversal(BSTNode* node) const;
public:
  BST (){}
  ~BST();
  
  BSTNode* getRoot() { return mRoot; }
  void insert(int value);
  void remove(int value);
  void clearTree(BSTNode *node);
  BSTNode* findParent(int value) const;
  BSTNode* findMin() const;
  BSTNode* findMax() const;
  void preOrderTraversal() const;
  void inOrderTraversal() const;
  void postOrderTraversal() const;
};

BST::~BST() {
  clearTree(mRoot);
}

void BST::clearTree(BSTNode* cur) {
  if (cur == nullptr) return;
  clearTree(cur->mLeft);
  clearTree(cur->mRight);
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
  BSTNode* parent = nullptr;
  BSTNode* cur = mRoot;
  BSTNode* deleteNode = nullptr;
  bool twoChild = false;
  bool leftSide = false;
  
  if (mRoot == nullptr) return;
  
  parent = findParent(value);
  
  if (mRoot->mValue != value) {
    if (parent->mLeft != nullptr && parent->mLeft->mValue == value) {
      cur = parent->mLeft;
      leftSide = true;
    }
    else if (parent->mRight != nullptr && parent->mRight->mValue == value){
      cur = parent->mRight;
    }
  }
  twoChild = cur->mLeft!= nullptr && cur->mRight != nullptr;
  if (twoChild) {
    deleteNode = cur;
    parent = cur;
    cur = cur->mRight;
    while (cur->mLeft != nullptr) {
      parent = cur;
      cur = cur->mLeft;
    }
    deleteNode->mValue = cur->mValue;
    if (parent->mLeft == cur) {
      parent->mLeft = nullptr;
    }
    else if (parent->mRight == cur){
      parent->mRight = nullptr;
    }
  }
  else {
    if (cur == mRoot) {
      if (cur->mLeft != nullptr) {
        mRoot = cur->mLeft;
      }
      else {
        mRoot = cur->mRight;
      }
    }
    else if (leftSide) {
      if (cur->mLeft != nullptr) {
        parent->mLeft = cur->mLeft;
      }
      else {
        parent->mRight = cur->mRight;
      }
    } else {
      if (cur->mLeft != nullptr) {
        parent->mRight = cur->mLeft;
      }
      else {
        parent->mRight = cur->mRight;
      }
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

void BST::preOrderTraversal() const
{
  cout << "preOrderTraversal: ";
  preOrderTraversal(mRoot);
  cout << endl;
}
void BST::preOrderTraversal(BSTNode* node) const
{
  if (node != NULL) {
    cout << node->mValue << " ";
    preOrderTraversal(node->mLeft);
    preOrderTraversal(node->mRight);
  }
}

void BST::inOrderTraversal() const
{
  cout << "inOrderTraversal: ";
  inOrderTraversal(mRoot);
  cout << endl;
}
void BST::inOrderTraversal(BSTNode* node) const
{
  if (node != NULL) {
    inOrderTraversal(node->mLeft);
    cout << node->mValue << " ";
    inOrderTraversal(node->mRight);
  }
}

void BST::postOrderTraversal() const
{
  cout << "postOrderTraversal: ";
  postOrderTraversal(mRoot);
  cout << endl;
}
void BST::postOrderTraversal(BSTNode* node) const
{
  if (node != NULL) {
    postOrderTraversal(node->mLeft);
    postOrderTraversal(node->mRight);
    cout << node->mValue << " ";
  }
}


#endif /* BST_H */
