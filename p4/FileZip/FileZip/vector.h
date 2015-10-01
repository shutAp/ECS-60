//
//  vector.h
//  FileZip
//
//  Created by Vincent Yang on 5/7/15.
//  Copyright (c) 2015 Vincent. All rights reserved.
//

#include <stdio.h>
#ifndef __FileZip__vector__
#define __FileZip__vector__


/*
 * The next line is used because Codewarrior has a conflict with
 * the STL vector. Make sure to put the #include of this file
 * AFTER all the system includes.
 */
#define vector Vector
#include <cstddef>

class ArrayIndexOutOfBounds { };

template <class Object>
class vector
{
public:
  explicit vector( int theSize = 0 ) : currentSize( theSize )
  { objects = new Object[ currentSize ]; }
  vector( const vector & rhs ) : objects( NULL )
  { operator=( rhs ); }
  ~vector( )
  { delete [ ] objects; }
  
  int size( ) const
  { return currentSize; }
  
  Object & operator[]( int index )
  {
#ifndef NO_CHECK
  if( index < 0 || index >= currentSize )
    throw ArrayIndexOutOfBounds( );
#endif
  return objects[ index ];
  }
  
  const Object & operator[]( int index ) const
  {
#ifndef NO_CHECK
  if( index < 0 || index >= currentSize )
    throw ArrayIndexOutOfBounds( );
#endif
  return objects[ index ];
  }
  
  
  const vector & operator = ( const vector & rhs );
  void resize( int newSize );
private:
  int currentSize;
  Object * objects;
};

#include "vector.cpp"

#endif /* defined(__FileZip__vector__) */
