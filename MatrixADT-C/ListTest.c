
#include "List.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef struct EntryObj * Entry;
typedef struct EntryObj {
    int val;
}EntryObj;



Entry newEntry(int val){
    Entry n = malloc(sizeof(EntryObj));
    n->val = val;
    return n;
}

void deleteEntry(Entry * e){
    if((*e)!=NULL){
       // free((*e)->val);
        //free((*e)->col);
        free(*e);
        *e=NULL;
    }
}

void printList(FILE * out, List l){
    moveFront(l);
    while(index(l)>=0){
        printf("%d ",*(int*)get(l));
        moveNext(l);
    }
}


/*
void freeList(List* pL); // Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
// Access functions -----------------------------------------------------------


// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.
void set(List L, void * x); // Overwrites the cursor element’s data with x.


void insertBefore(List L, void * x); // Insert new element before cursor.
void deleteBack(List L); // Delete the back element. Pre: length()>0

*/

int main (void){

    List test = newList();
    for(int i = 0; i < 20;i++){
        Entry e = newEntry(i*2);
        append(test,e);
    }
    printList(stdout,test);
    printf("\nshould print 0 -> 38 (inc by 2)\n");
    assert(length(test)==20);
    for(int i = 0; i < 5;i++){
        Entry del = front(test);
        deleteEntry(&del);
        deleteFront(test);
    }
    printList(stdout,test);
    printf("\nshould be 10 -> 38 (inc by 2)\n");
    assert(length(test)==15);
    moveFront(test);
    for(int i = 9; i < 38;i+=2){
        Entry e = newEntry(i);
        insertBefore(test,e);
        moveNext(test);
    }
    printList(stdout,test);
    printf("\nshould be 9 -> 38\n");
    moveBack(test);
    for(int i = 38; i >= 9;i--){
        assert(*(int*)get(test)==i);
        movePrev(test);
    }

    for(int i = 8; i >= 0; i--){
        Entry e = newEntry(i);
        prepend(test,e);
    }
    printList(stdout,test);
    printf("\nshould be 0 -> 38\n");

    for(int i = 0; i <= 8; i++){
        Entry del = back(test);
        deleteEntry(&del);
        deleteBack(test);
    }
    assert(length(test)==30);
    printList(stdout,test);
    printf("\nshould be 0 -> 29\n");

    moveFront(test);
    moveNext(test);
    moveNext(test);
    moveNext(test);
    moveNext(test);
    moveNext(test);
    moveNext(test);
    assert(index(test)==6);
    Entry e = newEntry(999);
    Entry f = newEntry(1000);
    insertBefore(test,e);
    insertBefore(test,f);
    assert(index(test)==8);

    printList(stdout,test);
    printf("\nshould be 0 1 2 3 4 5 999 1000 6 -> 29\n");
    moveFront(test);
    for(int i = 0; i < length(test);i++){
        Entry d = get(test);
        deleteEntry(&d);
        moveNext(test);

    }
    clear(test);
    printf("\nnothing should be printed below after clearing of the list\n");
    assert(length(test)==0);
    printList(stdout,test);
    freeList(&test);

}   

