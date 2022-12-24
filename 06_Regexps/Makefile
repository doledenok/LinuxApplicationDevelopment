all:	esub.c
	cc esub.c -o esub

test-1:	esub
	./esub "[ab]" AB bcdaefgh > log/test-1.log
	echo bcdaefgh | sed -E "s/[ab]/AB/" | cmp log/test-1.log

test-2: esub
	./esub ahahah not_funny ahah////ahahah > log/test-2.log
	echo ahah////ahahah | sed -E "s/ahahah/not_funny/" | cmp log/test-2.log

test-3:
	./esub "(a)(b)" "@@\2@\1@@" abcd > log/test-3.log
	echo abcd | sed -E "s/(a)(b)/@@\2@\1@@/" | cmp log/test-3.log

test-4:
	./esub "(a)(b)" "@@\2\3@@" abcd > log/test-4.log || true
	echo "Wrong match number: 3" | cmp log/test-4.log

test-5:	esub
	./esub "[ab}" AB bcdaefgh > log/test-5.log || true
	echo Regex compilation failed: Unmatched [, [^, [:, [., or [= | cmp log/test-5.log

test:	esub test-1 test-2 test-3 test-4 test-5
	echo TESTS PASSED!

clean:
	rm -rf log esub *.o *.out