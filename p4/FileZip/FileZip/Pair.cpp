//
//  Pair.cpp
//  FileZip
//
//  Created by Vincent Yang on 5/7/15.
//  Copyright (c) 2015 Vincent. All rights reserved.
//

#include "Pair.h"
Pair::Pair(char *k, int val, int len)
{
  for (int i = 0; i < len; i++)
  {
    key[i] = k[i];
  }
  value = val;
  length = len;
}
int Pair::getValue()
{
  return value;
}