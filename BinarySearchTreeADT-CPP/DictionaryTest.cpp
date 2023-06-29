/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA7 
* DictionaryTest.cpp 
* Test file for Dictionary.cpp.
*********************************************************************************/ 


#include <iostream>
#include <string>
#include "Dictionary.h"
#include <assert.h>
using namespace std;

int main(){
    string a[] = { "xenopus", "banana", "cat",  "elephant", "fish", "giraffe",  "apple", "iguana", "jaguar",  "octopus","lion", "monkey", "newt",  "rabbit","panda", "quail", "horse", "snake", "tiger", "unicorn", "vulture","dog",  "kangaroo","whale" };
    Dictionary A;
    for (int i = 0; i < 24;i++){
        A.setValue(a[i],i);
    }
    assert(A.size()==24);
    cout <<"The indorder of A is " << endl << A << endl;
    cout <<"Everything should be printed in alphabetical order.\n";

    cout <<"The preorder of A is " << endl << A.pre_string() << endl;


    Dictionary B;
    for (int i = 0; i < 24;i++){
        B.setValue(a[i],i);
    }

    assert(B==A);

    B.setValue("whale",201);
    B.setValue("apple",232);
    B.setValue("iguana",255);

    assert(!(B==A));
    assert(B.size() == 24);
    cout <<"The inorder of B is " << endl << B << endl;

    B.clear();
    assert(B.size()==0);

    //test contains();
    assert(A.contains("apple"));
    assert(A.contains("whale"));
    assert(!(A.contains("door")));

    //test current key
    A.begin();
    A.next();
    A.next();
    A.next();
    assert(A.currentKey() == "dog");
    A.prev();
    assert(A.currentKey() == "cat");
    A.next();
    A.next();
    assert(A.currentVal() == 3);
    A.end();
    assert(A.currentKey() == "xenopus");
    assert(A.currentVal() == 0);
    A.clear();

    //ensuring segfault doesnt happen for small dictionaries.
    A.setValue("item1",1);
    A.setValue("item2",3);
    A.clear();

    cout << "done testing\n";









}