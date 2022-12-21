AM_CFLAGS = -O0 -g

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

test:
	echo "something" | sha1sum | cut -d ' ' -f 1 > pattern1.log
	echo 'SHA1 "something' | ./rhasher | grep -f pattern1.log

	echo "something" | md5sum | cut -d ' ' -f 1 > pattern2.log
	echo 'MD5 "somesthing' | ./rhasher | grep -f pattern2.log

	echo "TESTS PASSED"

distclean:
	rm -rf *.cache *.log config.* configure rhasher *.o *.m4 install-sh Makefile Makefile.in missing stamp-h1 compile depcomp test-driver *.log src/.deps src/.dirstamp src/rhasher.o