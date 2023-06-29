/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 Pa7 
* Dictionary.cpp 
* Contains the full implementation for the Dictionary ADT with a BST.
*********************************************************************************/ 

#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;
Dictionary::Node::Node(keyType x, valType y){
    key = x;
    val = y;
      
}


//makes a new dictionary in the empty state.
Dictionary::Dictionary(){
    //std::cout<<"what??";
    nil = new Node("-1",-1); //this should be a dummy node or increases changes of segfault
    //std::cout<<"say what??";
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary&D){
    nil = new Node("-1",-1); //this should be a dummy node or increases changes of segfault
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root,nil);
    
    
}

Dictionary::~Dictionary(){
   // printf("delete operator called!\n");
    if(root != nil){
        postOrderDelete(root);
    }
    
    delete nil;
    
}


Dictionary::Node * Dictionary::search(Node * R, keyType K)const{
    //std::cout << "looking at " << K << " and " << R->key;
    //std::cout << " the value of is " << R->val <<"\n";
    if(R == nil || K==R->key){
        //std::cout<<"the value to return is " << R->val << "\n";
        return R;
    }
    else if(K<R->key){
        return search(R->left,K);
    }
    else {
        return search(R->right,K);
    }
    
}

void Dictionary::preOrderString(std::string& s, Node *R)const{
    if(R != nil){
        //std::cout << "doing prestring rn\n";
        s+=(R->key);
        s+= "\n";
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

void Dictionary::inOrderString(std::string& s, Node *R)const{
	//std::cout<< "in order called!\n";
	
    if(R != nil){
    	
        //std::cout<< " R not nil\n";
        //std::cout<< "the value of nil key is " << nil->key << "\n";
	//std::cout<< "the value of nil val is " << nil->val << "\n";
	
        //std::cout<< "the value of key is " << R->key << "\n";
	//std::cout<< "the value of val is " << R->val << "\n";
	
        inOrderString(s,R->left);
        s+=(R->key);
        //cout<<"in order in prog\n";
        s+=" : ";
        s+=std::to_string(R->val);
        s+= "\n";
        inOrderString(s,R->right);
    }
}

void Dictionary::preOrderCopy(Node * R, Node *N){

    if(R->key ==N->key){
    	
    	return;
    }
    this->setValue(R->key,R->val);
    
    preOrderCopy(R->left,N);
    preOrderCopy(R->right,N);
    
}

void Dictionary::postOrderDelete(Node * R){
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        num_pairs--;
        delete R;
    }
}

Dictionary::Node * Dictionary::findMax(Node *R){
    if(R != nil){
        while(R->right != nil){
            R = R->right;
            //cout << "value of R key is " << R->key << endl;
        }
    }
    return R;
}

Dictionary::Node * Dictionary::findMin(Node *R){
    if(R != nil){
        
        while(R->left != nil){
            R = R->left;
        }
    }
    return R;
}

Dictionary::Node * Dictionary::findNext(Node * R){
    if (R==nil || R->right == nil){
        return R;
    }
    else{
        R = R->right;
        return R;
    } 
}

Dictionary::Node * Dictionary::findPrev(Node * R){
    if (R==nil || R->left == nil){
        return R;
    }
    else{
        R = R->left;
        return R;
    } 
}

int Dictionary::size() const{
    return num_pairs;
}

bool Dictionary::contains(keyType k) const{
    Node * R = root;
    if(search(R,k) != nil){
        return true;
    }
    else{
        return false;
    }
}

valType& Dictionary::getValue(keyType k) const{
    Node * R = root;
    if(contains(k)){
    	Node * ret = search(R,k);
    	return ret->val;
    }
    else{
    	throw std::logic_error("You are attempting to find something that doesn't exist.\n");
    }
    	
}

bool Dictionary::hasCurrent()const{
    if(current != nil){
        return true;
    }
    else{
        return false;
    }
}

keyType Dictionary::currentKey()const{
    if(hasCurrent()){
        return current->key;
    }
    else{
    	throw std::logic_error("Current is null. Cannot return key.\n");
    }
}

valType& Dictionary::currentVal() const{
    if(hasCurrent()){
        return current->val;
    }
    else{
    	throw std::logic_error("Current is null. Cannot return val.\n");
    }
}

void Dictionary::next(){
    if(hasCurrent()){
        if(current->right != nil){
            current = findMin(current->right);
            return;
        }
        Node * y = current->parent;
        while(y != nil && current == y->right){
            current = y;
            y = y->parent;
        }
        current = y;
        //then current is equal to whatever is next.
    }
    else{
    	throw std::logic_error("Cannot move next. Cursor is null.\n");
    }
   	
}

void Dictionary::prev(){
    if(hasCurrent()){
        if(current->left != nil){
            current = findMax(current->left);
            return;        
        }
        Node * y = current->parent;
        while(y != nil && current == y->left){
            current = y;
            y = y->parent;
        }
        current = y;
    }
    else{
    	throw std::logic_error("Cannot move prev. Cursor is null.\n");
    }
}

void Dictionary::begin(){
    if(num_pairs > 0){
        current = findMin(root->left);
        
        if(current==nil){
	        current = root;
	    }
    }
}

void Dictionary::end(){
    if(num_pairs > 0){
        if(root->right == nil){
            current = root;
        }
        else{
            current = findMax(root->right);
        }
    }
}

void Dictionary::clear(){
    Node * R = root;
    postOrderDelete(R);
    current = nil;
    num_pairs = 0;
    root = nil;
}

void Dictionary::setValue(keyType k, valType v){
    int doNotAdd = 0;
    //std::cout<<"something wrong here\n";
    Node * n = new Node(k,v);
    //std::cout<<"nah nothing with new node\n";
    n->left = nil;
    n->right = nil;
    n->parent = nil;

    Node * y = nil;
    Node * r = root;
    ///std::cout << "now processing " << n->key << "\n";
    while(r != nil){
        y = r;
        
        int cmp_res = n->key.compare(r->key);

        if(cmp_res < 0){
            r = r->left;
            //std::cout<<"moved left\n";
        }
        else if(cmp_res > 0){
            r = r->right;
            //std::cout<<"moved right\n";
        }
        else {
            r->val = n->val;
            //std::cout<< "equals \n";
            n->parent = y;
            doNotAdd=1;
            delete n;
            break;
        }

        n->parent = y;
    }
    //printf("done looping\n");
    
    if(!doNotAdd){
        
    	if(y==nil){
            root = n;
            //this means the tree was empty.
    	}
    	else if (n->key < y->key){
            y->left = n;
    	}
    	else{
            y->right = n;
    	}
    	num_pairs++;
    	
    }
}

void Dictionary::transplant(Node * u, Node * v){
    if(u->parent == nil){
        root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v != nil){
        v->parent = u->parent;
    }
}

void Dictionary::remove(keyType k){

    
    if(contains(k)){
        num_pairs--;
        Node * del = search(root,k);
        if (del == current){
            current = nil;
            //if pointing in current make it nil.
        }
        if(del->left == nil){
            //transplant delete and delete.right;
            transplant(del,del->right);
        }
        else if (del->right == nil){
            //transplant delete and delete.left
            transplant(del,del->left);
        }
        else{
            Node * y_min = findMin(del->right);
            if(y_min->parent != del){
                //transplant y min and y min right child.
                transplant(y_min,y_min->right);
                y_min->right = del->right;
                y_min->right->parent = y_min;
            }
            transplant(del,y_min);
            y_min->left = del->left;
            y_min->left->parent = y_min;
        }
        delete del;
    }
    else{
    	throw std::logic_error("You are attempting to remove a value that doesn't exist\n");
    }
}

std::string Dictionary::to_string()const{
    Node * start = root;
    std::string ret = "";
    inOrderString(ret,start);
    return ret;
}

std::string Dictionary::pre_string()const{
    Node * start = root;
    std::string ret = "";
    preOrderString(ret,start);
    return ret;
}

bool Dictionary::equals(const Dictionary &D)const{
    std::string c = to_string();
    std::string d = D.to_string();
    if (d.compare(c)==0){
        return 1;
    }
    return 0;
}

std::ostream& operator<<( std::ostream& stream, Dictionary &D ){
    return stream << D.to_string();
}


bool operator==(const Dictionary &A, const Dictionary &B){
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary &D){
    //fnuprintf("this operator called!\n");
    if(this != &D){
        Dictionary t = D;
        std::swap(root,t.root);
        std::swap(num_pairs, t.num_pairs);
        std::swap(nil,t.nil);

    }
    return *this;
    
}















