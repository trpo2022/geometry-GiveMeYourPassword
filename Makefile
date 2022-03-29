all: main run clean

main: main.c
	g++ -Wall -w -o main main.c

clean:
	rm main

run:
	./main	