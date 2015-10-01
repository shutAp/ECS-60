//
//  Pair.h
//  FileZip
//
//  Created by Vincent Yang on 5/7/15.
//  Copyright (c) 2015 Vincent. All rights reserved.
//

#ifndef __FileZip__Pair__
#define __FileZip__Pair__

#include <stdio.h>
class Pair
{
private:
  char *key;
  int value, length;
public:
  Pair(char *k, int val, int len);
  int getValue();
};
#endif /* defined(__FileZip__Pair__) */
