/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
#include<iostream>
using namespace std;



void deleteTree(SymNode* root){
    //this need to be modified later
    if(root==NULL){
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root; // symnode destructor will be called // no dynamic memory allocations in symnode //
}

int __getHeight__(SymNode* node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}

int __getBalanceFactor__(SymNode*node){
    if(node == NULL){
        return 0;
    }
    return __getHeight__(node->left) - __getHeight__(node->right);
}

SymNode* __rotateRight__(SymNode*y){
    SymNode* parent_y = y->par;
    SymNode* x = y->left;
    SymNode* temp = x->right;

    x->par = parent_y;
    x->right = y;
    y->par = x;
    y->left = temp;
    if(temp!=NULL){
    temp->par = y;
    }
    //update x height :
    y->height = max(__getHeight__(y->left),__getHeight__(y->right))+1;
    x->height = max(__getHeight__(x->left),__getHeight__(x->right))+1;
    return x;
}

SymNode* __rotateLeft__(SymNode*x){
   SymNode* parent_x = x->par;
   SymNode* y = x->right;
   SymNode* temp = y->left;

    y->par = parent_x;
    y->left = x;
    x->par = y;
    x->right = temp;
    if(temp!=NULL){
        temp->par = x;
    }
    x->height = max(__getHeight__(x->left), __getHeight__(x->right))+1;
    y->height = max(__getHeight__(y->left),__getHeight__(y->right))+1;
    return y;
}

void inorder(SymNode* root){ 
    if(root == NULL){
        return;
    }
    inorder(root->left);
    string parent_key ="null";
    if(root->par!=NULL){
        parent_key= root->par->key;
    }

    string left_child = "null";
    string right_child = "null";
    if(root->left!=NULL){
        left_child = root->left->key;
    }

    if(root->right!=NULL){
        right_child = root->right->key; 
    }

    cout <<"node is " << root->key << " parent is " <<parent_key << " left child is " << left_child  << " right child is "  << right_child  << " height is " << root->height << endl;
    inorder(root->right);
}

void print(SymbolTable* table){
    cout << "============================ size of table is " << table->get_size() << "============================"<<endl;

    SymNode* RootNode = table->get_root();
    inorder(RootNode);
     cout << "==========================================================================="<<endl;

}

SymNode* __insert__(SymNode*node , SymNode* parent, string k, int&size){
    if(node == NULL){
        SymNode* RootNode = new SymNode(k);
        RootNode->par = parent;
        size++;
        return RootNode;
    }

    if(node->key > k){
        node->left = __insert__(node->left,node,k,size);
    }
    else if(node->key < k){
        node->right = __insert__(node->right,node,k,size);
    }


    node->height = max(__getHeight__(node->left),__getHeight__(node->right))+1;

    int BalanceFactor = __getBalanceFactor__(node);
    
    //left left insertion:
    if(BalanceFactor>1 && node->left->key > k ){
        node =__rotateRight__(node);
    }

    //right right insertion:
    else if(BalanceFactor<-1 && node->right->key < k){
       node =__rotateLeft__(node);
    }

    // left right insertion: 
    else if(BalanceFactor >1 && node->left->key < k){
        node->left = __rotateLeft__(node->left);
        node = __rotateRight__(node);
    }

    //right left insertion:
    else if(BalanceFactor<-1 && node->right->key > k){
        node->right = __rotateRight__(node->right);
        node = __rotateLeft__(node);
    }
      return node;
}

SymNode* __getMin__(SymNode* root){
    SymNode* temp = root;
    while(temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

SymNode* __handleDeleteRotations__(SymNode* node){ 
    int BalanceFactor = __getBalanceFactor__(node);
    int LeftBalanceFactor = __getBalanceFactor__(node->left);
    int RightBalanceFactor = __getBalanceFactor__(node->right);
    
    if(BalanceFactor>1 && LeftBalanceFactor==0){
        return __rotateRight__(node);
    }

    else if(BalanceFactor>1 && LeftBalanceFactor>0){
        return __rotateRight__(node);
    }

    else if(BalanceFactor>1 && LeftBalanceFactor<0){
        node->left = __rotateLeft__(node->left);
        return __rotateRight__(node);
    }


    else if(BalanceFactor<-1 && RightBalanceFactor==0){
        return __rotateLeft__(node);
    }

    else if(BalanceFactor<-1 && RightBalanceFactor<0){
        return __rotateLeft__(node);
    }

    else if(BalanceFactor<-1 && RightBalanceFactor>0){
        node->right = __rotateRight__(node->right);
        return __rotateLeft__(node);
    }
    return node;
}

SymNode* __delete__(SymNode* node,string k, int&size){

    if(node == NULL){
        return node;
    }

    if(node->key < k ){
        node->right = __delete__(node->right ,k,size);
    }

    else if(node->key > k ){
        node->left = __delete__(node->left,k,size);
    }

    else{
        //node.key == k :
       
        SymNode* ParentNode= node->par;
        if(node->left == NULL && node->right == NULL){
            
            delete node;
            size--;
            return NULL;
        }

        //single child:
        else if(node->left == NULL && node->right!= NULL){
            SymNode* temp = node->right;
           
            temp->par = ParentNode;
            delete node;
            size--;
            return temp;
            
        }

        else if(node->right == NULL && node->left!=NULL){
            SymNode* temp= node->left;
            temp->par = ParentNode;
            delete node;
            size--;
            return temp;
        }

        //both child:
        else if(node->left!=NULL && node->right!= NULL){
            SymNode* MinKey = __getMin__(node->right);
            node->key = MinKey->key;
            node->address = MinKey->address;
            node->right = __delete__(node->right,MinKey->key,size);
        }
    }

    node->height = max(__getHeight__(node->left),__getHeight__(node->right)) + 1;

    node = __handleDeleteRotations__(node);

    return node;
}

SymbolTable::SymbolTable(){
    size =0;
    root = NULL;
}

void SymbolTable::insert(string k){
    SymNode* parent = NULL;
    root = __insert__(root,parent,k,size);

}

void SymbolTable::remove(string k){
    root = __delete__(root,k,size);
}

int SymbolTable::search(string k){
    SymNode* temp = root;
    while(temp!=NULL){
        if(temp->key ==k ){
            return temp->address;
        }

        else if(temp->key > k){
            temp = temp->left;
        }

        else{
            temp = temp->right;
        }
    }
    return -2; //temp == null // key not found 
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* temp = root;
    while(temp!=NULL){
        if(temp->key == k){
            temp->address = idx;
            return;
        }
        else if(temp->key > k){
            temp = temp->left;
        }

        else{
            temp = temp->right;
        }
    }
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    deleteTree(root);
}

// what are the edge cases: 

int main(){

    SymbolTable* tb = new SymbolTable();
    tb->insert();
    return 0;
}