
/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA4 
* List.c 
* Contains implementation for a List ADT using a Doubly Linked List.
*********************************************************************************/ 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"
typedef struct NodeObj * Node;
typedef struct NodeObj {
    void* val;
    Node prev;
    Node next;
}NodeObj;
typedef struct ListObj {
    int index; //this defines the current position of the cursor.
    int num_elements;
    Node head;
    Node tail;
    Node cursor;  
}ListObj;
// Constructors-Destructors ---------------------------------------------------
Node newNode(void*  value){
    Node n = malloc(sizeof(NodeObj));
    if(n==NULL){
        return NULL;
    }
    n->next = NULL;
    n->val = value;
    return n;
}
void deleteNode(Node *n){
    if((*n)!=NULL){
        //free((*n)->val);
        free(*n);
        *n=NULL;
    }
}
List newList(void){
    List l;
    l = malloc (sizeof(ListObj));
    assert(l!=NULL);
    l -> num_elements = 0;
    l -> index = -1;
    l->cursor = NULL;
    //l->tail->next = NULL;
    l->head=l->tail=NULL;
    return l;
} // Creates and returns a new empty List.
void freeList(List* pL){ // Frees all heap memory associated with *pL, and sets
    /*if(pL != NULL){
        Node curr = (*pL)->head;
        Node temp = curr;
        while(curr!=NULL){
            temp = curr;
            deleteNode(&curr);
            curr = temp->next;
        }
        free(*pL);
        *pL = NULL;
    }
    */
    
    if(pL != NULL && *pL !=NULL){
    	
    	while((*pL)->num_elements != 0){
    	    Node curr = (*pL)->tail;
    	    (*pL)->tail = (*pL)->tail->prev;
    	    (*pL)->num_elements-=1;
    	    free(curr);
    	    curr = NULL;
    	    }
    	
    	free(*pL);
    	*pL =NULL;
    }
}
// Access functions -----------------------------------------------------------

