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
    //StackLi< Queue<int> > stack();
    StackLi< Queue<short> > stack = *new StackLi< Queue<short> >();
    Queue<short> currentQueue = *new Queue<short>(250000);
    int counter = 0;

    if (!inf.is_open())
    {
        cout << endl;
        return 0;
    }

    while (!inf.eof())
    {    
        inf >> in;
        counter++;
        if (!inf.eof())
            currentQueue.enqueue(in);

        if (counter == atoi(argv[2]))
        {
            counter = 0;
            stack.push(currentQueue);
            currentQueue = *new Queue<short>();
        }
    }
    stack.push(currentQueue);
    if (stack.isEmpty())
    {
        cout << "the stack is empty" << endl;
    }
    if (currentQueue.isEmpty())
    {
        cout << "The queue is empty" << endl;
    }
    while(!stack.isEmpty())
    {
        //unload each queue
        currentQueue = stack.topAndPop();
        int c = 1;
        while (!currentQueue.isEmpty())
        {
            in = currentQueue.getFront();
            cout << in << " ";
            currentQueue.dequeue();
            if (c == atoi(argv[2]))
                return 0;
        }
    }

    cout << endl;
    return 0;
}
