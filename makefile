all: main.o
	gcc -o main main.o

main.o:
	gcc -c main.c

clean:
	rm main.o
	rm main

run:
	./main