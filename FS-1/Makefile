all: saka 

saka: main.o
	g++ main.o -o saka

main.o: main.cpp 
	g++ main.cpp -c 

clean: 
	rm -rf *.o saka
