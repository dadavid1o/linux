all: redirect-cin

redirect-cin: redirect-cin.o 
	g++ redirect-cin.o -o redirect-cin

redirect-cin.o: redirect-cin.cpp
	g++ redirect-cin.cpp -c

clean:
	rm -rf *.o redirect-cin

