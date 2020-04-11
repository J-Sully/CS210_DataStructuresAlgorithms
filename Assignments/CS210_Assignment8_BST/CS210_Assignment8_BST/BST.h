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
  //BSTNode* mRoot = nullptr;
public:
  BSTNode* mRoot = nullptr;
  BST (){}
  ~BST();
  
  void insert(int value);
  void clearTree(BSTNode *node);
  BSTNode* findParent(int value) const;

//  void remove(int value);
  /*
  /// ------------------------------------------
  BSTNode* finMin() const
  {
  }
  /// ------------------------------------------
  BSTNode* finMax() const
  {
  }
  /// ------------------------------------------
  void preOrderTraversal() const
  {
    cout << "preOrderTraversal: ";
    preOrderTraversal(root);
    cout << endl;
  }
  void preOrderTraversal(BSTNode* node) const
  {
    if (node != NULL) {
      cout << node->value << " ";
      preOrderTraversal(node->left);
      preOrderTraversal(node->right);
    }
  }
  /// ------------------------------------------
  void inOrderTraversal() const
  {
    cout << "inOrderTraversal: ";
    inOrderTraversal(root);
    cout << endl;
  }
  void inOrderTraversal(BSTNode* node) const
  {
    if (node != NULL) {
      inOrderTraversal(node->left);
      cout << node->value << " ";
      inOrderTraversal(node->right);
    }
  }
  /// ------------------------------------------
  void postOrderTraversal() const
  {
    cout << "postOrderTraversal: ";
    postOrderTraversal(root);
    cout << endl;
  }
  void postOrderTraversal(BSTNode* node) const
  {
    if (node != NULL) {
      postOrderTraversal(node->left);
      postOrderTraversal(node->right);
      cout << node->value << " ";
    }
  }
  */
};

BST::~BST() {
  clearTree(mRoot);
}

void BST::clearTree(BSTNode* cur) {
  if (cur != nullptr) {
    clearTree(cur->mLeft);
    clearTree(cur->mRight);
    delete cur;
  }
  return;
}

void BST::insert(int value) {
  BSTNode* branch = mRoot;
  if (mRoot == nullptr) {
    mRoot = new BSTNode(value);
    return;
  }
  branch = findParent(value);
  if (branch->mValue > value) {
    branch->mLeft = new BSTNode(value);
    return;
  }
  if (branch->mValue < value) {
    branch->mRight = new BSTNode(value);
    return;
  }
  return;
  /*
  if (branch->mValue > value)
  while (branch != nullptr) {
    if (branch->mValue == value) return;
    if (branch->mValue < value) {
      if (branch->mRight == nullptr) {
        branch->mRight = new BSTNode(value);
        return;
      }
      branch = branch->mRight;
    }
    if (branch->mValue > value) {
      if (branch->mLeft == nullptr) {
        branch->mLeft = new BSTNode(value);
        return;
      }
      branch = branch->mLeft;
    }
  }
  return;
   */
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
    if (cur->mValue > value) {
      if (cur->mLeft == nullptr) {
        return parent;
      }
      cur = cur->mLeft;
    }
  }
}
/*
void BST::remove(int value) {
  BSTNode* parent = nullptr;
  BSTNode* cur = nullptr;
  //bool oneChild = false, twoChild = false, nochild = false;
  if (mRoot == nullptr) return;
  

}
 */

#endif /* BST_H */
