all: MODUL2 

MODUL2: MODUL2.o
	g++ MODUL2.o -o MODUL2 -std=c++20

MODUL2.o: MODUL2.cpp 
	g++ MODUL2.cpp -std=c++20 -c 

clean: 
	rm -rf *.o MODUL2
