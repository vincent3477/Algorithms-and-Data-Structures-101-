/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA1 
* Lex.c 
* A program for sorting words in alphabetical order using a LIST ADT
*********************************************************************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "List.h"



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
        int numLines = 0;
        //int maxChar = 0;
       // int numChar = 0;
        char * word1 = (char*)malloc(300*sizeof(char));
        while(fgets(word1, 300, inFile)!=NULL){
           /* if(getc(inFile) == '\n'){
                numLines ++;
                if(numChar > maxChar){
                    maxChar = numChar;
                    
                }
                numChar = 0;
                
            }

            numChar ++;
	    */
	    numLines++;
	    
        }
        free(word1);

        char ** inWords = (char**)malloc(numLines* sizeof(char*));
                
        fclose(inFile);

        FILE *inFile_read = fopen(argv[1],"r");
        char * word = (char*)malloc(300*sizeof(char));
        //char * word_cpy = NULL;    
        int iter = 0;


        while(fgets(word, 300, inFile_read)!=NULL && iter < numLines){
            inWords[iter] = (char*)malloc(300*sizeof(char));
            //word_cpy = (char*)malloc(300*sizeof(char));
            strcpy(inWords[iter], word);
            //inWords[iter] = word_cpy;
            
            iter++;

        }

	//free(word_cpy);
        List sortedWords = newList();




        //begin sort
        int i = 1;
        if(numLines-1 >= 1){




            if(strcmp(inWords[i],inWords[i-1]) < 0){ 
                prepend(sortedWords, i-1);
                prepend(sortedWords, i);

            }
            else{
                prepend(sortedWords, i);
                prepend(sortedWords, i-1);
            }

            for( i = 2; i < numLines; i ++){
                int j = i;
                /*while(j > 0){
                    printf("we are looking at %s (in LL) and %s (index %d to inspect)\n",inWords[get(sortedWords)],inWords[j],j);
                    if(strcmp(inWords[get(sortedWords)],inWords[j])<0){
                        moveNext(sortedWords);
                        printf("move next performed\n");
                        
                    }
                    else if(strcmp(inWords[get(sortedWords)],inWords[j])>=0){
                        insertBefore(sortedWords,i);
                        printf("now inserted before the words %s\n",inWords[get(sortedWords)]);
                        break;
                    }

                    else if(index(sortedWords)==length(sortedWords)-1){
                        append(sortedWords,i);
                        break;    
                    }
                    j-=1;
                    printf("\n\n");
                    

                }
                */

                       //strcmp(s1, s2)<0 is true if and only if s1 comes before s2
                       //strcmp(s1, s2)>0 is true if and only if s1 comes after s2
                       //strcmp(s1, s2)==0 is true if and only if s1 is identical to s2
                moveBack(sortedWords);
                while(index(sortedWords)!=-1){
                    //printf("we are looking at %s (in LL) and %s (index %d to inspect)\n",inWords[get(sortedWords)],inWords[j],j);
                    if(strcmp(inWords[get(sortedWords)],inWords[j])>0){ //if the word in sorted LL comes after the word in the unsorted array
                        movePrev(sortedWords);
                        //printf("move prev performed\n");
                        
                    }
                    else if(strcmp(inWords[get(sortedWords)],inWords[j])<=0){ //if the word in sorted LL comes before the word in the unsorted 
                        insertAfter(sortedWords,i);
                       // printf("now inserted after the words %s\n",inWords[get(sortedWords)]);
                        break;
                    } 
                  //  printList(stdout, sortedWords);
                  //  printf("\n");   

                }
                if(index(sortedWords)==-1){
                    prepend(sortedWords,i);
                }
                
            }

        

        }

        //printList(stdout, sortedWords);

        moveFront(sortedWords);     
        while((index(sortedWords) <= length(sortedWords)-1) && (index(sortedWords)>=0)){

            fprintf(outFile, "%s", inWords[get(sortedWords)]);
            moveNext(sortedWords);
        }
       
       
       	int j = 0;
       	
       	free(word);

	while(j < numLines){
       		free(inWords[j]);
       		//printf("free\n");
       		j++;
       	}
       	free(inWords);
       	inWords = NULL;
       	//free(word_cpy);
        freeList(&sortedWords);
        fclose(outFile);
        fclose(inFile_read);
        return 0;
    
    }
    else{
        fprintf(stderr, "You did not provide 2 arguments. Usage: ./Lex <input file> <output file>.\n");
        exit(EXIT_FAILURE);
    }
}
