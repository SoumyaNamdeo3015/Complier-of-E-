#include<iostream>
using namespace std;

class Node{

    public:
    Node* left;
    Node* right;
    Node* par;
    string key;

    Node(string k){
        key =k;
        left = NULL;
        right = NULL;
        par = NULL;
    }

    Node(){
        left = NULL;
        right = NULL;
        par = NULL;
    }
};


Node* insert(Node* root, Node*parent,string k){
    if(root == NULL){
        Node* newNode = new Node(k);
        newNode->par = parent;
        return newNode;
    }

    if(root->key > k){
        root->left = insert(root->left,root,k);
    }

    else if(root->key < k ){
        root->right = insert(root->right,root,k);
    }
    return root;
}


void inorder(Node* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    string parent_key ="null";
    if(root->par!=NULL){
        parent_key= root->par->key;
    }
    cout <<"node is " << root->key << " parent is " <<parent_key<< endl;
    inorder(root->right);
}

int main()
{
    Node* root = NULL;
    Node* parent = NULL;
    // root = insert(root,parent,"a5");
    // root = insert(root,parent,"a2");       
    // root = insert(root,parent,"a1");
    // root = insert(root,parent,"a6");
    // root = insert(root,parent,"a3");
    // inorder(root);

    
   
    return 0;

}