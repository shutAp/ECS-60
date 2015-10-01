//
//  hNode.h
//  p4
//
//  Created by Davey Jay Belliss on 5/11/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
//

#ifndef __p4__hNode__
#define __p4__hNode__

#include <stdio.h>
#include <iostream>
using namespace std;

class hNode
{
    unsigned char ASCII;
    int weight;
    bool isLeaf;// = false;
    bool isLeft; //= false;
    hNode* parent = NULL;
    hNode* left = NULL;
    hNode* right = NULL;

    
    
public:
    hNode();
    hNode(hNode* first, hNode* second);
    hNode(int ASCI, int weigh = 0);
    
    int getValue();
    bool operator<(hNode RHS);
    void operator=(hNode RHS);
    void print(unsigned  char* binary, int& pos);
    void setParentL(hNode* parent);
    void setParentR(hNode* parent);
    void setASCII(unsigned char letter);
        void getCode2(hNode* leaves[256], int* binaryChar, int &pos2, short &bits, int &pos, unsigned char* encodedMessage, int size, const unsigned  char *message);
    void getCode(unsigned  char* binaryChar, int &pos2, short &bits, int &pos, unsigned char* encodedMessage);
    void treeTraverse2(unsigned  char* decodedMessage, unsigned const char* encodedMessage, int &pos, int &decoded, unsigned char* binary, short& bits, int& bytes, int size, short stopper);
    void treeTraverse(unsigned  char* decodedMessage,unsigned const  char* encodedMessage, int &pos, int &decoded, unsigned char* binary, short& bits, int & bytes, int size, short stopper);
    
    void treeTraverse3(unsigned  char* decodedMessage, int &decoded, unsigned char* binary, short& bits,  short stopper, hNode* ptr);//final traversal
    bool isLeafNode();
    
};
#endif /* defined(__p4__hNode__) */
