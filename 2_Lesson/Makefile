.SUFFIXES:
.PHONY: clean compile checkstyle test
.PRECIOUS: %.o

all: clean compile checkstyle test

compile: PrimeMain 

checkstyle:
	clang-format-12 --dry-run -Werror *.cpp


PrimeMain: PrimeMain.o Prime.o
	clang++ -o PrimeMain PrimeMain.o Prime.o

Prime.o: Prime.cpp 
	clang++ -c Prime.cpp

PrimeMain.o: PrimeMain.cpp
	clang++ -c PrimeMain.cpp

PrimeTest: PrimeTest.o Prime.o
	clang++ -o PrimeTest PrimeTest.o Prime.o -lgtest -lpthread

PrimeTest.o: PrimeTest.cpp
	clang++ -c PrimeTest.cpp


test: PrimeTest
	./PrimeTest

format:
	find . -iname '*.cpp' -o -iname '*.h' | xargs clang-format-12 -i

clean:
	rm -f PrimeMain
	rm -f PrimeTest
	rm -f *.o
	rm -f a.out
