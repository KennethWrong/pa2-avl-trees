
#This is a makefile
WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -03 $(WARNING) $(ERROR)

pa4:
	$(CC) *.c -o pa2

all:
	$(CC) *.c -o pa2

exec:
	./pa1
clean:
	rm -rf pa2
	rm -rf *.exe
	rm -rf *.o

test1:
	./pa2 -b ./examples/ops0.b ./tests/test1.b
test2:
	./pa2 -b ./examples/ops1.b ./tests/test2.b
test3:
	./pa2 -b ./examples/ops2.b ./tests/test3.b
test4:
	./pa2 -b ./examples/ops3.b ./tests/test4.b

test5:
	./pa2 -e ./examples/tree0.b
test6:
	./pa2 -e ./examples/tree1.b
test7:
	./pa2 -e ./examples/tree2.b
test8:
	./pa2 -e ./examples/tree3.b
test9:
	./pa2 -e ./examples/invalidtree0.b
test10:
	./pa2 -e ./examples/invalidtree1.b
test11:
	./pa2 -e ./examples/invalidtree2.b
test12:
	./pa2 -e ./examples/Emptyfile.b
test13:
	./pa2 -e ./examples/joe.b
test14:
	./pa2 -b ./examples/joe.b ./tests/test4.b
test15:
	./pa2 -b ./examples/Emptyfile.b ./tests/joe4.b