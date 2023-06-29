#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListTest          makes ListTest
# make clean             removes all binaries
# make checkTest         checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------
CFLAGS = -Wall -Werror -Wextra -Wpedantic 


Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c17 -Wall -c Lex.c

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o


ListTest.o : ListTest.c List.h
	gcc -std=c17 -Wall -c -g ListTest.c


List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

checkTest : 
	valgrind --leak-check=full ListTest

checkLex :
	valgrind --leak-check=full Lex in1.txt out1.txt
