default : hamming.o
	gcc -o hamming hamming.o

hamming.o : hamming.c
	gcc -c hamming.c

clean :
	rm hamming hamming.o
