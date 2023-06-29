Vincent Siu, vsiu2
## About the program:
The FindPath program will create a Graph using the underlying Graph.c implementation, and it will allow the client to find the path from one vertice to another by doing BFS, which gives them a source vertex to go off from. Included is also a test file to test the functionality of Graph.c *on it's own*.

## Program usage: 
 - 1. make FindPath
 - 2. ./FindPath (input file) (output file)

## Files included:
 - FindPath.c (This program parses a text file, which the first portion contains the number of vertices, the second containing all the vertices themselves, and the third containing the number of connections or edges.)
 - List.c (Contains full implementation for a Doubly Linked List.)
 - List.h (header file for List.c)
 - Graph.c (Contains full implementation for a Graph ADT, which relies on the previously made Doubly Linked List ADT.)
 - Graph.h (header file for Graph.c)
 - GraphTest.c (A program to test functionality for Graph.c)
 - Makefile (to compile any include files.)
 - README (this file.)