all: clean compile checkstyle test


compile: SnakeMain


Snake.o: Snake.cpp Snake.h
	clang++-12 -c Snake.cpp

SnakeMain.o: SnakeMain.cpp Snake.h
	clang++-12 -c SnakeMain.cpp  

SnakeMain: Snake.o SnakeMain.o
	clang++-12 -o SnakeMain SnakeMain.o Snake.o -lncurses


SnakeTest.o: SnakeTest.cpp Snake.h
	clang++-12 -c SnakeTest.cpp

SnakeTest: Snake.o SnakeTest.o
	clang++-12 -o SnakeTest SnakeTest.o Snake.o -lncurses -lgtest -pthread


checkstyle:
	clang-format-12 --dry-run -Werror *.cpp

test: SnakeTest
	./SnakeTest

format:
	find . -iname '*.cpp' -o -iname '*.h' | xargs clang-format-12 -i

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

