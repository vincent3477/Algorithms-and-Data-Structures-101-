/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA5 
* List.cpp 
* Contains implementation for a List ADT using a Doubly Linked List.
*********************************************************************************/ 

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

List::Node::Node(ListElement x){
    data = x;
 
}

List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy; 
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
}

List::List(const List &L){
    //List n;
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor=0;


    this->moveFront();
    Node * c = L.frontDummy->next;
    while(c != L.backDummy){
        this->insertBefore(c->data);
        c = c->next;
    }
}

List::~List(){
    
    
    if(frontDummy != nullptr){
        moveFront();
        while(num_elements > 0){
            eraseAfter();
        }
        delete frontDummy;
        delete backDummy;
    
    }
}


void List::insertBefore(ListElement x){
    Node * n = new Node(x);
    if(length()==0){
        frontDummy->next = n;
        backDummy->prev = n;
        n->next = backDummy;
        n->prev = frontDummy;
        beforeCursor = n;
        num_elements++;
        pos_cursor++;
        
    }
    else{
        beforeCursor->next = n;
        n->prev = beforeCursor;
        afterCursor->prev = n;
        n->next = afterCursor;
        beforeCursor = n;
        num_elements++;
        pos_cursor++;
    }
}

void List::insertAfter(ListElement x){
    Node * n = new Node(x);
    if(length()==0){
        
        frontDummy->next = n;
        backDummy->prev = n;
        afterCursor = n;
        n->next = backDummy;
        n->prev = frontDummy;
        num_elements++;
        
    }
    else{
        n->next = afterCursor;
        n->prev = beforeCursor;
        beforeCursor->next = n;
        afterCursor->prev = n;
        afterCursor = n; //difference.
        num_elements++;
        
    }
}

void List::eraseAfter(){
    if(afterCursor != backDummy && num_elements > 0){
        Node * n = afterCursor;
        beforeCursor->next = afterCursor->next; //problem here
        afterCursor->next->prev = afterCursor->prev;
        afterCursor = afterCursor->next;
        delete n;
        num_elements--;

    }
    else{
         throw std::range_error("Cannot eraseAfter(). You are at the very last element.");
    }
}

void List::eraseBefore(){
    if(beforeCursor != frontDummy && num_elements > 0){
        Node * n = beforeCursor;
        beforeCursor -> prev -> next = afterCursor;        
        afterCursor -> prev = beforeCursor->prev;
        beforeCursor = beforeCursor->prev;
        delete n;
        num_elements--;
        pos_cursor--;
    }
    else{
         throw std::range_error("Cannot eraseBefore(). You are at the very first element.");
    }
}

ListElement List::peekNext()const{
    if(pos_cursor < num_elements){
        return(afterCursor->data);
    }
    else{
        throw std::range_error("Cannot move next. You are are at the very last position.");
    }
}

ListElement List::peekPrev()const{
    if(pos_cursor > 0){
        return(beforeCursor->data);
    }
    else{
        throw std::range_error("Cannot move prev. You are are at the very first position.");
    }
    
}

ListElement List::moveNext(){
    if(pos_cursor >= num_elements){
        throw std::range_error("Cannot move next. You are are at the very last position.");
    }
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev(){
    if(pos_cursor == 0){
        throw std::range_error("Cannot move back. You are at the very first postiion.");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

ListElement List::front()const{
    if(num_elements > 0){
        return(frontDummy -> next -> data);
    }
    else{
        throw std::length_error("Empty list while trying to get the front element.");
    }
}

ListElement List::back()const{
    if(num_elements > 0){
        return(backDummy->prev->data);
    }
    else{
        throw std::length_error("Empty list while trying to get the rear element.");
    }
}

void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor=0;

}

void List::moveBack(){
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
}





void List::setAfter(ListElement x){
    if(pos_cursor < 0 || pos_cursor > num_elements){
        throw std::range_error("List: You are attempting to set an element that is after the last element.");
    }
    //Node * n = new Node(x);
    afterCursor->data = x;
}

void List::setBefore(ListElement x){
    if(pos_cursor < 0 || pos_cursor > num_elements){
        throw std::range_error("List: You are attempting to set an element that is before the first element.");
    }
    beforeCursor->data = x;
}

int List::length() const{
    return(num_elements);

}

int List::position() const{
    return(pos_cursor);
}


int List::findNext(ListElement x){
    while(pos_cursor < num_elements){
        if (afterCursor->data == x){
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    return -1;
}

int List::findPrev(ListElement x){
    while(pos_cursor != 0){
        if(beforeCursor->data == x){
            movePrev();
            return pos_cursor;
            
        }
        movePrev();
    }
    return -1;
    
}

void List::clear(){
    moveFront();
    while(num_elements > 0){
        eraseAfter();
    }
}

void List::cleanup(){
    int passCursor = 0;
    int definitelyPassedCursor = 0;
    Node * unique_val = frontDummy->next;
    Node * check = frontDummy->next;
    while(unique_val != backDummy && unique_val->next != backDummy){
        if(unique_val == afterCursor){
            definitelyPassedCursor = 1;
        }
        check = unique_val->next;
        passCursor = 0;
        while(check != backDummy){
            if(check == afterCursor){
                passCursor = 1;
            }
            if(check->data == unique_val->data){
                Node * del = check;
                if(check == beforeCursor){
                    beforeCursor = beforeCursor->prev;
                    check->prev->next = check->next;
                    check->next->prev = check->prev;
                    check = check->next;
                    num_elements-=1;
                    pos_cursor-=1;
                    delete del;
                }
                else if(check==afterCursor){
                    afterCursor=afterCursor->next;
                    check->prev->next = check->next;
                    check->next->prev = check->prev;
                    check = check->next;
                    num_elements-=1;
                    delete del;
                }
                else{
                    check->prev->next = check->next;
                    check->next->prev = check->prev;
                    check = check->next;
                    num_elements-=1;
                    if(!passCursor && !definitelyPassedCursor){
                        pos_cursor -=1;
                    }
                    delete del;

                }
                
            } 
            else{
                check = check->next; 
            } 
            
        }
        unique_val = unique_val->next;
    }
}

bool List::equals(const List &R)const{
    if(R.num_elements != this->num_elements){
        return false;
    }

    Node * n = this->frontDummy;
    Node * m = R.frontDummy;

    while(n != backDummy){
        if(n->data != m->data){
            return false;
        }
        n = n->next;
        m = m->next;
    }
    return true;
}

List List::concat(const List &L)const{
    List ret;//need to check if any of the lists are empty.
    ret.moveFront();
    Node * n = this->frontDummy->next;
    Node * m = L.frontDummy->next;
    while(n != this->backDummy){
        ret.insertBefore(n->data);
        n = n->next;
    }
    while(m != L.backDummy){
        ret.insertBefore(m->data);
        m = m->next;
    }
    ret.moveFront();
    return ret;


}


std::string List::to_string()const{
    Node * n = frontDummy->next;
    std::string ret = "";
    while(n!=backDummy){
        ret += std::to_string(n->data) + " ";
        n = n->next;
    }
    return ret;


}


std::ostream& operator<<( std::ostream& stream,  const List& L ) {
   return stream << L.List::to_string();
}

bool operator==(const List& A, const List& B){
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this Queue with state of Q, then returns a reference
// to this Queue.
List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}



