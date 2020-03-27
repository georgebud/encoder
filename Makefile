build: encoder

encoder: encoder.o
	gcc -Wall -g encoder.o -lm -o encoder

encoder.o: encoder.c
	gcc -c -g encoder.c

run: encoder
	./encoder

clean: 
	rm -f *.o *~ encoder
