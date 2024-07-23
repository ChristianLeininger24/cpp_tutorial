all: clean compile checkstyle test

compile:
	clang++ -o PrimeMain PrimeMain.cpp
	clang++ -o PrimeTest PrimeTest.cpp -lgtest -pthread

checkstyle:
	clang-format-12 --dry-run -Werror *.cpp

test:
	./PrimeTest

format:
	find . -iname '*.cpp' -o -iname '*.h' | xargs clang-format-12 -i

clean:
	rm -f PrimeMain
	rm -f PrimeTest