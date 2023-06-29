/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA1 
* ListTest.c 
* Used to Test List.c ensuring proper functionality.
*********************************************************************************/ 


#include "List.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


int main (void){

    List l = newList();
    //testing multiple manipulation and move operations.
    //test 1 (5 manipulation operations): 
    printf("Begin test 1\n");
    append(l,1);
    prepend(l,5);
    moveFront(l);
    insertBefore(l,7);
    insertAfter(l,8);
    deleteFront(l);
    assert(get(l)==5);
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("results should be 5 8 1\n");
    printf("---------------------------------\n");

    //test 2:
    //test 1 (10 manipulation operations): 
    printf("Begin test 2\n");
    clear(l);
    assert(length(l)==0);
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("if something has been printed, then error in your code!\n");
    printf("---------------------------------\n");
    prepend(l,1);
    moveBack(l);
    append(l,6);
    insertAfter(l,7);
    moveNext(l);
    insertBefore(l,18);
    insertAfter(l,72);
    prepend(l,67);
    prepend(l,68);
    prepend(l,69);
    append(l,77);
    set(l, 86);
    deleteBack(l);
    deleteFront(l);
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("results should be 68 67 1 18 86 72 6\n");
    printf("---------------------------------\n");


    //test 3: test move front and move next.
    clear(l);
    append(l,67);
    printf("an error should be printed below.\n");
    insertAfter(l,66); //cursor is undefined, you cannot do an insertAfter.  
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("result should be 67\n");
    printf("---------------------------------\n");
    append(l,68);
    append(l,69);
    append(l,70);
    moveFront(l);
    moveNext(l);
    moveNext(l);
    moveNext(l);
    assert(index(l) == 3);
    moveNext(l);
    assert(index(l)==-1);

    //test 4: test deleteFront and deleteBack 
    clear(l);
    for(int i = 0; i < 12;i++){
        append(l,i);
    }
    moveFront(l);
    deleteFront(l);
    assert(index(l)==-1);
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("result should be 1 2 3 4 ... 11\n");
    printf("---------------------------------\n");
    moveBack(l);
    assert(index(l)==10);
    deleteBack(l);
    assert(index(l)==-1);
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("result should be 1 2 3 4 ... 10\n");
    printf("---------------------------------\n");
    moveBack(l);

    printf("----ensuring deleteBack doesnt cause segfault-----\n");
    for(int i = 0; i < 10; i++){
        deleteBack(l); 
    }

    assert(index(l)==-1);
    assert(length(l)==0);

    for(int i = 0; i < 12;i++){
        prepend(l,i);
    }
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("result should be 11 10 9 ... 0\n");
    printf("---------------------------------\n");

    printf("----ensuring deleteFront doesnt cause segfault-----\n");
    for(int i = 0; i < 12; i++){
        deleteFront(l); 
    }
    printf("---------------------------------------------------\n");

    assert(length(l)==0);
    assert(index(l)==-1);

    for(int i = 0; i < 12;i++){
        append(l,i);
    }
    moveFront(l);
    moveNext(l);
    deleteBack(l);
    assert(get(l)==1);
    moveBack(l);
    assert(get(l)==10);// 9 8 
    movePrev(l);
    movePrev(l);
    deleteFront(l);
    assert(index(l)==7);
    


    //test 5: test delete():
    clear(l);
    prepend(l,5);
    prepend(l,6);
    moveFront(l);
    prepend(l,7);
    prepend(l,8);
    assert(index(l)==2);
    moveNext(l);
    insertBefore(l,10);
    insertBefore(l,11);
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("result should be 8 7 6 10 11 5\n");
    printf("---------------------------------\n");
    assert(index(l)==5);
    delete(l);
    assert(index(l)==-1);
    printf("-------print statement below-----\n");
    printList(stdout,l);
    printf("\n");
    printf("result should be 8 7 6 10 11\n");
    printf("---------------------------------\n");
    deleteBack(l);
    deleteBack(l);
    deleteBack(l);
    deleteBack(l);
    moveBack(l);
    delete(l);
    assert(length(l)==0);
    assert(index(l)==-1);









    





    //printList(stdout,new);
    printList(stdout,l);
    freeList(&l);
    return 0;
}
