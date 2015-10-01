#include <iostream>
#include "InternalNode.h"
using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{
  // students must write this
  int i;
  //cout << "internal size is " << internalSize << endl;
  for (i = 1; i < count && keys[i] < value; i++)
  {
    //cout << "key number " << i << " is " << keys[i] << endl;
  } //iterate to appropriate spot to insert.
  //cout << "i is " << i << endl;
  //cout << "count is " << count << endl;
  //if (i == count)
    i--;
  BTreeNode *temp = (children[i])-> insert(value);
  keys[i] = children[i]->getMinimum();
  if (i-1 >= 0)
    keys[i-1] = children[i-1]->getMinimum();
  if (i+1 < count)
    keys[i+1] = children[i+1]->getMinimum();
  if (temp != NULL)
  {
    insert(temp);
    cout << "SPLITTING IN INTERNAL NNODE INSERT REACHED, TAKE CARE OF IT!" << endl;
  }
  if (temp == NULL)
  {
    //cout << "temp is null" << endl;
  }
  return NULL;
  
//  return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  // students must write this
  //cout << "Internal Node: ";
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = children[0]->getMinimum();
  keys[1] = children[1]->getMinimum();
  //cout << keys[0] << ", " << keys[1] << endl;
  count=2;
  for (int i = 0; i < count-1; i++)
  {
    children[i]->setRightSibling(children[i+1]);
  }
  for (int i = count-1; i > 0; i--)
  {
    children[i]->setLeftSibling(children[i-1]);
  }
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  if (count < internalSize) //if not full
  {
    //cout << "in method" << endl;
    int i;
    for (i = count; i > 0 && keys[i-1] > newNode->getMinimum(); i--)
    {
      children[i] = children[i-1];
      keys[i] = keys[i-1];
    }
    keys[i] = newNode->getMinimum();
    children[i] = newNode;
    count++;
    for (int i = 0; i < count-1; i++)
    {
      children[i]->setRightSibling(children[i+1]);
    }
    for (int i = count-1; i > 0; i--)
    {
      children[i]->setLeftSibling(children[i-1]);
    }
  }
  else //if full
  {
    
  }
  

  
  // students may write this
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


