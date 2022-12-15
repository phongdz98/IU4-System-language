# all: main 
# lib.o: lib.c
# 	gcc -c lib.c
# main.o: main.c
# 	gcc -c main.c
# main: main.o lib.o
# 	gcc -o main main.o lib.o
# clean:
# 	rm -f main.o lib.o main
all: stack.exe
stack.o: stack.c
	gcc -c stack.c
stack.exe: stack.o
	gcc -o stack.exe stack.o
clean:
	rm -f stack.o stack.exe