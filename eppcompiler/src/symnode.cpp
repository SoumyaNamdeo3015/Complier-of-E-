/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
//Write your code below this line
// #include<iostream>
// using namespace std;

SymNode::SymNode(){
    left = NULL;
    right = NULL;
    par = NULL;
    height = 1;
}

SymNode::SymNode(string k){
    key =k;
    left = NULL;
    right = NULL;
    par = NULL;
    height = 1;
}

SymNode* SymNode::LeftLeftRotation(){
    return NULL;
}

SymNode* SymNode::RightRightRotation(){
    return NULL;
}

SymNode* SymNode::LeftRightRotation(){
    return NULL;
}

SymNode* SymNode::RightLeftRotation(){
    return NULL;
}

SymNode::~SymNode(){
    // deletion needs to me modified later 
    address =-1;
    height = 0;
    key ="";
}

