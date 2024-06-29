#pragma once
#include <string>
using namespace std;

class ExprTreeNode {
public:
    string type; // Can be "ADD", "SUB", "MUL", "DIV", "MOD", "VAL", "DEL", "RET" or "VAR" (for variable)

    // Stores the variable name if type is "VAR"
    string id;
    //Store the value of the number if type is "VAL"
    int num;

    ExprTreeNode* left;
    ExprTreeNode* right;

    ExprTreeNode();
    ExprTreeNode(string t,int v);

    ~ExprTreeNode();
};