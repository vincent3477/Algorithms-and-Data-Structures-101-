/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA2
* GraphTest.c
* Test file for Graph ADT
*********************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include <assert.h>
#include"Graph.h"

int main(void){
    Graph gt = newGraph(50);
    //testing addArc and addEdge with zeros.
    addArc(gt,0,8);
    addArc(gt,8,0);
    addArc(gt,0,0);
    addEdge(gt,0,0);
    addEdge(gt,8,0);
    addEdge(gt,0,8);

    assert(getSize(gt)==0);
    printf("Graph printed below. There should be NO edges\n");
    printGraph(stdout,gt);
    printf("\nend of print statement\n");

    //testing makeNull, so segfaults dont happen
    makeNull(gt);

    //addArc and number of edges in the graph.
    for(int i = 0; i < 45;i++){
        addArc(gt,i,i+3);
    }
    assert(getSize(gt)==44);
    for(int i = 0; i < 45; i+=2){
        addArc(gt,2,i);
        
    }
    for(int i = 44; i > 0; i-=2){
        addArc(gt,2,i);
        //nothing should be added here.
    }
    assert(getSize(gt)==66);
    addEdge(gt,50,10);
    addEdge(gt,10,50);
    assert(getSize(gt)==67);
    addEdge(gt,51,9);
    assert(getSize(gt)==67);
    printf("Graph printed below.\n");
    printGraph(stdout,gt);
    printf("\nend of print statement\n");
    assert(getOrder(gt)==50);
    assert(getSource(gt)==NIL);
    makeNull(gt);
    //assert(getOrder(gt)==0);
    printf("Graph printed below.\n");
    printGraph(stdout,gt);
    printf("Everything should be empty!\n");
    freeGraph(&gt);
    Graph gt2 = newGraph(8);
    addEdge(gt2,1,2);
    addEdge(gt2,1,3);
    addEdge(gt2,1,4);
    addEdge(gt2,2,4);
    addEdge(gt2,2,5);
    addEdge(gt2,3,4);
    addEdge(gt2,3,6);
    addEdge(gt2,4,3);
    addEdge(gt2,4,5);
    addEdge(gt2,4,7);
    addEdge(gt2,6,7);
    addArc(gt2,8,7);
    addArc(gt2,8,5);
    assert(getSize(gt2)==12);
    printGraph(stdout,gt2);
    BFS(gt2,1);
    List path = newList();
    getPath(path,gt2,8);
    List pathModel = newList();
    append(pathModel,-1);
    printf("we try to find the path from 1-8, but 8 is not reachable. There should not be a path.\n");
    printf("Your List: ");
    printList(stdout,path);
    printf("\nwhat it must be: ");
    printList(stdout,pathModel);
    printf("\n");
    clear(path);
    getPath(path,gt2,7);
    printf("we try to find the path from 1-7.\n");
    printf("Your List: ");
    printList(stdout,path);
    printf("\nwhat it must be: ");
    clear(pathModel);
    append(pathModel,1);
    append(pathModel,4);
    append(pathModel,7);
    printList(stdout,pathModel);



    freeGraph(&gt2);

}