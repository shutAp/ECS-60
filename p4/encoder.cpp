//
//  encoder.cpp
//  p4
//
//  Created by Davey Jay Belliss on 5/7/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
#include "encoder.h"
#include "binaryHeap.cpp"
#include <fstream>
//#include "CPUTimer.h"
Encoder::Encoder()
{
} // Encoder()


Encoder::~Encoder()
{
} // ~Encoder()

void Encoder::encode(const unsigned  char *message, const int size,
                     unsigned  char *encodedMessage,
                     int *encodedSize)
{
  //  CPUTimer ct;
    int arr[256] = {0};
    for (int i = 0; i <= size - 1 ; i++)
        arr[message[i]]++;
    
    int position = 1;
    int* pos = &position;
    
    BinaryHeap<hNode*> heap(256);
    
    for (int i = 0; i <= 255; i++)
       
        if (arr[i] != 0)
        {
            hNode* node = new hNode(i, arr[i]);
            heap.insert(node);
        }//Inserts into heap
    
    hNode* leaves[256];//To place pointers to heapNodes
    hNode* first,*second, *root = NULL,* newNode = NULL;
    heap.deleteMin(first);
   
    while (!heap.isEmpty())
    {
        heap.deleteMin(second);
      
        if (first->isLeafNode())
            leaves[first->getValue()] = first;
      
        if (second->isLeafNode())
            leaves[second->getValue()] = second;
        
        newNode = new hNode(first, second);
        heap.insert(newNode);
        heap.deleteMin(first);
       
    }// Contructs tree
    
    root = newNode;
    // CPUTimer ct;
    root->print(encodedMessage, *pos);// prints tree PLR
   // cout << dec << "CPU time: " << ct.cur_CPUTime();

    
    encodedMessage[(*pos)++] = 'D';
    encodedMessage[(*pos)++] = 'O';
    encodedMessage[(*pos)++] = 'N';
    encodedMessage[(*pos)++] = 'E';


    int position2 = 0;
    int* pos2 = &position2; // how many bits
   //  CPUTimer ct;
    short bit = 0;
    short* bits = &bit;
    unsigned char* binary = new unsigned char[size * 10];
 //   int* binary = new int;


    
    

//   root->getCode2(leaves, binary, *pos2, *bits, *pos, encodedMessage, size, message);

    for (int i = 0; i <= size - 1; i++)
    {
  
        leaves[message[i]]->getCode(binary, *pos2, *bits, *pos, encodedMessage);

    }
 

    *binary <<= (7 - bit);
    
    encodedMessage[(*pos)++] = *binary;
    
    encodedMessage[0] = (char)bit;
    
    
    *encodedSize = *pos;

}  // encode()

