#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

bool LeafNode::isFull() const
{
  if (count >= leafSize)
    return true;
  return false;
}

int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  return 0;
} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  if (!isFull())
  {
    int i;
    for (i = count; i > 0 && values[i-1] > value; i--)
    {
      values[i] = values[i-1];
    }
    values[i] = value;
    count++;
    return NULL;
  }
  //insert new number to self
  int toPush;
  if (value < getMinimum())
  {
    toPush = value;
  }
  else
  {
    toPush = getMinimum();
  }
  if ((LeafNode*) leftSibling != NULL && !((LeafNode *)leftSibling) -> isFull())
  {
    //if it gets here, push left.
    if (value < values[0]) //if the smallest current value < value
        //then push the smallest value in the array to the left.
      //else push value over. shift everything accordingly.
      leftSibling->insert(value);
    else
    {
      leftSibling->insert(values[0]);
      for (int i = 0; i < count; i++)//count or count-1?
      {
        values[i] = values[i+1];
      }
      count--;
      insert(value);
    }
    return NULL;
  }
  else if ((LeafNode*) rightSibling != NULL && !((LeafNode *) rightSibling) -> isFull())
  {
    if (value > values[count-1]) //if the biggest current value > value
      //then push the biggest value in the array to the right.
      //else push value over. shift everything accordingly.
      rightSibling->insert(value);
    else
    {
      rightSibling->insert(values[count-1]);
      count--;
      insert(value);
    }
    return NULL;
  }
  LeafNode *newNode = new LeafNode(leafSize, parent, NULL, NULL);
  if (count % 2 == 0)
  {
    for (int i = (count/2); i < count; i++)
    {
      newNode -> insert(values[i]);
    }
    count = (count/2);
  }
  else
  {
    for (int i = (count+1)/2; i < count; i++)
    {
      newNode -> insert(values[i]);
    }
    count = (count+1)/2;
  }
  //take care of newest
  if (value > values[count-1])
  {
    newNode -> insert(value);
  }
  else
  {
    newNode -> insert(values[count-1]);
    count--;
    insert(value);
  }
  return newNode;
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


