/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
//Write your code below this line
#include<iostream>

bool isOperator(string OperatorString){
    if(OperatorString=="+" || OperatorString =="-" || OperatorString == "*" ||  OperatorString=="/" || OperatorString =="%"){
        return true;
    }
    return false;
}

int convertToNumber(string TokenString){
    int num = stoi(TokenString);
    return num;
}

bool isNumber(string TokenString){
    char TokenChar = TokenString[0];
    int AscciValue  = TokenChar;
    if(AscciValue>=48 && AscciValue<=57){
        return true;
    }
    return false;
}

ExprTreeNode* createNode(string TokenString){
    ExprTreeNode* NewNode;
    if(TokenString== "+"){NewNode = new ExprTreeNode("ADD",0);}

    else if(TokenString =="-"){NewNode = new ExprTreeNode("SUB",0);}

    else if(TokenString == "*"){NewNode = new ExprTreeNode("MUL",0);}

    else if(TokenString == "/"){NewNode = new ExprTreeNode("DIV",0);}

    else if(TokenString == "%"){NewNode = new ExprTreeNode("MOD",0);}

    else if(TokenString =="del"){NewNode = new ExprTreeNode("del",0);}

    else if(TokenString =="ret"){NewNode = new ExprTreeNode("ret",0);}

    else if(TokenString == ":="){NewNode = new ExprTreeNode(":=",0);}

    else if(isNumber(TokenString)){
        int v = convertToNumber(TokenString);
        NewNode = new ExprTreeNode("VAL",v);
    }
  
    else{    //TokenString is variable
        NewNode = new ExprTreeNode(TokenString,0);
    }
    return NewNode;
}

void inorderP(ExprTreeNode*Node){
    if(Node== NULL){
        return;
    }
    cout << "(";
    inorderP(Node->left);
    string op;
    if(Node->type == "ADD"){op = "+";}
    if(Node->type == "SUB"){op = "-";}
    if(Node->type == "MUL"){op ="*";}
    if(Node->type == "DIV"){op = "/";}
    if(Node->type == "VAL"){ cout <<Node->num;}
    if(Node->type == "VAR"){op = Node->id;}
    if(Node->type == "del"){op = "del";}
    if(Node->type == "ret"){op = "ret";}
    if(Node->type ==":="){op = ":=";}
    cout << op <<"";
    inorderP(Node->right);
    cout << ")";
}

Parser::Parser(){
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression){
    vector<ExprTreeNode*>VectorNodes;
    ExprTreeNode*EqualNode = createNode(expression[1]);
    ExprTreeNode* LeftNode = createNode(expression[0]);
    EqualNode->left = LeftNode;

    int sz= expression.size();
    for(int i=2;i<sz;i++){
        string TokenString = expression[i];

        if(TokenString =="("){/*then do noting*/}

        else if(isNumber(TokenString)==1){
            ExprTreeNode* Node = createNode(TokenString);
            VectorNodes.push_back(Node);
        }

        else if(isOperator(TokenString)==1){
            ExprTreeNode* top = VectorNodes[VectorNodes.size()-1];
            VectorNodes.pop_back();
            ExprTreeNode* OperatorNode = createNode(TokenString);
            OperatorNode->left = top;
            VectorNodes.push_back(OperatorNode);
        }

        else if(TokenString ==")"){
            ExprTreeNode*top = VectorNodes[VectorNodes.size()-1];
            VectorNodes.pop_back();
            VectorNodes[VectorNodes.size()-1]->right = top;
        }

        else{
            //TokenString is a variable name:
            ExprTreeNode* VariableNode = createNode(TokenString);
            VectorNodes.push_back(VariableNode);
        }

    }
    EqualNode->right = VectorNodes[0];
    expr_trees.push_back(EqualNode);

    //LeftNode can be  DEL, VAR, RET type:

    if(LeftNode->type == "VAR"){ // variable assignment then insert in symbol table;
        //if the var is reassigned without deleting then what to do ?
        //then write the code here : 
        symtable->insert(LeftNode->id);
    }

    else if(LeftNode->type =="del"){
        symtable->remove(EqualNode->right->id); //delete from the symbol table;
    }

    else if(LeftNode->type == "ret"){
        //then do nothing to the symtable;
    }
}

Parser::~Parser(){
    delete symtable;
}

void inorder1(SymNode* root){ 
    if(root == NULL){
        return;
    }
    inorder1(root->left);
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
    inorder1(root->right);
}



void print2(SymbolTable* table){
    cout << "============================ size of table is " << table->get_size() << "============================"<<endl;

    SymNode* RootNode = table->get_root();
    inorder1(RootNode);
     cout << "==========================================================================="<<endl;
}

// int main(){
// // Statement 1: v := ((3 * 2) + (10 * 11))
// vector<string> token1 = {"v", ":=", "(", "(", "3", "*", "2", ")", "+", "(", "10", "*", "11", ")", ")"};
// // Statement 2: a := (((3 * v) + 9) / 11)
// vector<string> token2 = {"a", ":=", "(", "(", "(", "3", "*", "v", ")", "+", "9", ")", "/", "11", ")"};
// // Statement 3: b := a
// vector<string> token3 = {"b", ":=", "a"};
// // Statement 4: del := b
// vector<string> token4 = {"del", ":=", "b"};
// // Statement 5: c := ((3 * a) - (2 * v))
// vector<string> token5 = {"c", ":=", "(", "(", "3", "*", "a", ")", "-", "(", "2", "*", "v", ")", ")"};


// vector<vector<string>>l{token1,token2,token3,token4};

// Parser* p= new Parser();
// for(int i=0;i<l.size();i++){
//     p->parse(l[i]);
//     cout <<"parsing for expression "<<i+1 << " done!" << endl;
//     // inorderP(p->expr_trees.back());
//     // cout << endl <<"printing symbol table " << endl;
//     // print2(p->symtable);
// }
//     for(int i=0;i<p->expr_trees.size();i++){
//         inorderP(p->expr_trees[i]);
//         cout << endl;
//     }

//     return 0;
// }
