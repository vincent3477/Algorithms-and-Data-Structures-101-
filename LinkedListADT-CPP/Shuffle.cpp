/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA5 
* Shuffle.cpp 
* Implements a riffle shuffle. Contains the main() program.
*********************************************************************************/ 


#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

List Shuffle(List &d){
    int isOdd = 0;
    if(d.length() % 2 != 0){
        isOdd = 1;
    }
    int lenA1 = d.length() / 2; //lenA1 is the length of the first half of the list.
    int lenA2 = lenA1;
    if(isOdd){ //lenA2 is the length of the second half of the list.
        lenA2 = lenA1  + 1;
    }
    
    //printf("the length of d is %d\n",d.length());
    //printf("the length of lenA1 is %d\n",lenA1);
    //printf("the length of lenA2 is %d\n",lenA2);

    List A;
    A.moveFront();
    d.moveFront();

    //first, append the first half of the elements int
    while(d.position() < lenA1){
        A.insertBefore(d.peekNext()); 
        d.moveNext();
    }

    List B;
    B.moveFront();
    while(d.position()-lenA1 < lenA2){
        B.insertBefore(d.peekNext());
        d.moveNext();
    }
    //std::cout << A;
    //std::cout << "\n";
    //std::cout << B;
    //std::cout << "\n";

    List C;
    B.moveFront();
    A.moveFront();

    while(B.position() < B.length() || A.position() < A.length()){
        
        
        if(B.position() < B.length()){
            C.insertBefore(B.peekNext());
            B.moveNext();
            
        }
        if(A.position() < A.length()){
            C.insertBefore(A.peekNext());
            A.moveNext();
        }
        
    }
    

    return C;
    
    
}

using namespace std;

int main(int argc, char * argv[]){
    if(argc != 2){
        throw std::invalid_argument("You did not enter 1 argument. Usage: Shuffle <int>");
    }


    int numDecks = atoi(argv[1]);
    
    cout << "deck size       shuffle count\n";
    cout << "------------------------------\n";

    int deck =1;
    List d;
    while(deck <= numDecks){
        
        for(int i = 1 ; i <= deck; i++){
            d.insertBefore(i);
        }
        
        int shuffle_count = 1;
        List d_shuffled = Shuffle(d);
        
        while(!(d_shuffled == d)){
            
            d_shuffled = Shuffle(d_shuffled);
            shuffle_count++;
        
        }
       
        if(deck < 10){
            cout << " " << deck << "               " << shuffle_count << "\n";
        }
        else if (deck >= 10 && deck < 100){
            cout << " " << deck << "              " << shuffle_count << "\n";
        }
        else if (deck >= 100 && deck < 1000 ){
            cout << " " << deck << "             " << shuffle_count << "\n";
        }
        d.clear();
        deck++;


    }
    
    


}