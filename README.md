# Rutgers-cs214-code
--------------------

## How to compile these programs
Most folders contain a make where the command: "make all" will compile the code

## Assignment 1
Printing shapes using the symbol * 

## Assignment 2
1. Function adds element to a list at nth element
2. String buffer 

## Assignment 3
Code is designed to fix the command:
	> cat file1 file2 file3 | ./ww 80
Where the bug comes from the last paragraph of one file merging with the first paragraph of the next file
File exectuion:
> ./{compiled file name} {count of word wrap} {File}

## Project 1
Takes in a file and word wraps it with a given value. Execute by using:
> ./{compiled file name} {width} {File}

## Project 3
Terminal based Multi-Threaded server where users can access and manipulate keys stored in the server

####Compilation:
> make all

####Execution
Execution the server:
> ./{compiled file name} {port number}

Accessing server
> {terminal based program to connect to server} {server port number}
