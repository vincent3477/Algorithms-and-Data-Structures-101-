/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA4 
* Matrix.c 
* Implementation for a Matrix ADT
*********************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj * Entry;
typedef struct EntryObj {
    double val;
    int col;
}EntryObj;


typedef struct MatrixObj {
    List * row;
    Entry entry;
    int nnz;
    int num_rows;
}MatrixObj;

Entry newEntry(double val, int col){
    Entry n = malloc(sizeof(EntryObj));
    n->val = val;
    n->col = col;
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

Matrix newMatrix(int n){
    Matrix m = malloc(sizeof(MatrixObj));
    m->num_rows = n;   
    m->row = (List*)calloc(n+1,sizeof(List));
    m->nnz = 0;
    for(int i = 0; i < n+1; i++){
        m->row[i] = newList();
    }
    return m;

}

void freeMatrix(Matrix *pM){
    if((*pM)!=NULL && pM != NULL){
        for(int i = 0; i <= (*pM)->num_rows; i++){
           moveFront((*pM)->row[i]);
           while(index((*pM)->row[i]) >=0){
                Entry del = get((*pM)->row[i]);
                set((*pM)->row[i],NULL);
                deleteEntry(&del);
                moveNext((*pM)->row[i]);
                //delete((*pM)->row[i]);
           }
        }
        for(int i = 0; i <= (*pM)->num_rows; i++){
            freeList(&(*pM)->row[i]);
        }
        free((*pM)->row);
        free(*pM);
        (*pM) = NULL;
    }
}

int size(Matrix M){
    
    return M->num_rows ;
}

int NNZ(Matrix M){
    return M->nnz;
}

int equals(Matrix A, Matrix B){
    //int non_zero_elements = 0;
    if(size(A) != size(B)){
        return 0;
    }
    for(int i = 1; i <= A->num_rows;i++){
        if(length(A->row[i]) != length(B->row[i])){
            return 0;
        }
        moveFront(A->row[i]);
        moveFront(B->row[i]);
        while(index(A->row[i])!=-1 && index(B->row[i])!=-1){
            Entry a_element = get(A->row[i]);
            Entry b_element = get(B->row[i]);
            if((a_element->col != b_element->col) || (a_element->val != b_element->val)){

                return 0;
            }
            moveNext(A->row[i]);
            moveNext(B->row[i]);
        }
    }
    return 1;
}

void makeZero(Matrix M){
    M->nnz=0; 
    if(M != NULL){
        for(int i = 1 ; i <= M->num_rows;i++){
            moveFront(M->row[i]);
            while(index(M->row[i])!=-1 ){
                Entry d = get(M->row[i]);
                set(M->row[i],NULL);
                deleteEntry(&d);
                moveNext(M->row[i]);
            }
        }
        for(int i = 0 ; i <= M->num_rows;i++){
            
           clear(M->row[i]);
        }
    }
}

void changeEntry(Matrix M, int i, int j, double x){
    
    if(j < 1 || j > size(M)){
        printf("Could not change an entry. Your specified column, being %d, is out of bounds.\n",j);
        exit(EXIT_FAILURE);
    }
    if(i < 1 || i > size(M)){
        printf("Could not change an entry. Your specified row, being %d, is out of bounds.\n",i);
        exit(EXIT_FAILURE);
    }

    if(x==0){
        
        moveFront(M->row[i]);
        while(index(M->row[i])>=0){
            Entry d = get(M->row[i]);
            if ( d->col == j){
                M->nnz-=1;
                set(M->row[i],NULL);
                deleteEntry(&d);
                delete(M->row[i]);
                break;
            }
            moveNext(M->row[i]); 
        }
        
    }
    else{
        int insDone = 0;
        //i is row number
        //j is column number
        if(length(M->row[i])==0){
            Entry n = newEntry(x,j);
            append(M->row[i],n);
            M->nnz++;
        }
        else{
            moveFront(M->row[i]);
            Entry entrySet = get(M->row[i]);
    
            while(index(M->row[i])!=-1){
                entrySet = get(M->row[i]);
                if(j == entrySet->col){
                    //entrySet->val = x;
                    set(M->row[i],NULL);
                    deleteEntry(&entrySet);
                    Entry newSet = newEntry(x,j);
                    set(M->row[i],newSet);
                    
                    insDone = 1;
                    break;
                }
            
                else if(j > entrySet->col){
                    moveNext(M->row[i]);
                    
                }
                else if(j < entrySet->col){
                    //entrySet->col = j;
                    //entrySet->val = x;
                    Entry newSet = newEntry(x,j);
                    insertBefore(M->row[i],newSet);
                    M->nnz++;
                    insDone = 1;
                    
                    break;
                }
            }
            if(!insDone){
                Entry newSet = newEntry(x,j);
                append(M->row[i],newSet);
                
                M->nnz++;
            }
            
            
        }
    }
}


Matrix copy(Matrix A){
    Matrix cpy = newMatrix(size(A));
    for(int i = 0; i < size(A);i++){
        moveFront(A->row[i]);
        while(index(A->row[i]) >= 0){
            Entry e = get(A->row[i]);
            Entry e_new = newEntry(e->val,e->col);
            append(cpy->row[i],e_new);
            cpy->nnz++;
            moveNext(A->row[i]);
            }
    }
    return cpy;
}

Matrix transpose(Matrix A){
    Matrix aT = newMatrix(size(A));
    for(int i = 1; i <= size(A);i++){
        moveFront(A->row[i]);
        while(index(A->row[i]) >= 0){
            Entry entry = get(A->row[i]);
            changeEntry(aT,entry->col,i,entry->val);
            moveNext(A->row[i]);
        }
    }
    return aT;

}
Matrix scalarMult(double x, Matrix A){
    Matrix aSM = newMatrix(size(A));
    for(int i = 1; i <= size(A); i++){
        moveFront(A->row[i]);
        while(index(A->row[i])>=0){
            Entry entry = get(A->row[i]);
            double prod = x * entry->val;
            changeEntry(aSM,i,entry->col,prod);
            moveNext(A->row[i]);
        }
    }
    return aSM;
}


Matrix sum(Matrix A, Matrix B){
    if(size(A) != size(B)){
        printf("Sum could not be done. Size of A and size of B do not match.\n");
        exit(EXIT_FAILURE);
    }
    Matrix addition = newMatrix(size(A));
    // populate the list if one of the matrices respective rows is empty
    for(int i = 1; i <= size(A);i++){
        if(length(A->row[i])!=0){
            moveFront(A->row[i]);
            while(index(A->row[i]) >= 0){
                Entry a = get(A->row[i]);
                Entry aCpy = newEntry(a->val,a->col);
                append(addition->row[i],aCpy);
                addition->nnz += 1;
                moveNext(A->row[i]);
            }
        }
    }
    

    //printMatrix(stdout,addition);
    //printf("the print above is the addition populated with a\n");
    for(int i = 1;i <= size(B);i++){
        if(length(B->row[i])!=0){
            moveFront(B->row[i]);
            while(index(B->row[i])>=0){ //replace this loop, with a for. We have to affix each and every element and check each and every element with the multiplciation.
                                        //the value in a specific entry in teh matrix does not determine whether its a zero or not. 
                moveFront(addition->row[i]);
                Entry b = get(B->row[i]);
                //Entry add = get(addition->row[i]);
                int insDone = 0;
                while(index(addition->row[i])>=0){
                    Entry add = get(addition->row[i]);
                    
                    if(b->col == add->col){
                        if(add->val + b->val == 0){
                            set(addition->row[i],NULL);
                            deleteEntry(&add);
                            delete(addition->row[i]);
                            addition->nnz-=1;
                            insDone = 1;
                            break;
                        }
                        else{
                            Entry bCpy = newEntry(b->val + add->val,b->col);
                            deleteEntry(&add);
                            set(addition->row[i],bCpy);
                            insDone = 1;
                            break;
                        }

                        
                    }
                    else if(b->col > add->col){
                        moveNext(addition->row[i]);
                        
                    }
                    
                    else if(b->col < add->col){
                        Entry bCpy = newEntry(b->val,b->col);
                        insertBefore(addition->row[i],bCpy);
                        addition->nnz++;
                        insDone = 1;
                        break;
                    }
                }
                if(!insDone){
                    Entry bCpy = newEntry(b->val,b->col);
                    append(addition->row[i],bCpy);
                    addition->nnz++;
                }
                
                moveNext(B->row[i]);
            }
            //prepend htere.
        }
    }
    return addition;
    

}
Matrix diff(Matrix A, Matrix B){
    if(size(A) != size(B)){
        printf("Diff could not be done. Size of A and size of B do not match.\n");
        exit(EXIT_FAILURE);
    }
    Matrix addition = newMatrix(size(A));
    // populate the list if one of the matrices respective rows is empty
    for(int i = 1; i <= size(A);i++){
        if(length(A->row[i])!=0){
            moveFront(A->row[i]);
            while(index(A->row[i]) >= 0){
                Entry a = get(A->row[i]);
                Entry aCpy = newEntry(a->val,a->col);
                append(addition->row[i],aCpy);
                addition->nnz += 1;
                moveNext(A->row[i]);
            }
        }
    }

    //printMatrix(stdout,addition);
    //printf("the print above is the addition populated with a\n");
   
    for(int i = 1;i <= size(B);i++){
        if(length(B->row[i])!=0){
            moveFront(B->row[i]);
            
            while(index(B->row[i])>=0){
                moveFront(addition->row[i]);
                Entry b = get(B->row[i]);
                
                int insDone = 0;
                while(index(addition->row[i])>=0){
                    Entry add = get(addition->row[i]);
                    if(b->col == add->col){

                        if(add->val - b->val == 0){
                            set(addition->row[i],NULL);
                            deleteEntry(&add);
                            delete(addition->row[i]);
                            addition->nnz--;
                            insDone = 1;
                            break;
                        }
                        else{
                            Entry bCpy = newEntry(add->val - b->val,b->col);
                            deleteEntry(&add);
                            set(addition->row[i],bCpy);
                            insDone = 1; 
                            break;
                        }

                        
                    }
                    else if(b->col > add->col){
                        moveNext(addition->row[i]);
                        
                    }
                    
                    else if(b->col < add->col){
                        Entry bCpy = newEntry(-b->val,b->col);
                        insertBefore(addition->row[i],bCpy);
                        addition->nnz+=1;
                        insDone = 1;
                        break;
                    }
                }
                if(!insDone){
                    Entry bCpy = newEntry(-b->val,b->col);
                    append(addition->row[i],bCpy);
                    addition->nnz++;
                }
                
                moveNext(B->row[i]);
                
                
            }
            //prepend htere.
        }
    }
    return addition;
    

}

double dot_product(Matrix A, Matrix B, int a_row, int b_row){
    moveFront(A->row[a_row]);
    double result = 0;
    while(index(A->row[a_row])>=0){
        Entry a = get(A->row[a_row]);
        moveFront(B->row[b_row]);
        while(index(B->row[b_row])>=0){
               
            Entry b = get(B->row[b_row]);
            if(b->col == a->col){
                result += (b->val * a->val);
            }
            moveNext(B->row[b_row]);

        }
        moveNext(A->row[a_row]);
    }
    return result;
}

Matrix product(Matrix A, Matrix B){
    if(size(A) != size(B)){
        printf("Product could not be done. Size of A and size of B do not match.\n");
        exit(EXIT_FAILURE);
    }
    Matrix prod = newMatrix(size(A));

    /*
    //loop through a, then loop through row of b then get the addition
    for(int i = 1; i <= size(B);i++){
        //first step, loop through the first row, then lopp through column in second matrix
        moveFront(get(prod->row[i]));
        while(index(prod->row[i])>=0){
            moveFront(B->row[i]);
            while(index(B->row[i])>=0){ // for each row in B
                for(int i = 1; i <= size(B);i++){ //for each col in B
                    Entry b_col_row = get(B->row[i]); //col matches row.
                    moveFront(prod->row[b_col_row->col]); //remember that this is for A.
                    while(index(prod->row[b_col_row->col])>=0){//for each col in A
                        Entry a_col_row = get(prod->row[b_col_row->col])
                        if(a_col_row->col == i){
                            Entry addElem = newEntry()
                            
                        }
                    }
                }
            }
            //the rows in the second matrix HAVE TO MATCH the columns in the first matrix, then ADD.
            //otherwise if they do not match, then DO NOT ADD because they multply by zero.


        }

    }
    */
    int sizeProd = size(prod);
    Matrix b_Transposed = transpose(B);
    for(int i = 1 ; i <= sizeProd;i++){
        for(int j = 1; j <= sizeProd;j++){
            //printf("i = %d\n",i);
            //printf("j = %d\n",j);
            //printf("size is %d\n",size(prod));
            if(length(A->row[i])>0 && length(b_Transposed->row[j])>0){
                double elem = dot_product(A,b_Transposed,i,j);
                if(elem != 0.0){
                    Entry elem_entry = newEntry(elem,j);
                    append(prod->row[i],elem_entry);
                    prod->nnz++;
                }
                
            }
            
            
        }
        

    }
    freeMatrix(&b_Transposed);
    return prod;

}

void printMatrix(FILE* out, Matrix M){
    
    for(int i = 1; i <= size(M);i++){
        
        if(length(M->row[i])!=0){
            fprintf(out,"%d: ", i);
            moveFront(M->row[i]);
            while(index(M->row[i])!=-1){
                Entry element = get(M->row[i]);
                fprintf(out,"(%d, %.1f) ",element->col,element->val);
                moveNext(M->row[i]);
            }
            fprintf(out,"\n");
        }
    }
}





