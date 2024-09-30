all: PUSH

PUSH: complex.o sort.o main.o
	g++ complex.o sort.o main.o -o PUSH

complex.o: complex.cpp
	g++ complex.cpp -c 

sort.o: sort.cpp 
	g++ sort.cpp -c 

main.o: main.cpp
	g++ main.cpp -c

clean: 
	rm -rf *.o PUSH
 
	

