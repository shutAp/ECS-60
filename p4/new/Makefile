encoder.out : binaryHeap.o decoder.o encoder.o hNode.o main.o vector.o  
	g++ -ansi -pg -Wall -g -o encoder.out binaryHeap.o decoder.o encoder.o hNode.o main.o vector.o  

binaryHeap.o : binaryHeap.cpp binaryHeap.h 
	g++ -ansi -Wall -g -c binaryHeap.cpp

decoder.o : decoder.cpp decoder.h hNode.h 
	g++ -ansi -Wall -g -c decoder.cpp

encoder.o : encoder.cpp encoder.h binaryHeap.cpp 
	g++ -ansi -Wall -g -c encoder.cpp

hNode.o : hNode.cpp hNode.h 
	g++ -ansi -Wall -g -c hNode.cpp

main.o : main.cpp CPUTimer.h encoder.h decoder.h 
	g++ -ansi -Wall -g -c main.cpp

vector.o : vector.cpp vector.h 
	g++ -ansi -Wall -g -c vector.cpp

clean : 
	rm -f encoder.out binaryHeap.o  decoder.o  encoder.o  hNode.o  main.o  vector.o   
