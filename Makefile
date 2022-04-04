all: main 

main: main.cpp
	g++ -Wall -w -o main main.cpp

clean:
	rm main

run:
	./main	