
//
//  hNode.cpp
//  p4
//
//  Created by Davey Jay Belliss on 5/11/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
//

#include "hNode.h"

void hNode::getCode2(hNode* leaves[256], int* binaryChar, int &pos2, short& bits, int& pos, unsigned char* encodedMessage, int size, const unsigned  char *message)
{
    hNode* ptr = this;
    bool leftb[21] = {false};
    short truth = 0;
    for (int i = 0; i <= size - 1; i++)
    {/*
        if (bits >= 8)
        {
        encodedMessage[pos++] = (*binaryChar << 24) >> 24;
        *binaryChar <<= 8;
        bits = bits - 8;
        //    *binaryChar = 0;
        }*/
        truth = 0;
        ptr = leaves[message[i]];
        
        while (ptr->parent != NULL)
        {
            leftb[truth] = ptr->isLeft;
            ptr = ptr->parent;
            truth++;
            
            //  ptr = parent;
        }
        truth--;
        
        while (truth >= 0)
        {
            if (leftb[truth])
            {
                bits++;
                
                if (bits == 8)
                {
                    encodedMessage[pos++] = *binaryChar;
                    bits = 0;
                    *binaryChar = 0;
                }
                
                *binaryChar <<= 1;
                
            }
            
            else
            {
                bits++;
                *binaryChar |= 1;
                
                if (bits == 8)
                {
                    encodedMessage[pos++] = *binaryChar;
                    *binaryChar = 0;
                    bits = 0;
                }
                *binaryChar <<= 1;
                
            }
            truth--;
        }
        

    }
    
}// prints original message into binary array to be converted into actual binary in encoded message





void hNode::getCode(unsigned  char* binaryChar, int &pos2, short& bits, int& pos, unsigned char* encodedMessage)
{
    if (parent != NULL)
        parent->getCode(binaryChar, pos2, bits, pos, encodedMessage);
    else
        return;
    
    if (isLeft)
    {
        
     //   *binaryChar |= 0;
        bits++;
        
        if (bits == 8)
        {
            encodedMessage[pos++] = *binaryChar;
            bits = 0;
            *binaryChar = 0;
        }
        
        *binaryChar <<= 1;
        
        return;
        
 
    }
    
    else
    {
        bits++;
        *binaryChar |= 1;
        
        if (bits == 8)
        {
            encodedMessage[pos++] = *binaryChar;
            *binaryChar = 0;
            bits = 0;
        }
        *binaryChar <<= 1;
        return;
    }
    
    
}
    

    
// prints original message into binary array to be converted into actual binary in encoded message



bool hNode::isLeafNode()
{
    return isLeaf;
}



void hNode::print(unsigned  char* encodedMessage, int& pos)
{
    
    if (isLeaf)
    {
        encodedMessage[(pos)++] = '1';
        encodedMessage[(pos)++] = (unsigned  char)ASCII;
        return;
        
    }//1 signifies the next character is ASCII of leafnode
    
    encodedMessage[(pos)++]= '0'; // 0 signifies internal node
    left->print(encodedMessage, pos);
    right->print(encodedMessage, pos);
    
}//prints tree PLR into encoded array(0's and 1's and ASCII's to remake tree)



void hNode::setParentL(hNode *parent)
{
    this->parent = parent;
    parent->left = this;
}



void hNode::setParentR(hNode *parent)
{
    this->parent = parent;
    parent->right = this;
    
}

void hNode::treeTraverse(unsigned  char* decodedMessage, unsigned const char* encodedMessage, int &pos, int &decoded, unsigned char* binary, short& bits, int& bytes, int size, short stopper)
{
     hNode* ptr = this;
    
    
    while(1)
    {
       
        
        if (ptr->right) // if not leafNode
        {
            if (bits == 8) // used all 8 bits
            {
            
                bits = 0;
                bytes++;
                binary[0] = encodedMessage[pos++];
                if (bytes == size - 1)
                {
                    this->treeTraverse3(decodedMessage, decoded, binary, bits, stopper, ptr);
                    return;
                }// last set of bits
                 
            }// new set of bits
        
            char x = 128 & binary[0];
            binary[0] <<= 1;
            bits++;
            
            if (x) // go right
                ptr = ptr->right;
            
            else //(encodedMessage[i] == '0')
                ptr = ptr->left;
                
            }
    
            else
            {
                decodedMessage[decoded++] = (unsigned char)ptr->ASCII;
                ptr = this;
                
            }
    }
    
}//converts binary into chars for decoded message

