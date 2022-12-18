all:	range.c
	cc range.c -O0 -g -o range

gdb-1:	range scen1.gdb
	gdb -x scen1.gdb -q --batch --args ./range 1 12 > log/scen1.log
gdb-2:	range scen2.gdb
	gdb -x scen2.gdb -q --batch --args ./range -100 100 3 > log/scen2.log

test:	log/scen1.log log/scen2.log
	grep '@@@' log/scen1.log | cmp test/scen1.txt
	grep '@@@' log/scen2.log | cmp test/scen2.txt
	echo TESTS PASSED!

clean:
	rm -rf range log *.o *.out test