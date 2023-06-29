/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA4 
* Sparse.c 
* Contains the main implemenation to manipulate a matrix.
*********************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Matrix.h"

int main (int argc, char *argv[]){
    if( argc == 3 ) {
        FILE *inFile;
        FILE *outFile;
        //int numLines[3] ={};
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
       
        //a = num NONZERO lines for matrix a
        //b = num NONZERO lines for matrix b
        //n = the dimensions of BOTH matrices.
        //format a b n.
        int nonzero_a = 0;
        int nonzero_b = 0;
        int matrix_dim = 0;
        fscanf(inFile,"%d %d %d",&matrix_dim,&nonzero_a,&nonzero_b);


        Matrix A = newMatrix(matrix_dim);
        int linesRead = 0;
        int row;
        int column;
        double value;
        while(!feof(inFile) &&  linesRead < nonzero_a){
            linesRead++;
            fscanf(inFile,"%d %d %lf",&row,&column,&value);
            changeEntry(A,row,column,value);

        }
        linesRead = 0;
        Matrix B = newMatrix(matrix_dim);
        while(!feof(inFile) && linesRead < nonzero_b){
            linesRead++;
            fscanf(inFile,"%d %d %lf",&row,&column,&value);
            changeEntry(B,row,column,value);
            
        }

        //start printing stuff to the file.
        fprintf(outFile,"A has %d non-zero entries:\n",nonzero_a);
        printMatrix(outFile,A);
        fprintf(outFile,"\n");

        fprintf(outFile,"B has %d non-zero entries:\n",nonzero_b);
        printMatrix(outFile,B);
        fprintf(outFile,"\n");
        printf("got all the entries\n");

        fprintf(outFile,"(1.5)*A =\n");
        Matrix a_scalared = scalarMult( 1.5,  A);
        printMatrix(outFile, a_scalared);
        fprintf(outFile,"\n");
        printf("scalar mult done\n");

        fprintf(outFile,"A+B =\n");
        Matrix sum_ab = sum(A,B);
        printMatrix(outFile, sum_ab);
        fprintf(outFile,"\n");
        printf("A+B done\n");

        fprintf(outFile,"A+A =\n");
        Matrix sum_aa = sum(A,A);
        printMatrix(outFile, sum_aa);
        fprintf(outFile,"\n");
        printf("A+A done\n");

        fprintf(outFile,"B-A =\n");
        Matrix diff_ba = diff(B,A);
        printMatrix(outFile,diff_ba);
        fprintf(outFile,"\n");
        printf("B-A done\n");

        fprintf(outFile,"A-A =\n");
        Matrix diff_aa = diff(A,A);
        printMatrix(outFile,diff_aa);
        fprintf(outFile,"\n");
        printf("A-A done\n");

        fprintf(outFile,"Transpose(A) =\n");
        Matrix a_transposed = transpose(A);
        printMatrix(outFile, a_transposed);
        fprintf(outFile,"\n");
        printf("TA done\n");

        fprintf(outFile,"A*B =\n");
        Matrix prod_ab = product(A,B);
        printMatrix(outFile,prod_ab);
        fprintf(outFile,"\n");
        printf("AxB done\n");

        fprintf(outFile,"B*B =\n");
        Matrix prod_bb = product(B,B);
        printMatrix(outFile, prod_bb);
        printf("BxB done\n");

        freeMatrix(&A);
        freeMatrix(&B);
        freeMatrix(&a_scalared);
        freeMatrix(&sum_ab);
        freeMatrix(&sum_aa);
        freeMatrix(&diff_ba);
        freeMatrix(&diff_aa);
        freeMatrix(&a_transposed);
        freeMatrix(&prod_ab);
        freeMatrix(&prod_bb);
        fclose(outFile);
        fclose(inFile);
        return 0;
    }
    else{
        fprintf(stderr,"You did not specify two files.");
        exit(EXIT_FAILURE);
        
    }
}


        
