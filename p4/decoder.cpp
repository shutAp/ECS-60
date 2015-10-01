//
//  decoder.cpp
//  p4
//
//  Created by Davey Jay Belliss on 5/7/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
//


#include "decoder.h"
#include "hNode.h"
#include <fstream>
//#include "CPUTimer.h"


void Decoder::decode(const unsigned  char* encodedMessage, const int encodedSize,
                     unsigned  char* decodedMessage, int *decodedSize)
{
    hNode* root = new hNode();
 
    int pointer = 0;
    int *pos = &pointer; // POSITION IN ENCODED ARRAY
    short extra = encodedMessage[0];
    makeTree(encodedMessage, encodedSize, decodedMessage, decodedSize, root, *pos, false);
    (*pos) = *pos + 5;
    int decode = 0;
    int *decoded = &decode; // NUMBER OF ELEMENTS DECODED
    short bits = 0;
    short *bit = &bits;
    int bytes = 0;
    int *byte = &bytes; // numbers oc chars decoded
    unsigned char* binary = new unsigned char; // CHAR TO READ BINARY CHARACTERS OUT OF
    int size = encodedSize - *pos; // HOW MANY BITS TO READ
    binary[0] = encodedMessage[(*pos)++];
    
    
    root->treeTraverse(decodedMessage, encodedMessage, *pos, *decoded, binary, *bit, *byte, size, extra);
     *decodedSize = *decoded;
    return;
    
} // decode()



Decoder::Decoder()
{
} // Decoder()


Decoder::~Decoder()
{
} // ~Decoder()



void Decoder::makeTree(const unsigned  char *encodedMessage, const int encodedSize, unsigned  char *decodedMessage, int *decodedSize, hNode* parent, int& i, bool isLeft)
{
    i++;
    
    if (encodedMessage[i] == 'D')
        if (encodedMessage[i+1] == 'O')
            if (encodedMessage[i+2] == 'N')
                if (encodedMessage[i+3] == 'E')
                    return;
  
    if (encodedMessage[i] == '0')//current node is NOT a leafnode
    {
        
        hNode* newNodeL = new hNode();
        newNodeL->setParentL(parent);
        makeTree(encodedMessage, encodedSize, decodedMessage, decodedSize, newNodeL, i, true);
        
        hNode* newNodeR = new hNode();
        newNodeR->setParentR(parent);
        makeTree(encodedMessage, encodedSize, decodedMessage, decodedSize, newNodeR, i, false);
        
        return;
     }
    
    else //(encodedMessage[i] == '1')
        parent->setASCII(encodedMessage[++i]);
} // Rebuilds Tree
