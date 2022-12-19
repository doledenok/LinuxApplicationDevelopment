all:	esub.c
	cc esub.c -o esub

test-1:	esub
	./esub [ab] AB bcdaefgh > log/test-1.log
	echo bcdaefgh | sed -E "s/[ab]/AB/" | cmp log/test-1.log

test-2: esub
	./esub ahahah not_funny ahah////ahahah > log/test-2.log
	echo ahah////ahahah | sed -E "s/ahahah/not_funny/" | cmp log/test-2.log

test-3:	esub
	./esub [ab} AB bcdaefgh > log/test-3.log || true
	echo Regex compilation failed: Unmatched [, [^, [:, [., or [= | cmp log/test-3.log

test:	esub test-1 test-2 test-3
	echo TESTS PASSED!

clean:
	rm -rf log esub *.o *.out