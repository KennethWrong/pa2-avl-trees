
#This is a makefile
WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -03 $(WARNING) $(ERROR)

all:
	$(CC) create_tree.c pa2.c -o pa2

exec:
	./pa1
clean:
	rm -rf pa2
	rm -rf *.exe
	rm -rf *.o

test1:
	./pa2 -b ./examples/ops0.b ./examples/ops0m.txt
