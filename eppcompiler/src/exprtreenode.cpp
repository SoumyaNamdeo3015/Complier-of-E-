/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
//Write your code below this line
//pulblic : string type , string id, int num 
ExprTreeNode::ExprTreeNode(){
    type = "";
    id = "";
    num =  0;
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    type = t;
    num = 0;
    left = NULL;
    right = NULL;

    if(type== "VAL"){num =  v; id ="VAL";}
    else if(type == ":="){id = ":=";}
    else if(type== "ADD"){id ="ADD";} 
    else if(type == "SUB"){id ="SUB";}
    else if(type == "MUL"){id ="MUL";}
    else if(type=="DIV"){id = "DIV";}
    else if(type == "MOD"){id = "MOD";}
    else if(type =="del"){id = "del";}
    else if(type == "ret"){id = "ret";}
    else{type = "VAR";id = t;}
}

ExprTreeNode::~ExprTreeNode(){
    left = NULL;
    right = NULL;
    type = "";
    id = "";
    num =  0;
}

