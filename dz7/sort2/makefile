all: sort.exe
sort.o: sort.c
	gcc -c sort.c
sort.exe: sort.o
	gcc -o sort.exe sort.o
clean:
	rm sort.o sort.exe