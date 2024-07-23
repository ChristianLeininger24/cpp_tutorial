all: clean compile checkstyle test

compile:
	clang++ -o GcdMain GcdMain.cpp
	clang++ -o GcdTest GcdTest.cpp -lgtest -pthread

checkstyle:
	clang-format-12 --dry-run -Werror *.cpp

test:
	./GcdTest

format:
	find . -iname '*.cpp' -o -iname '*.h' | xargs clang-format-12 -i

clean:
	rm -f GcdMain
	rm -f GcdTest
