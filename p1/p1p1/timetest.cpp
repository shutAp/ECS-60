//
//  main.cpp
//  timetest
//
//  Created by Vincent Yang and Davey Jay Belliss on 4/1/15.
//  Copyright (c) 2015 Vincent Yang and Davey Jay Belliss. All rights reserved.
//

#include <iostream>
#include "CursorList.h"
#include "dsexceptions.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "SkipList.h"
#include "StackLi.h"
#include "QueueAr.h"
#include "vector.h"
#include "CPUTimer.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

vector<CursorNode<int> > cursorSpace(250000);

int getChoice()
{
    cout << "Your choice >> ";
    int choice;
    cin >> choice;
    
    return choice;
}

void RunList( char* filename)
{
    List<int> list;
    ListItr<int> itr = list.zeroth();
    ifstream inf(filename);
    char command[10];
    inf.ignore(1000, '\n');
    char nums[10];
    while (inf >> command)
    {
        if (command[0] == 'i')
        {
            
            int i = 0;
            for (int j = 1; (command[j] != '\000'  ); j++, i++)
                nums[i] = command[j];
            nums[i] = '\0';
            int insert = atoi(nums);
            list.insert(insert, itr);
        }
        if (command[0] == 'd')
        {
            
            int i = 0;
            for (int j = 1; (command[j] != '\000'  ); j++, i++)
            {
                nums[i] = command[j];
            }
            nums[i] = '\0';
            int delet = atoi(nums);

            list.remove(delet);
        }
    }
}

void RunCursorList( char* filename)
{
    CursorList<int> clist(cursorSpace);
    CursorListItr<int> it = clist.zeroth();
    ifstream inf(filename, ios::in);
    char command[10];
    inf.ignore(1000, '\n');
    
    char nums[10];
    while (inf >> command)
    {
        if (command[0] == 'i')
        {
            int i = 0;
            for (int j = 1; (command[j] != '\000'  ); j++, i++)
            {
                nums[i] = command[j];
            }
            nums[i] = '\0';
            int insert = atoi(nums);
            clist.insert(insert, it);
        }
       
        if (command[0] == 'd')
        {
            int i = 0;
            for (int j = 1; (command[j] != '\000'  ); j++, i++)
                nums[i] = command[j];
            nums[i] = '\0';
            int delet = atoi(nums);
            clist.remove(delet);
        }
    }
}

void RunStackAr( char* filename)
{
    StackAr<int> stack(250000);
    ifstream inf(filename);
    char command[10];
    inf.ignore(1000, '\n');
    inf >> command;
    while (!inf.eof())
    {
        if (command[0] == 'i')
        {
            char nums[10];
            for (int j = 1,i = 0; ((command[j] != '\0')  ); j++, i++)
                nums[i] = command[j];
            int insert = atoi(nums);
            stack.push(insert);
        }
        if (command[0] == 'd')
            stack.pop();
        inf >> command;
    }
}

void RunStackLi( char* filename)
{
    StackLi<int>* stack= new StackLi<int>();
    ifstream inf(filename);
    char command[10];
    inf.ignore(1000, '\n');
    inf >> command;
    while (!inf.eof())
    {
        if (command[0] == 'i')
        {
            char nums[10];
            for (int j = 1,i = 0; ((command[j] != '\0')  ); j++, i++)
                nums[i] = command[j];
           
            int insert = atoi(nums);
            stack->push(insert);
        }
        if (command[0] == 'd')
            stack->pop();
    
        inf >> command;
    }
}

void RunQueueAr( char* filename)
{
    Queue<int>* queue= new Queue<int>(250000);
    ifstream inf(filename);
    char command[10];
    inf.ignore(1000, '\n');
    inf >> command;
    while (!inf.eof())
    {
        if (command[0] == 'i')
        {
            char nums[10];
            for (int j = 1,i = 0; ((command[j] != '\0')  ); j++, i++)
            {
                nums[i] = command[j];
            }
            int insert = atoi(nums);
            queue->enqueue(insert);
        }
        if (command[0] == 'd')
        {
            queue->dequeue();
        }
        inf >> command;
    }
}

void RunSkipList( char* filename)
{
    SkipList<int> slist(-1, 125000);
    ifstream inf(filename);
    char command[10];
    inf.ignore(1000, '\n');
    char nums[10];
    while (inf >> command)
    {
        if (command[0] == 'i')
        {
            int i = 0;
            for (int j = 1; (command[j] != '\000'  ); j++, i++)
                nums[i] = command[j];
            int insert = atoi(nums);
            nums[i] = '\0';
            slist.insert(insert);
        }
        
        if (command[0] == 'd')
        {
            int i = 0;
            for (int j = 1; (command[j] != '\000'  ); j++, i++)
                nums[i] = command[j];
            nums[i] = '\0';
            int delet = atoi(nums);
            
            slist.deleteNode(delet);
        }
    }
}

int main(int argc, const char * argv[]) 
{
    char filename[250];
    cout << "Filename >> ";
    cin >> filename;
    cout << endl;
    cout << "      ADT Menu" << endl;
    cout << "0. Quit" << endl;
    cout << "1.LinkedList" << endl;
    cout << "2.CursorList" << endl;
    cout << "3.StackAr" << endl;
    cout << "4.StackLi" << endl;
    cout << "5.RunQueueAr" << endl;
    cout << "6.SkipList" << endl;
    vector<CursorNode <int> > cursorSpace(250000);
    CPUTimer ct;
    int choice = 0;

    do
    {
        choice = getChoice();
        ct.reset();
        switch (choice)
        {
            case 0: break;
            case 1: RunList(filename); break;
            case 2: RunCursorList(filename); break;
            case 3: RunStackAr(filename); break;
            case 4: RunStackLi(filename); break;
            case 5: RunQueueAr(filename); break;
            case 6: RunSkipList(filename); break;
            default: cout << "Your choice is not between 1 and 6." << endl;
              cout << "Please try again. " << endl << endl; 
              break;
        }
        if (choice > -1 && choice < 7)
          cout << "CPU time: " << ct.cur_CPUTime() << endl << endl;
        if (choice == 0)
          return 0;
        cout << "      ADT Menu" << endl;
        cout << "0. Quit" << endl;
        cout << "1.LinkedList" << endl;
        cout << "2.CursorList" << endl;
        cout << "3.StackAr" << endl;
        cout << "4.StackLi" << endl;
        cout << "5.RunQueueAr" << endl;
        cout << "6.SkipList" << endl;
    } while (choice != 0);

    return 0;
}



