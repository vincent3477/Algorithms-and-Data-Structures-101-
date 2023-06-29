/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA2
* Graph.c 
* Contains the full implementation for a Graph ADT
*********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj {
    List * listArr;
    int * color; //0 = white, 1 = grey, 2 = black
    int * parent;
    int * distance; 
    int numVertices; 
    int numEdges;
    int vertexIndex; //this is the most recently used vertex when BGS was called.

}GraphObj;


Graph newGraph(int n){
    Graph g = malloc(sizeof(GraphObj));
    g->numVertices = n;
    g->numEdges = 0;
    g->vertexIndex = NIL;
    g->listArr = (List*)calloc(n+1,sizeof(List));
    for (int i = 0 ; i < n+1; i++){
        g->listArr[i] = newList();
    }
    g->color = (int*)calloc(n+1,sizeof(int));
    g->parent = (int*)calloc(n+1,sizeof(int));
    g->distance = (int*)calloc(n+1,sizeof(int));
    
    return g;
}
void freeGraph(Graph *pG){
    if(pG != NULL && *pG != NULL){
        if((*pG)->listArr!= NULL){
            for(int i = 0 ; i <= (*pG)->numVertices;i ++){
                if((*pG)->listArr[i] != NULL){
                    freeList(&(*pG)->listArr[i]);
                }
            }
        free((*pG)->listArr);
        (*pG)->listArr = NULL;
        }
    
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free(*pG);
    
    *pG = NULL;
    }
}
/*** Access functions ***/
int getOrder(Graph G){
    //this function returns the number of vertices.
    return G->numVertices;
}
int getSize(Graph G){
    //this function returns the number of edges.
    return G->numEdges;
}
int getSource(Graph G){
    if(G->vertexIndex != -1){
        return G->vertexIndex;
    }
    else{
        return NIL;
    }
}
int getParent(Graph G, int u){
    if(G->vertexIndex != -1){
        return G->parent[u];
    }
    else{
        return NIL;
    }
}
int getDist(Graph G, int u){
    if(G->vertexIndex != -1){
        return G->distance[u];
    }
    else{
        return INF;
    }
}
void getPath(List L, Graph G, int u){
    // this will apend to List L, the vertices of a shortest path in G to the the source
    //  in this case u is VERY NOT THE SOURCE.
    
    //printf("\n");
    if(G->vertexIndex != -1){
        if(u == G->vertexIndex){
            append(L,u); // we want to print the source here.
        //printf("appending %d was called\n",u);
        }
        else if (G->parent[u] == -1){
            append(L, -1);
            //printf("something was not found???\n");
        }
        else{
            //printf("recurson happens here with parent of u being %d\n",G->parent[u]);
             //we want to priint the destination here
            getPath(L,G,G->parent[u]);
            append(L,u);
            
        }
        
    }
    

    
    
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    for(int i = 0; i < getOrder(G)+1; i++){
        if(G->listArr[i]!=NULL){
            clear(G->listArr[i]);
        }
    }
    G->numEdges = 0;

}
void addEdge(Graph G, int u, int v){
    //this function can only incremment number of edges once.
    int found = 0;
    int insDone = 0;
    if(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)){
        if(G->listArr[u] != NULL){
            if(length(G->listArr[u]) < 1){
                append(G->listArr[u],v);
                //G->numEdges++;
                insDone = 1;
            }
            else{
                moveFront(G->listArr[u]);
                while(index(G->listArr[u]) < length(G->listArr[u]) && index(G->listArr[u])>=0){
                    if(get(G->listArr[u]) == v){
                        found = 1;
                        break;
                    }
                    if(get(G->listArr[u]) < v){
                        moveNext(G->listArr[u]);
                    }
                    else if(get(G->listArr[u]) > v){
                        insertBefore(G->listArr[u],v);
                        //G->numEdges++;
                        insDone = 1;
                        break;
                    }
                                
                }
                if(!found && !insDone){
                    append(G->listArr[u],v);
                    //G->numEdges++;
                    insDone = 1;
                    //printf("append done for %d and %d\n",u,v);

                    
                }
            }
            
            
            
        }
        if(G->listArr[v] != NULL){
            found = 0;
            insDone = 0;
            if(length(G->listArr[v]) < 1){
                append(G->listArr[v],u);
                //if(!insDone){
                //    G->numEdges++;
                //}
                //G->numEdges++;
                insDone = 1;
            }
            else{
                moveFront(G->listArr[v]);
                while(index(G->listArr[v]) < length(G->listArr[v]) && index(G->listArr[v])>=0){
                
                    if(get(G->listArr[v]) == u){
                        found = 1;
                        break;
                    }
                    if(get(G->listArr[v]) < u){
                        moveNext(G->listArr[v]);
                    }
                    else if(get(G->listArr[v]) > u){
                        insertBefore(G->listArr[v],u);
                        //if(!insDone){
                        //    G->numEdges++;
                        //}
                        insDone = 1;
                        break;
                    }
                                
                }
                if(!found && !insDone){
                    append(G->listArr[v],u);
                    //G->numEdges++;
                    insDone = 1;
                }
            }
            
            
            
        }
        if(insDone){
            G->numEdges++;
        }
    }
    
    
}
void addArc(Graph G, int u, int v){
    int found = 0;
    int insDone = 0;
    if(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)){
        if(G->listArr[u] != NULL){
            if(length(G->listArr[u]) < 1){
                append(G->listArr[u],v);
                insDone = 1;
            }
            else{
                moveFront(G->listArr[u]);
                while(index(G->listArr[u]) < length(G->listArr[u]) && index(G->listArr[u])>=0){
                    if(get(G->listArr[u]) == v){
                        found = 1;
                        break;
                    }
                    if(get(G->listArr[u]) < v){
                        moveNext(G->listArr[u]);
                    }
                    else if(get(G->listArr[u]) > v){
                        insertBefore(G->listArr[u],v);
                        insDone = 1;
                        break;
                    }
                                
                }
                if(!found && !insDone){
                    append(G->listArr[u],v);
                    //G->numEdges++;
                    insDone = 1;
                    
                }
            }
        }
        if(insDone){
            G->numEdges++;
        }
    }
}

