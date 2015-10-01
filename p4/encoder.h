//
//  encoder.h
//  p4
//
//  Created by Davey Jay Belliss on 5/7/15.
//  Copyright (c) 2015 Davey Jay Belliss. All rights reserved.
//

#ifndef ENCODER_H
#define	ENCODER_H
#include "strings.h"


class Encoder
{
public:
    Encoder();
    void encode(const unsigned  char *message, const int size,
                unsigned  char *encodedMessage, int *encodedSize);
    ~Encoder();
    
    unsigned char getBits(short a, short b, short c, short d, short e, short f, short g, short h);

private:
    
};

#endif	/* ENCODER_H */