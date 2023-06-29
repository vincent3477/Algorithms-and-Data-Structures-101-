#********************************************************************************* 
# Vincent Siu, vsiu2
# 2023 Spring CSE101 PA8 
# Makefile
# Used to both compile WordFrequency and Order.
#********************************************************************************/ 

CC = g++
CFLAGS = -std=c++17 -Wall 
LFLAGS = -std=c++17 -Wall 

all: Order WordFrequency DictionaryTest

Order: Order.o Dictionary.o
	$(CC) -o Order Order.o Dictionary.o $(LFLAGS)
	
WordFrequency: WordFrequency.o Dictionary.o
	$(CC) -o WordFrequency WordFrequency.o Dictionary.o $(LFLAGS)
	
DictionaryTest: DictionaryTest.o Dictionary.o
	$(CC) -o DictionaryTest DictionaryTest.o Dictionary.o $(LFLAGS)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f WordFrequency Order DictionaryTest *.o
	

