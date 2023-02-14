all: stack.exe
stack.o: stack.c
	gcc -c stack.c
stack.exe: stack.o
	gcc -o stack.exe stack.o
clean:
	rm -f stack.o stack.exe