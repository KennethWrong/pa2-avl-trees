
#This is a makefile
WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -03 $(WARNING) $(ERROR)

all:
	$(CC) create_tree.c pa2.c tree_helper.c -o pa2

exec:
	./pa1
clean:
	rm -rf pa2
	rm -rf *.exe
	rm -rf *.o

test1:
	./pa2 -b ./examples/ops0.b ./tests/ops0m.txt
test2:
	./pa2 -b ./examples/ops0.txt ./tests/ops0mt.txt
test3:
	./pa2 -b ./examples/ops2.txt ./tests/ops2t.txt
test4:
	./pa2 -b ./examples/ops3.txt ./tests/ops3t.txt
test5:
	./pa2 -b ./examples/personal.txt ./tests/ops3t.txt
	