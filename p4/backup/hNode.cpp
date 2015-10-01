
//
//  hNode.cpp
//  p4
//
//  Created by Davey Jay Belliss on 5/11/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
//

#include "hNode.h"


void hNode::getCode(unsigned  char* binary, int &i)
{
    if (parent != NULL)
        parent->getCode(binary, i);
    else
        return;
    
    if (isLeft)
        binary[i++] = 0;
    else
        binary[i++] = 1;

}// prints original message into binary array to be converted into actual binary in encoded message



void hNode::getCode2(unsigned  char* binaryChar, int &pos2, short& bits, int& pos, unsigned char* encodedMessage)
{
    if (parent != NULL)
        parent->getCode2(binaryChar, pos2, bits, pos, encodedMessage);
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
    
    
    
        

    
}// prints original message into binary array to be converted into actual binary in encoded message



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

void hNode::treeTraverse(unsigned  char* decodedMessage, unsigned const char* encodedMessage, int &pos, int &decoded, unsigned char* binary, short& bits, int& bytes, int size, int stopper)
{
     hNode* ptr = this;
    
    
    while(1 )
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
                        this->treeTraverse3(decodedMessage, encodedMessage, pos, decoded, binary, bits, bytes, size, stopper, ptr);
                        return;
                    }
                 
                }
        
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


void hNode::treeTraverse3(unsigned  char* decodedMessage, unsigned const char* encodedMessage, int &pos, int &decoded, unsigned char* binary, short& bits, int& bytes, int size, int stopper, hNode* ptr)
{
if (bits == stopper)
    return;
    
    while(1 )
    {
        
        
        if (ptr->right) // if not leafNode
        {

            
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
            if (bits == stopper) // used all 8 bits
            {
                return;
                bits = 0;
                bytes++;
                if (bytes == size - 1)
                    return;
                binary[0] = encodedMessage[pos++];
            }
            
        }
    }
    
}//converts binary into chars for decoded message



void hNode::treeTraverse2(unsigned  char* decodedMessage, unsigned const char* encodedMessage, int &pos, int &decoded, unsigned char* binary, short& bits, int& bytes)
{
    
    if (right) // if not leafNode
    {
        if (bits == 8) // used all 8 bits
        {
            
            bits = 0;
            bytes++;
            binary[0] = encodedMessage[pos++];
        }
        
        int x = 128 & binary[0];
        binary[0] <<= 1;
        if (x) // go right
            right->treeTraverse2(decodedMessage, encodedMessage, pos, decoded, binary, ++bits, bytes);
        else //(encodedMessage[i] == '0')
            left->treeTraverse2(decodedMessage, encodedMessage, pos, decoded,binary, ++bits, bytes);
        return;
    }
    
    else
        decodedMessage[decoded++] = (unsigned char)ASCII;
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