void BFS(Graph G, int s){
    
    if(s > G->numVertices || s <= 0){
        exit(EXIT_FAILURE);
        
    }
    G->vertexIndex = s;
    for(int i = 1 ; i <= getOrder(G);i++){
        G->color[i] = 0;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = 1;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    
    List queue = newList();
    append(queue, s);
    while(length(queue)!=0){
        int x = front(queue);
        deleteFront(queue);
        
        /*for(int j = 1 ; j < G->numVertices; j++){
            if(G->color[j] == 'w'){
                G->color[j] = 'g';
                G->distance[j] = G->distance[x]+1;
                G->parent[j] = x;
                prepend(queue,j);
            }
        }
        */
        //printf("the value of x is %d\n",x);
        //printList(stdout,G->listArr[x]);
        //printf("dude\n");
        
        if(length(G->listArr[x])!=0){
            moveFront(G->listArr[x]);
            int i = get(G->listArr[x]);
            //printf("the length fo the the lsit is %d while the index is %d\n", length(G->listArr[x]),index(G->listArr[x]));
            //printf("the index of the lsit is %d", index(G->listArr[x]));
            while(index(G->listArr[x]) < length(G->listArr[x]) && index(G->listArr[x])>=0){
            //printf("the index is %d\n",index(G->listArr[x]));

                i = get(G->listArr[x]);
                if(G->color[i]==0){
                    G->color[i] = 1;
                    G->distance[i] = G->distance[x]+1;
                    G->parent[i] = x;
                    append(queue, i);
                }

                moveNext(G->listArr[x]);
                // i = get(G->listArr[x]);
            
            }
        }

        
        G->color[x] = 2;
        //printf("the dist is ");
        //for(int l = 0; l < getOrder(G);l++){
        //    printf("%d ",G->distance[l]);
        //}
        //printf("\n");
        
    }
    freeList(&queue);



}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    for(int i = 1; i <= G->numVertices;i++){
        fprintf(out, "%d: ", i);
        printList(out, G->listArr[i]);
        fprintf(out,"\n");       
    }
}





