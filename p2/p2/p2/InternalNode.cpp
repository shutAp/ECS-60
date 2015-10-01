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
int InternalNode::getCount() const
{
  return count;
}

BTreeNode* InternalNode::pushRight()
{
  if (rightSibling != NULL && !((InternalNode*)rightSibling)->isFull())
  {
    ((InternalNode*)rightSibling)->insert(children[count-1]);
    count--;
  }
  return NULL;
}
int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  return 0;
} // InternalNode::getMinimum()

bool InternalNode::isFull() const
{
  if (count < internalSize)
    return false;
  return true;
}

void InternalNode::updateKeys()
{
  for (int i = 0; i < count; i++)
  {
    keys[i] = children[i]->getMinimum();
  }
}
InternalNode* InternalNode::insert(int value) //to be used for normal insertion
{
  updateSiblings();
  int i;
  for (i = 1; i < count && keys[i] < value; i++){}
    //iterate to appropriate spot to insert.
  i--;
  BTreeNode *temp = (children[i])-> insert(value);
  keys[i] = children[i]->getMinimum();
  if (i-1 >= 0)
    keys[i-1] = children[i-1]->getMinimum();
  if (i+1 < count)
    keys[i+1] = children[i+1]->getMinimum();
  if (temp != NULL) //move size check here?
  {
    if (count < internalSize)
      insert(temp);//inserting a new child from LeafNode
    else
    {
      //this must return an internal node.
      if (leftSibling != NULL && !((InternalNode*) leftSibling) -> isFull())
      {
        //if it gets here, push left.
        if (temp->getMinimum() < getMinimum()) //if the smallest current value < value
          //then push the smallest value in the array to the left.
          //else push value over. shift everything accordingly.
        {
          ((InternalNode*) leftSibling)->insert(temp);
          //cout << "pushing left siling"
        }
        else
        {
          ((InternalNode*)leftSibling)->insert(children[0]);
          for (int i = 0; i < count; i++)//count or count-1?
          {
            keys[i] = keys[i+1];
            children[i] = children[i+1];
          }
          count--;
          insert(temp);
        }
        updateKeys();
        return NULL;
        
      }
      else if (rightSibling != NULL && !((InternalNode *) rightSibling) -> isFull())
      {
        
        if (value > keys[count-1]) //if the biggest current value > value
          //then push the biggest value in the array to the right.
          //else push value over. shift everything accordingly.
          ((InternalNode*)rightSibling)->insert(temp);
        else
        {
          ((InternalNode*)rightSibling)->insert(children[count-1]);
          count--;
          insert(temp);
        }
        updateKeys();
        return NULL;
      }
      InternalNode *newNode = new InternalNode(internalSize, leafSize, parent, this, NULL);
      setRightSibling(newNode);
      if (count % 2 == 0)
      {
        for (int i = (count/2); i < count; i++)
        {
          newNode -> insert(children[i]);
        }
        count = (count/2);
      }
      else
      {
        for (int i = (count+1)/2; i < count; i++)
        {
          newNode -> insert(children[i]);
        }
        count = (count+1)/2;
      }
      //take care of newest
      if (temp->getMinimum() > keys[count-1])
      {
        newNode -> insert(temp);
      }
      else
      {
        newNode -> insert(children[count-1]);
        count--;
        insert(temp);
      }
      cout << "returning new node in internal node insert" << endl;
      updateKeys();
      return newNode;
    }
  }
  updateKeys();
  return NULL;
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2) //done
{ // Node must be the root, and node1
  // students must write this
  children[0] = oldRoot;
  children[1] = node2;
  count = 2;
  keys[0] = children[0]->getMinimum();
  keys[1] = children[1]->getMinimum();
  updateKeys();
} // InternalNode::insert()

void InternalNode::updateSiblings()
{
  for (int i = 0; i < count-1; i++)
  {
    children[i]->setRightSibling(children[i+1]);
  }
  for (int i = count-1; i > 0; i--)
  {
    children[i]->setLeftSibling(children[i-1]);
  }
  if (leftSibling != NULL)
  {
    children[0]->setLeftSibling(((InternalNode*)leftSibling)->children[leftSibling->getCount()-1]);
  }
  if (rightSibling != NULL)
  {
    children[count-1]->setRightSibling(((InternalNode*)rightSibling)->children[0]);
  }
  updateKeys();
}

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
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
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;
  updateKeys();
  cout << "Internal: ";
  for (i = 0; i < count; i++)
  {
    cout << keys[i] << ' ';
  }
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


