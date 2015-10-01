// Created by Vincent Yang for ECS 60 p1/p2

#include <iostream>
#include <stdlib.h>
#include "StackLi.h"
#include "QueueAr.h"
#include <fstream>

using namespace std;

int main(int argc, const char * argv[])
{
  //hold a stack of queues.
  
  ifstream inf(argv[1]);
  short in;
  StackLi< Queue<short> > stack = *new StackLi< Queue<short> >();
  Queue<short> currentQueue = *new Queue<short>(atoi(argv[2]));
  if (!inf.is_open())
  {
    cout << endl;
    return 0;
  }
  while (!inf.eof())
  {    
    inf >> in;
    
    if (!inf.eof())
    {
      currentQueue.enqueue(in);
    }
    if (currentQueue.isFull())
    {
      stack.push(currentQueue);
      currentQueue = *new Queue<short>(atoi(argv[2]));
    }
  }
  stack.push(currentQueue);
  while(!stack.isEmpty())
  {
    //unload each queue
    currentQueue = stack.topAndPop();
    while (!currentQueue.isEmpty())
    {
      in = currentQueue.getFront();
      cout << in << " ";
      currentQueue.dequeue();
    }
  }
  
  cout << endl;
  return 0;
}
