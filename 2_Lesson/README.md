# Prime Number Checker 
## This is a simple C++ program that checks whether a given number is prime or not. 
## Features 
- Input a number from the user. - Check if the number is prime. - Output the result to the user. 

## Dynamic vs stastic link
-  static link (.a)
	-  uses .a files and adds the code to the executable file 
		- exe gets bigger but no need for .a file well running the code
-  dynamic link (.so)
	- uses the .so files no extra code to the exe file
		- needs the .so file while running
- those are always lib* files 
	- example libgtest.a  can be used this Flag -lgtest
	-  default path /usr/local/lib
	- use -L path to force compiler to search also in this path for files
- use command ldd ./exe  to see which .so files are needed during run time
-  add more paths with export LD_LIBRARY_PATH=
- /etc/ld.so.conf.d/local.conf  file can also be added 
- then update comiler with sudo ldconfig
## Create own Libiary
## Requirements 
- Compiler Clang 12 or later
-  Styleckecker clang-format-12 
## Usage 
1. Clone the repository or download the source code. 
2. Use the provided Makefile to compile and run the program. 


### Example To compile and run the program using the Makefile:
 
 - Clone repository git ssh
  
	```shell
	git clone git@github.com:ChristianLeininger24/cpp_tutorial.git
	```
  
  - Create an executable file and test file
	```shell
	make compile
	```
- Run the program
	```shell
	./PrimeMain number
	```
- Run the test
	```shell
		make test
	```
