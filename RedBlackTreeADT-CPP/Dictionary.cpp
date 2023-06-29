/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 Pa8 
* Dictionary.cpp 
* Contains the full implementation for the Dictionary ADT with a RBT.
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

    nil = new Node("-1",-1); //this should be a dummy node or increases changes of segfault
    nil->color = 0;
    //std::cout<<"say what??";
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary&D){
    nil = new Node("-1",-1); //this should be a dummy node or increases changes of segfault
    root = nil;
    nil->color = 0;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root,nil);
    
    
}

Dictionary::~Dictionary(){

    if(root != nil){
        //printf("go to post order now!\n");
        postOrderDelete(root);
        //printf("done postordering\n");
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
        if(R->color == 1){
            s+= " (RED)";
        }
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

void Dictionary::BST_insert(Node * N){
    int doNotAdd = 0;
    //std::cout<<"something wrong here\n";
    
    //std::cout<<"nah nothing with new node\n";
    
    Node * M = new Node (N->key, N->val);
    Node * y = nil;
    Node * r = root;
    ///std::cout << "now processing " << n->key << "\n";
    while(r != nil){
        y = r;
        
        int cmp_res = M->key.compare(r->key);

        if(cmp_res < 0){
            r = r->left;
            //std::cout<<"moved left\n";
        }
        else if(cmp_res > 0){
            r = r->right;
            //std::cout<<"moved right\n";
        }
        else {
            r->val = M->val;
            //std::cout<< "equals \n";
            M->parent = y;
            doNotAdd=1;
            M->color = 0;
            delete M;
            break;
        }
    
        M->parent = y;
    }
    
    
    if(!doNotAdd){
        
    	if(y==nil){
            root = M;

            M->parent = nil;
            //this means the tree was empty.
    	}
    	else if (M->key < y->key){
            y->left = M;
    	}
    	else{
            y->right = M;
    	}
        M->left = nil;
        M->right = nil;
        M->color = N->color;
    	num_pairs++;    	
    }
}

void Dictionary::preOrderCopy(Node * R, Node *N){

    if(R->key ==N->key){
    	
    	return;
    }
    

    
    this->BST_insert(R);
    
    preOrderCopy(R->left,N);
    preOrderCopy(R->right,N);
    
}

void Dictionary::postOrderDelete(Node * R){
    if(R != nil){
        //std::cout << "going to delete node " << R->key << endl;
        //std::cout << "left and right " << R->left->key << " and " << R->right->key << endl;
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        //std::cout << "done deleting it\n";
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

void Dictionary::RB_Transplant(Node * u, Node * v){
    if(u->parent == nil){
        root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::LeftRotate(Node * N){
    Node * y = N->right;
    N->right = y->left;
    y->left->parent = N;
    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }
    else if(N == N->parent->left){
        N->parent->left = y;
    }
    else{
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;

}

void Dictionary::RightRotate(Node * N){
    Node * y = N->left;
    N->left = y->right;
    y->right->parent = N;
    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }
    else if(N == N->parent->right ){
        N->parent->right = y;
    }
    else{
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node * z){
    //Assume black is 0 and red is 1.
    
    while( num_pairs > 2 && z->parent->color == 1){

        if(z->parent == z->parent->parent->left){

            Node * y = z->parent->parent->right;
            
            if(y->color == 1){
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->right){
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                RightRotate(z->parent->parent);
            }
        }
        else{

            Node * y = z->parent->parent->left;
            
            //std::cout << "after the node y init statment\n";
            if(y->color == 1){
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;

            }
            else{

                if(z==z->parent->left){
                    z=z->parent;
                    RightRotate(z);
                }

                z->parent->color = 0;
                z->parent->parent->color = 1;
                LeftRotate(z->parent->parent);

            }
        }    
    }
    root->color = 0;
}

void Dictionary::RB_DeleteFixUp(Node * N){
    while(N != root && N->color == 0){
        if(N == N->parent->left){
            Node * w = N->parent->right;
            if(w->color ==1){
                w->color = 0;
                N->parent->color = 1;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if(w->left->color == 0 && w->right->color == 0){
                w->color = 1;
                N = N->parent;
            }
            else{
                if(w->right->color == 0){
                    w->left->color = 0;
                    w->color = 1;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = 0;
                w->right->color = 0;
                LeftRotate(N->parent);
                N = root;

            }
        }
        else{
            Node * w = N->parent->left;
            if(w->color == 1){
                w->color = 0;
                N->parent->color = 1;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if(w->right->color == 0 && w->left->color == 0){
            	w->color = 1;
            	N = N->parent;
            }
            else{
            	if(w->left->color == 0){
            	    w->right->color = 0;
            	    w->color = 1;
            	    LeftRotate(w);
            	    w = N->parent->left;
            	}
                w->color = N->parent->color;
                N->parent->color = 0;
                w->left->color = 0;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 0;
}

void Dictionary::RB_Delete(Node * N){
    Node * y = N;
    Node * x = N; //temp placeholder for Node x.
    int y_orig_color = y->color;
    if(N == current){
    	current = nil;
    }
    if(N->left == nil){
        x = N->right;
        RB_Transplant(N,N->right);
    }
    else if(N->right == nil){
        x = N->left;
        RB_Transplant(N,N->left);
    }
    else{
        y = findMin(N->right);
        y_orig_color = y->color;
        x = y->right;
        if(y->parent == N){
            x->parent = y;
        }
        else{
            RB_Transplant(y,y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N,y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if(y_orig_color == 0){
        RB_DeleteFixUp(x);
    }
    delete N;
    num_pairs--;
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
    Node * M = new Node(k,v);
    //Node * M = e;
    Node * y = nil;
    Node * r = root;
    ///std::cout << "now processing " << n->key << "\n";
    while(r != nil){
        y = r;
        
        int cmp_res = M->key.compare(r->key);

        if(cmp_res < 0){
            r = r->left;
            //std::cout<<"moved left\n";
        }
        else if(cmp_res > 0){
            r = r->right;
            //std::cout<<"moved right\n";
        }
        else {
            r->val = M->val;
            //std::cout<< "equals \n";
            M->parent = y;
            doNotAdd=1;
            M->color = 0;
            delete M;
            break;
        }
    
        M->parent = y;
    }
    
    
    if(!doNotAdd){
        
    	if(y==nil){
            root = M;

            M->parent = nil;
            //this means the tree was empty.
    	}
    	else if (M->key < y->key){
            y->left = M;
    	}
    	else{
            y->right = M;
    	}
        M->left = nil;
        M->right = nil;
        M->color = 1;
    	num_pairs++;
        RB_InsertFixUp(M);

        
    	
    }
}


void Dictionary::remove(keyType k){

    Node * rm = search(root,k);
    if(rm != nil){
        RB_Delete(rm);
    }
    else{
        //delete rm;
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
    //printf("this operator called!\n");
    if(this != &D){
        Dictionary t = D;
        std::swap(root,t.root);
        std::swap(num_pairs, t.num_pairs);
        std::swap(nil,t.nil);

    }
    return *this;
    
}





