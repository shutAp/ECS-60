#include <iostream>
#include <stdlib.h>
#include "StackLi.h"
#include <fstream>

using namespace std;
int main(int argc, const char * argv[])
{
  char line[256];
  char c;
  ifstream inf(argv[1]);
  StackLi<int> stack = *new StackLi<int>();
  StackLi<int> lineNum = *new StackLi<int>();
  bool commented = false;
  int i = 0;
  if (!inf.is_open())
    return 0;
  while(!inf.eof())
  {
    inf.getline(line, 256);
    i++; //increment line number
    for (int j = 0; line[j] != '\0'; j++)
    {
      c = line[j];
      
      if (commented && c != '*')
        continue;
      if (c == '/' && line[j+1] == '*')
      {
        stack.push(1);
        lineNum.push(i);
        commented = true;
      }
      else if (c == '*' && line[j+1] == '/') //-1
      {
        if (stack.isEmpty())
        {
          cout << "Unmatched */ on line #" << i << endl;
          return 0;
        }
        if (stack.top() != 1)
        {
          cout << "Unmatched */ on line #" << lineNum.top() << endl;
          return 0;
        }
        commented = false;
        stack.pop();
        lineNum.pop();
      
      }
      else if (c == '(') //2
      {
        lineNum.push(i);
        stack.push(2);
      }
      else if (c == ')') //-2
      {
        if (stack.isEmpty())
        {
          cout << "Unmatched ) on line #" << i << endl;
          return 0;
        }
        if (stack.top() != 2)
        {
          cout << "Unmatched ) on line #" << lineNum.top() << endl;
          return 0;
        }
        
        stack.pop();
        lineNum.pop();
      }
      else if (c == '[') //3
      {
        stack.push(3);
        lineNum.push(i);
      }
      else if (c == ']') //-3
      {
        if (stack.isEmpty())
        {
          cout << "Unmatched ] on line #" << i << endl;
          return 0;
        }
        if (stack.top() != 3)
        {
          cout << "Unmatched ] on line #" << lineNum.top() << endl;
          return 0;
        }
        //cout << "Found close bracket" << endl;
        lineNum.pop();
        stack.pop();
      }
      else if (c == '{') //4
      {
        stack.push(4);
        lineNum.push(i);
      }
      else if (c == '}') //-4
      {
        if (stack.isEmpty())
        {
          cout << "Unmatched } on line #" << i << endl;
          return 0;
        }
        if (stack.top() != 4)
        {
          cout << "Unmatched } on line #" << lineNum.top() << endl;
          return 0;
        }
        
        stack.pop();
        lineNum.pop();
      }
    }
  }
  if (!stack.isEmpty())
  {
    //cout << "stack is not empty" << endl;
    if (stack.top() == 1)
    {
      cout << "Unmatched /* on line #" << lineNum.top() << endl;
    }
    else if (stack.top() == 2)
    {
      cout << "Unmatched ( on line #" << lineNum.top() << endl;
    }
    else if (stack.top() == 3)
    {
      cout << "Unmatched [ on line #" << lineNum.top() << endl;
    }
    else if (stack.top() == 4)
    {
      cout << "Unmatched { on line #" << lineNum.top() << endl;
    }
    return 0;
  }
  cout << "OK" << endl;

}
