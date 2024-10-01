all: privet

privet: main.o 
	g++ main.o -o privet

main.o: main.cpp
	g++ -c main.cpp 

clean: 
	rm -rf *.o privet 
