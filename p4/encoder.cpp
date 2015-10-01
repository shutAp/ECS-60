//
//  encoder.cpp
//  p4
//
//  Created by Davey Jay Belliss on 5/7/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
#include "encoder.h"
#include "binaryHeap.cpp"
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
    unsigned char* binary = new unsigned  char[size * 10];

    for (int i = 0; i <= size - 1; i++)
    {
    //   leaves[message[i]]->getCode(binary, *pos2);
        leaves[message[i]]->getCode2(binary, *pos2, *bits, *pos, encodedMessage);

    }
    
    *binary <<= (7 - bit);
    
    encodedMessage[(*pos)++] = *binary;

  /*
    for ( int i = 0; i <= (*pos2) ;i=i+8) //reads in packets of 8 bits
    {

        encodedMessage[(*pos)++] = getBits(binary[i], binary[i+1], binary[i+2], binary[i+3], binary[i+4], binary[i+5], binary[i+6], binary[i+7]);
    }
    
    */
    
    //REMAINDER
  
    
    encodedMessage[0] = (char)bit;
    // encodedMessage[0] = (char)((*pos2) % 8);
    
    
    
    *encodedSize = *pos;

}  // encode()


unsigned char Encoder::getBits(short a, short b, short c, short d, short e, short f, short g, short h)
{
    unsigned char bit = 0;
    bit |= a;
    bit <<= 1;
    bit |= b;
    bit <<= 1;
    bit |= c;
    bit <<= 1;
    bit |= d;
    bit <<= 1;
    bit |= e;
    bit <<= 1;
    bit |= f;
    bit <<= 1;
    bit |= g;
    bit <<= 1;
    bit |= h;
    return bit;
}

