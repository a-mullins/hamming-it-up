default : hamming.o
	g++ -o hamming hamming.o

hamming.o : hamming.cpp
	g++ -c hamming.cpp

clean :
	rm hamming hamming.o
