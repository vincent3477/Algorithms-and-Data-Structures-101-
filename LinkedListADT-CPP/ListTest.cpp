/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA5 
* ListTest.cpp 
* Test file for List.cpp.
*********************************************************************************/ 


#include "List.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <string>

using namespace std;


//things to test
/*

   // Manipulation procedures -------------------------------------------------

 




   // insertAfter()
   // Inserts x after cursor.
   void insertAfter(ListElement x);


 



   // Other Functions ---------------------------------------------------------



*/




int main(){
    List A;
    for(int i = 0; i < 15; i++){
        A.insertBefore(i);
    }
    assert(A.length() == 15);
    assert(A.position()== 15);
    cout << A;
    cout << "\n Should print 0 - 14\n";

    List B = A;
    
    assert(B==A);

    B.movePrev();
    B.movePrev();
    B.movePrev();

    assert(B.position()==12);

    B.eraseAfter();
    B.eraseBefore();

    assert(!(B==A));
    assert(B.length() == 13);
    cout << B;
    cout << "\n should print 0 - 10 + 13 & 14\n";

    assert(B.peekNext() == 13);
    assert(B.peekPrev() == 10);
    assert(B.findNext(1)==-1);
    assert(B.findPrev(1)==1);
    
    B.moveFront();

    for(int i = B.length()-1; i >= 0;i-- ){
        B.setAfter(i);
        B.moveNext();
    }

    cout << B << "\n";
    cout << "Should print from 12 -> 0\n";

    List concat = A.concat(B);

    cout << concat << "\n";
    cout << "should print 0->14 + 12->0\n";

    for(int i = 0; i <= 17;i++){
        concat.moveNext();
    }
    assert(concat.position() == 18);

    concat.cleanup();

    assert(concat.position()==15);
    assert(concat.peekPrev()==14);
    assert(concat.length()==15);

    concat.clear();
    concat.cleanup();
    //making sure no segfaults occur.

    assert(concat.length()==0);
    assert(concat.position()==0);

    A.moveBack();
    A.eraseBefore();
    A.eraseBefore();
    A.eraseBefore();
    assert(A.length()==12);
    assert(A.position()==12);
    assert(A.back()==11);
    A.moveFront();
    A.eraseAfter();
    A.eraseAfter();
    A.eraseAfter();
    assert(A.length()==9);
    assert(A.position()==0);
    assert(A.front()==3);
    cout << A << "\n";
    cout << "should print 3->11\n";

    //time for some extreme cases for cleanup().
    //cleanup w/o duplicate values.
    A.cleanup();
    assert(A.position()==0);
    assert(A.length()==9);

    //clean up with cursor in back.
    A.moveBack();
    A.setBefore(3);
    A.cleanup();
    cout << A << "\n";
    cout << "Should print 3->10\n";
    assert(A.position()==8);
    assert(A.length()==8);
    assert(A.peekPrev()==10);

    //clean up with a small amount of values in the list
    for(int i = 0; i < 6;i++){
        A.eraseBefore();
    }

    A.insertAfter(4);
    cout << A << "\n";
    A.moveFront();
    A.moveNext();
    A.cleanup();


    assert(A.length()==2);
    assert(A.position()==1);
    

    A.setAfter(3);
    A.cleanup();
    assert(A.position()==1);
    assert(A.length()==1);

    A.clear();
    B.clear();
    


    
    


}