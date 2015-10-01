//
//  main.cpp
//  FileZip
//
//  Created by Vincent Yang on 5/7/15.
//  Copyright (c) 2015 Vincent. All rights reserved.
//

#include <iostream>
  //#include "QuadraticProbing.h"
#include "mystring.h"
#include <map>
using namespace std;
unsigned int toBinary(unsigned int k)
{
  return (k == 0 || k == 1 ? k : ((k % 2) + 10 * toBinary(k / 2)));
}
void generateInitialDict(map<char[], int> *map)
{
  cout << "in generateInitialDict" << endl;
  for (char c = 'a'; c <= 'z'; c++)
  {
    (*map)[c] = (int)c - 96;
  }  /*
  for (char c = 'a'; c <= 'z'; c++)
  {
    cout << "char c is " << c << endl;
    //map a to 1.
    cout << "now char c is " << (int)c-96 << endl;
    cout << "in binary: " << endl;
    cout << toBinary((int) c-96) << endl;
  }*/
}
void addToDict(char *testString, map<char[], int> *map)
{
  
}
int main(int argc, const char * argv[])
{
    //char filename[80];
    //cout << "filename >> ";
    //cin >> filename;
    //QuadraticProbing hashTable = *new QuadraticProbing();
  do
  {
      //generateInitialDict();
  } while (false);
  cout << "Testing HashTable" << endl;
  std::map<char[], int> map;
  generateInitialDict(&map);
  int valOne = map[];
  cout << "val is " << valOne << endl;
  char testString[] = {'t', 'h', 'i', 's', '\0'};
    //addToDict(testString, map<char[], int>*map)
  
  return 0;
}