int length(List L){
    return L->num_elements;
    // Returns the number of elements in L.
} 
int index(List L){
    return L->index;
    // Returns index of cursor element if defined, -1 otherwise.
} 
void * front(List L){
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List Error: calling front() on an empty List.\n");
        exit(EXIT_FAILURE);
    }
    return L->head->val;
} // Returns front element of L. Pre: length()>0
void * back(List L){
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List Error: calling back() on an empty List.\n");
        exit(EXIT_FAILURE);
    }
    return L->tail->val;
} // Returns back element of L. Pre: length()>0
void * get(List L){
    
    if(L->num_elements <= 0 ){
        //printf("wheres the error");
        fprintf(stderr, "List Error: calling get() on an empty List.\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0 ){
        //printf("wheres the error");
        fprintf(stderr, "List Error: calling get() while cursor is NULL.\n");
        exit(EXIT_FAILURE);
    }
    
    
    return L->cursor->val;
} // Returns cursor element of L. Pre: length()>0, index()>=0

// Manipulation procedures ----------------------------------------------------
void clear(List L){
   /* if(L!=NULL){
        Node curr = L->head;
        Node temp = curr;
        
        while(curr!=NULL){
            temp = curr;
            deleteNode(&curr);
            curr = temp->next;
            
            
        }
        L->head=L->tail=NULL;
        L -> num_elements = 0;
        L -> index = -1;
        L->cursor = NULL;
        
        
    }
    */
    
    if(L!=NULL){
    	while(L->num_elements != 0){
    	    Node curr = L->tail;
    	    L->tail = L->tail->prev;
    	    L->num_elements-=1;
    	    free(curr);
    	    curr = NULL;
    	    }
        L->head = L->tail = NULL;
    	L->cursor = NULL;
    	L->index = -1;
    	
    }
} // Resets L to its original empty state.
void set(List L, void * x){
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List Error: calling set() on empty List.\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling set() while the cursor is NULL.\n");
    }
    L->cursor->val = x;
    
} // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void moveFront(List L){
    if(length(L)!=0){
        L->cursor = L->head;
        L->index = 0;
    }
} // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L){
    if(L->num_elements > 0){
        L->cursor = L->tail;
        L->index = L->num_elements - 1 ;
        //printf("num elements is %d",L->num_elements);
    }
    
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L){
    if(index(L) >= 0 ){
        L->index -=1 ;
        L->cursor = L->cursor->prev;
    }
    else{
        L->index = -1;
        L->cursor = NULL;
    }
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
    if(L->num_elements > 0){
        if(L->cursor != NULL && L->cursor != L->tail){
   	        L->cursor = L->cursor->next;
            L->index +=1 ;            
        }
        else if(L->cursor != NULL && L->cursor == L->tail){
            L->index = -1;
            L->cursor = NULL;
        }
    }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, void * x){
    
   // printf("the lsit length is %d",length(L));
    if(length(L)>0){
        Node new = newNode(x);
        new->next = L->head;
        L->head->prev = new;
        L->head = new;
       // L->head->next = new;
       // L->head->next->prev = new;
        L->num_elements += 1; 
        L->index ++;
        //printf("prepending one element\n");   
    }
    else{
        Node new = newNode(x);
        L->head = L->tail = new;
        L->num_elements ++;
        L->index ++;
    }
    
} // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, void * x){
    if(length(L) > 0){
        Node new = newNode(x);
        new->prev = L->tail;  
        L->tail->next = new;
        L->tail = new;
        L->num_elements ++;  
    }
    else{
        Node new = newNode(x);
        L->head = L->tail = new;
        L->num_elements ++;
    }
    //printf("Here is the list after one append operation.\n");
    //printList(stdout, L);
    //printf("\n");
} // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void insertBefore(List L, void * x){
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List Error: calling insertBefore() on empty List.\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling insertBefore() while the cursor is NULL.\n");
    }
    if(L->num_elements > 0 && index(L) > 0){
        Node new = newNode(x);
        
        new->next = L->cursor;
        new->prev = L->cursor->prev;
        L->cursor->prev->next = new;
        L->cursor->prev = new;
        L->num_elements++;
        L->index ++;
        
    }
    if(L->num_elements > 0 && index(L) == 0){
    	Node new = newNode(x);
    	new->next = L->cursor; //or head
    	L->cursor->prev = new;
    	L->head = new;
    	L->num_elements++;
    	L->index ++;
    }
    
} // Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, void * x){
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List Error: calling insertAfter() on empty List.\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling insertAfter() while the cursor is NULL.\n");
    }
    if(L->num_elements > 0 && index(L) >= 0 && L->cursor != L->tail){
        Node new = newNode(x);
        new->next = L->cursor->next;
        new->prev = L->cursor;
        L->cursor->next->prev = new;
        L->cursor->next = new;
        L->num_elements++;
        
    }
    if(L->num_elements > 0 && L->cursor == L->tail){
    	Node new = newNode(x);
    	new->prev = L->tail;
    	L->tail->next = new;
    	L->tail = new;
    	L->num_elements++;
    	
    }
    
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0
void deleteFront(List L){  
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List A Error: calling deleteFront() on an empty List.\n");
        exit(EXIT_FAILURE);
    }
    if(L->num_elements > 1){
        Node curr = L->head;
        if(L->cursor == L->head){
            L->index = -1 ;
            L->cursor = NULL;
        }
        else{
            L->index -=1;
        }
        L->head = L->head->next;
        free(curr);
        curr = NULL;
        L->num_elements-=1;
        
    }
    else{
        Node curr = L->head;
        L->head = L->tail = NULL;
        deleteNode(&curr);
        L->index = -1;
        L->num_elements = 0;
    }
    
} // Delete the front element. Pre: length()>0
void deleteBack(List L){
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List A Error: calling deleteBack() on an empty List.\n");
        exit(EXIT_FAILURE);
    }
    if(L->num_elements > 1){
    	if(L->cursor == L->tail){
    	    Node curr = L->tail;
    	    L->tail = L->tail->prev;
    	    L->num_elements-=1;
    	    deleteNode(&curr);
    	    L->cursor = NULL;
       	    L->index = -1;
       	    L->tail->next = NULL;
   	    }
        else{
    	    Node curr = L->tail;
    	    L->tail = L->tail->prev;
   	        L->num_elements-=1;
    	    deleteNode(&curr);
            L->tail->next = NULL;
    	}
    }
    else{
    	Node curr = L->tail;
    	L->tail = L->head = NULL;
    	deleteNode(&curr);
    	L->index =-1;
    	L->num_elements = 0;
    }
    
    
    
    
    
    
} // Delete the back element. Pre: length()>0
void delete(List L){
    if(L->num_elements <= 0 ){
        fprintf(stderr, "List Error: calling delete() on empty List.\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        fprintf(stderr, "List Error: calling delete() while the cursor is NULL.\n");
    }
    if(L->cursor == L->tail){
    
    	deleteBack(L);
    	L->cursor = NULL;
    	L->index = -1;
    	
    }
    else if (L->cursor == L->head){
    	deleteFront(L);
    	L->cursor = NULL;
    	L->index = -1;
    }
    else{    
    	L->num_elements -=1;
    	Node curr = L->cursor;
    	Node temp = curr->next;
    	curr->next->prev = curr->prev;
    	curr->prev->next = temp;
        //free((curr)->val);
       // free((curr)->index);
    	free(curr);
    	L->cursor = NULL;
    	L->index = -1;
    	curr = NULL;
    }
        //check if list has only one node!!!!!!!!!!!!!!!!!!!!!!!
    
} // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0

