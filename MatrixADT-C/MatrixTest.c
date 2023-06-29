/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA4 
* MatrixTest.c 
* Contains test for Matrix.c
*********************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include"Matrix.h"

int main(){
    Matrix A = newMatrix(9);
    Matrix B = newMatrix(9);
    changeEntry(A,1,1,1);
    changeEntry(A,1,2,2);
    changeEntry(A,1,3,3);
    changeEntry(A,2,1,4);
    changeEntry(A,2,2,5);
    changeEntry(A,2,3,6);
    changeEntry(A,3,1,7);
    changeEntry(A,3,2,8);
    changeEntry(A,3,3,9);
    assert(NNZ(A)==9);
    assert(size(A)==9);
    assert(size(B)==9);
    assert(NNZ(B)==0);
    printMatrix(stdout,A);
    printf("should print \n1 2 3\n4 5 6\n7 8 9\n");
    B=copy(A);
    assert(equals(A,B));
    changeEntry(B,3,3,0);
    assert(!equals(A,B));
    printMatrix(stdout,B);
    printf("B should print \n1 2 3\n4 5 6\n7 8\n");
    changeEntry(A,1,1,0);
    changeEntry(A,1,2,0);
    changeEntry(A,2,1,0);
    changeEntry(A,2,2,-4);
    printMatrix(stdout,A);
    Matrix C = sum(A,B);
    assert(NNZ(C)==9);
    printMatrix(stdout,C);
    printf("The sum should print \n1 2 6\n4 1 12\n14 16 9\n");
    makeZero(A);
    makeZero(B);
    printMatrix(stdout,A);
    printf("\nprint statement initiated for Matrix A. nothing should be printed above.\n");
    changeEntry(A,1,1,0);
    changeEntry(A,1,2,0);
    changeEntry(A,1,3,0);
    changeEntry(A,2,1,5);
    changeEntry(A,2,2,2);
    changeEntry(A,2,3,1);
    changeEntry(A,3,1,4);
    changeEntry(A,3,2,2);
    changeEntry(A,3,3,5);

    changeEntry(B,1,1,0);
    changeEntry(B,1,2,1);
    changeEntry(B,1,3,2);
    changeEntry(B,2,1,3);
    changeEntry(B,2,2,0);
    changeEntry(B,2,3,4);
    changeEntry(B,3,1,5);
    changeEntry(B,3,2,7);
    changeEntry(B,3,3,7);

    Matrix D = product(A,B);
    printMatrix(stdout,D);
    printf("The prod should print \n0 0 0\n11 12 25\n31 39 51\n");

    Matrix E = scalarMult(0,A);
    printMatrix(stdout,E);
    printf("the scalar mult should print nothing\n");
    

    Matrix F = diff(E,D);
    printMatrix(stdout,F);
    printf("the diff of E and D should print \n-11 -12 -25\n-31 -39 -51\n");
    assert(NNZ(F)==6);

    Matrix G = transpose(F);
    printMatrix(stdout,G);
    printf("the transpose should print \n0 -11 -21\n0 -12 -39\n0 -25 -51\n");









    







    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);

    



}