void hNode::treeTraverse2(unsigned  char* decodedMessage, unsigned const char* encodedMessage, int &pos, int &decoded, unsigned char* binary, short& bits, int& bytes, int size, short stopper)
{
    hNode* ptr = this;
    int test = 0;
    test = encodedMessage[pos - 1];
    test <<= 8;
    test |= encodedMessage[pos++];
    test <<= 8;
    test |= encodedMessage[pos++];
    test <<= 8;
    test |= encodedMessage[pos++];

    
    char x;
    
    while(1)
    {
        
        
        if (ptr->right) // if not leafNode
        {
            if (bits == 32) // used all 8 bits
            {
                
                bits = 0;
                bytes = bytes + 4;
             //   binary[0] = encodedMessage[pos++];
                test = encodedMessage[pos++];
                test <<= 8;
                test |= encodedMessage[pos++];
                test <<= 8;
                test |= encodedMessage[pos++];
                test <<= 8;
                test |= encodedMessage[pos++];
                
                if (bytes >= size - 1)
                {
                    this->treeTraverse3(decodedMessage, decoded, binary, bits, stopper, ptr);
                    return;
                }// last set of bits
                
            }// new set of bits
            x = 128 & (test >> 24);
            test <<=1;
         //   x = 128 & binary[0];
          //  binary[0] <<= 1;
            bits++;
            
            if (x) // go right
                ptr = ptr->right;
            
            else //(encodedMessage[i] == '0')
                ptr = ptr->left;
            
        }
        
        else
        {
            decodedMessage[decoded++] = (unsigned char)ptr->ASCII;
            ptr = this;
            
        }
    }
    
}//converts binary into chars for decoded message


void hNode::treeTraverse3(unsigned  char* decodedMessage, int &decoded, unsigned char* binary, short& bits,  short stopper, hNode* ptr)
{
    if (bits == stopper)
        return;
    
    while(1 )
    {
        
        if (ptr->right) // if not leafNode
        {

            
            char x = 128 & binary[0];
            *binary <<= 1;
            bits++;
            if (x) // go right
                ptr = ptr->right;
            else //(encodedMessage[i] == '0')
                ptr = ptr->left;
            
        }
        
        else
        {
            decodedMessage[decoded++] = (unsigned char)ptr->ASCII;
            
            if (bits == stopper) // used all 8 bits
                return;
            
            ptr = this;
        }
    }
    
}//converts binary into chars for decoded message





void hNode::operator=(hNode RHS)
{
    this->ASCII = RHS.ASCII;
    this->weight = RHS.weight;
}


bool  hNode::operator<(hNode RHS)
{
    return ((this->weight) < (RHS.weight));
}// returns true if first has greater weight


int hNode::getValue()
{
    return ASCII;
}

hNode::hNode(hNode* first, hNode* second): ASCII(0)
{
    
    this->left = first;
    this->right = second;
    
    weight = first->weight + second->weight;
    left->parent = this;
    right->parent = this;
    isLeaf = false;
    left->isLeft = true;
    
}


hNode::hNode(): ASCII(0), weight(0)
{
    isLeaf = false;
    isLeft = false;
}

hNode::hNode(int ASCI, int weigh): ASCII(ASCI), weight(weigh), isLeaf(true)
{
     isLeft = false;
}


void hNode::setASCII(unsigned char letter)
{
    isLeaf = true;
    ASCII = (unsigned char)letter;
}