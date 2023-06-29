/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA2
* FindPath.c 
* A program to parse a text file to make a graph and find path from different
  sources to destinations.
*********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"
#include <string.h>

int main (int argc, char *argv[]){
    if( argc == 3 ) {
        FILE *inFile;
        FILE *outFile;
        inFile = fopen(argv[1],"r");
        outFile = fopen(argv[2],"w");

        if (inFile == NULL){
            fprintf(stderr, "The in-file name does not exist.");
            exit(EXIT_FAILURE);
        }
        if (outFile == NULL){
            fprintf(stderr, "The out-file name does not exist.");
            exit(EXIT_FAILURE);
        }
        
        //char * graphSize = (char*)malloc(sizeof(char)*500);
        //fgets(graphSize,500,inFile);
        
        //Graph g = newGraph(atoi(graphSize));

        //char * graphAtt = (char*)malloc(sizeof(char)*500);
        //int i = 0;
        //while(i < 500){
        //    graphAtt[i] = '\0';
        //    i++;
        //}
        //char * num1 = (char*)malloc(sizeof(char)*250);
        //char * num2 = (char*)malloc(sizeof(char)*250);
        int j = 0;
        fscanf(inFile,"%d",&j);
        Graph g = newGraph(j);
        //printf("the thing we are inserting is %d\n",j);

        int k = 0;
        int l = 0;

        while(!feof(inFile)){
            fscanf(inFile,"%d %d", &k, &l);
           // printf("the value odf k is %d and k is %d\n",k,l);

            if(k == 0 || l == 0){
                break;
            }
            addEdge(g,k,l);
        }
        printGraph(outFile,g);
        fprintf(outFile,"\n");
        while(!feof(inFile)){
            fscanf(inFile,"%d %d", &k, &l);
            //printf("the things we are looking at include %d\n",k);

            if( k == 0 || l == 0){
                break;
            }

            BFS(g,k); //call bfs starting from k, using that as our source to help guide us to the destination vertex.

            if(getDist(g,l)==-1){
                fprintf(outFile,"The distance from %d to %d is infinity\n", k, l);
            }
            else{
                fprintf(outFile,"The distance from %d to %d is %d\n", k, l, getDist(g,l));
            }


            
            if(getDist(g,l) != -1){
                fprintf(outFile, "A shortest %d-%d path is: ",k,l);
                List path = newList();
                getPath(path, g, l);
                //printf("get path done\n");
                printList(outFile, path);
                fprintf(outFile,"\n\n");
                freeList(&path);
                
            }
            else{
                fprintf(outFile,"No %d-%d path exists\n\n",k,l);
            }

        }
        
        /*while(fgets(graphAtt, 500, inFile)!=NULL && strcmp(graphAtt, "0 0\n") != 0){
            
            int i = 0;
            int j = 0;
            printf("exec\n");
            while(strcmp(&graphAtt[i]," ")!=0 && graphAtt[i] ){
                num1[i] = graphAtt[i];
                i++;
                printf("value oif i is %d\n",i);
                printf("value oif gA is %d\n",graphAtt[i]);
            }
            j = i + 1;
            i = 0;
            
            while(strcmp(&graphAtt[i]," ")!=0 && graphAtt[i]){
                num2[i] = graphAtt[j];
                j++;
                i++;
            }

            if(atoi(num1) == 0 || atoi(num2)== 0){
                printf("zeros detected, terminating first loop now.");
                break;
            }
            
            addEdge(g,atoi(num1),atoi(num2));
            for(int k = 0; k < 250;k ++){
                num1[k] = num2[k] = '\0';
            }
            for(int k = 0; k < 500; k++){
                graphAtt[i] = '\0';
            }
            printf("valu of str 0 0 is %d\n",strcmp(graphAtt, "0 0"));
            int h = 0;
            printf("%s",graphAtt);
            printf("\n");
        }
        
        

        for(int k = 0; k < 250;k++){
                num1[k] = num2[k] = '\0';
            }
        while(fgets(graphAtt, 500, inFile)!=NULL && strcmp(graphAtt, "0 0") != 0){
            int i = 0;
            int j = 0;
            while(strcmp(&graphAtt[i]," ")!=0){
                num1[i] = graphAtt[i];
                i++;
            }
            j = i + 1;
            i = 0;
            while(strcmp(&graphAtt[i]," ")!=0){
                num2[i] = graphAtt[j];
                j++;
                i++;
            }
            BFS(g,atoi(num1));
            fprintf(outFile,"The distance from %d to %d is %d\n", atoi(num1), atoi(num2), getDist(g,atoi(num2)));
            if(getDist(g,atoi(num2)) != -1){
                fprintf(outFile, "The shortest %d-%d path is: ",atoi(num1),atoi(num2));
                List path = newList();
                getPath(path, g, atoi(num2));
                printList(outFile, path);
            }
            else{
                fprintf(outFile,"No %d-%d oath exists",atoi(num1),atoi(num2));
            }
            for(int k = 0; k < 250;k ++){
                num1[k] = num2[k] = '\0';

            }
            
           


        }
    */
    freeGraph(&g);
    fclose(inFile);
    fclose(outFile);
    
    //freeList(&path);
    
        

    }
    else{
        printf("You did not provide 2 arguments. Usage: ./FindPath <infile> <outfile>.");
        exit(EXIT_FAILURE);
    }
}