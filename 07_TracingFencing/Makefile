all:	move.c
	cc move.c -o move

test-1:	move
	echo something | cat > src.txt
	strace -eopenat -e fault=openat:error=EACCES ./move src.txt dst.txt 2> log/test-1.log || true
	grep "./move: error while loading shared libraries: libc.so.6: cannot open shared object file: Permission denied" log/test-1.log

test-2: fake_remove.c move
	cc -shared -o fake_remove.so fake_remove.c
	echo something | cat > src_PROTECT.txt
	LD_PRELOAD=`pwd`/fake_remove.so ./move src_PROTECT.txt dst.txt
	test -f src_PROTECT.txt

test:	test-1 test-2
	echo TESTS PASSED!

clean:
	rm -rf *.o *.out log dst.txt move *.so *.txt
