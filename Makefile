__build: main

main:
	gcc tree.c main.c -o main

clean:
	rm main