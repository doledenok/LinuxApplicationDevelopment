ARGS_2 = arg1
ARGS_3 = arg1 arg2 arg3
TRASH = *.out *.o *.a *.so *.log prog prog-a prog-so log

all: prog prog-a prog-so

prog:	const.o fun.o prog.o
	cc $^ -o prog
prog-a:	prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o prog-a
prog-so:	prog.o liboutput.so
	cc -L. prog.o -loutput -o prog-so

test: 	prog prog-a prog-so test/*

	mkdir -p log
	./prog > log/prog_1.log 2>>log/prog_1.log
	./prog-a > log/prog-a_1.log 2>>log/prog-a_1.log
	LD_LIBRARY_PATH=`pwd` ./prog-so > log/prog-so_1.log 2>>log/prog-so_1.log

	./prog $(ARGS_2) > log/prog_2.log 2>>log/prog_2.log
	./prog-a $(ARGS_2) > log/prog-a_2.log 2>>log/prog-a_2.log
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARGS_2) > log/prog-so_2.log 2>>log/prog-so_2.log

	./prog $(ARGS_3) > log/prog_3.log 2>>log/prog_3.log
	./prog-a $(ARGS_3) > log/prog-a_3.log 2>>log/prog-a_3.log
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARGS_3) > log/prog-so_3.log 2>>log/prog-so_3.log

	cmp log/prog_1.log test/prog_1.txt
	cmp log/prog_2.log test/prog_2.txt
	cmp log/prog_3.log test/prog_3.txt
	cmp log/prog-a_1.log test/prog-a_1.txt
	cmp log/prog-a_2.log test/prog-a_2.txt
	cmp log/prog-a_3.log test/prog-a_3.txt
	cmp log/prog-so_1.log test/prog-so_1.txt
	cmp log/prog-so_2.log test/prog-so_2.txt
	cmp log/prog-so_3.log test/prog-so_3.txt
	echo TESTS PASSED!


liboutput_static.a:	const.o fun.o
	ar -rcs liboutput_static.a $^

liboutput.so: 	const.o fun.o
	cc -shared $^ -o liboutput.so

fun.o:	fun.c 
	cc fun.c -fPIC -c -o fun.o
prog.o:	prog.c 
	cc prog.c -c -o prog.o

const.o:	const.c 
	cc const.c -c -o const.o

clean:
	rm -rf $(TRASH)