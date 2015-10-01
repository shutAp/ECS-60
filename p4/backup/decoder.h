//
//  decoder.h
//  p4
//
//  Created by Davey Jay Belliss on 5/7/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
//

// Author: Sean Davis
#ifndef DECODER_H
#define DECODER_H
#include "hNode.h"

class Decoder
{
public:
    Decoder();
    ~Decoder();
    void decode(const unsigned  char* encodedMessage, const int encodedSize,
                unsigned  char* decodedMessage, int *decodedSize);
    void makeTree(const unsigned  char* encodedMessage, const int encodedSize,
                     unsigned  char* decodedMessage, int *decodedSize, hNode* parent, int& i, bool isLeft);
private:
    
};

#endif  /* DECODER_H */