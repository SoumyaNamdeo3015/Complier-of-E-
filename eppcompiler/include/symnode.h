#pragma once
#include "string"
using namespace std;

class SymNode {
public:
    string key;
    int height;
    int address=-1;
    
    SymNode* par;
    SymNode* left;
    SymNode* right;

    SymNode();
    SymNode(string k);

    SymNode* LeftLeftRotation(); // case 1
    SymNode* RightRightRotation(); // case 2
    SymNode* LeftRightRotation(); // case 3
    SymNode* RightLeftRotation(); // case 4

    ~SymNode();
    
};