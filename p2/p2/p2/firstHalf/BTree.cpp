#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;

BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const int value)
{
  //cout << "value in BTree:insert is " << value << endl;
  BTreeNode* temp = root->insert(value);
  if (temp != NULL) //if it has to split
  {
    InternalNode* newRoot = new InternalNode(internalSize, leafSize, NULL, NULL, NULL);
    ((InternalNode*)newRoot)->insert(root, temp);
    root -> setParent(newRoot);
    temp -> setParent(newRoot);
    root = newRoot;
  }
  else if (temp == NULL)
  {
    //cout << "interna node returns null in btree.cpp" << endl;
    //cout << "INTERNAL NODE INSERT HERE" << endl;
  }
  // students must write this
} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);

  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()
