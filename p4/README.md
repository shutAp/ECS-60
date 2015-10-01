# Huffman

This program compresses files with Huffman encoding,
completed May 19, 2015 for program 4, ECS 60 at UC Davis

## Assignment:
This was the first challenge program of ECS 060, Data Structures and Programming
at the University of California, Davis.
[Program 4 Assignment](https://github.com/YangVincent/Huffman/blob/master/prog4.pdf)

## Considered Alternatives:
Originally, Lempel-Ziv-Welch compression was considered for this project.
However before long, LZW compression took too long, and an alternative had to be
used. Therefore, we implemented Huffman encoding.

## How it works: 
* The main portion of the program reads in a file as a char array. It then finds
how many time each character (from 0 to 256) was used
* It then creates a min-heap of "Trees", removing each node and replacing the 
combined node into the heap. When the heap has only one item, the tree has 
finished building
* It reads the Tree as well as the 8-numRemainderBits into the first portion of
output. 
* Finally, it compresses the message using the Huffman tree, and converts the 
1's and 0's to binary with bitshifts

![Huffman](https://github.com/YangVincent/Huffman/blob/master/Huffman.png)
