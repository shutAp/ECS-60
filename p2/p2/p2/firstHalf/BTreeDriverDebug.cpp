#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "BTree.h"

using namespace std;

int main(int argc, char *argv[])
{
  cout << "ay" << endl;
  //BTree tree(3, 3);
  BTree tree(3, 2);
  //BTree tree(atoi(argv[2]), atoi(argv[3]));
  int value;
  char s[80];

  ifstream inf(argv[1]);
  while(inf >> value)
  {
    cout << "Inserting " << value << ". \n";
    tree.insert(value);
    tree.print();
    fgets(s, 80, stdin);
  } // while

  int in = 0;
  while (in >= 0)
  {
    cout << "What do you want to input?" << endl;
    cin >> in;
    //cout << "in is " << in << endl;
    tree.insert(in);
    tree.print();
  }
  tree.print();
  return 0;
}  // main

