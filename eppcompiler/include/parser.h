#pragma once
#include "exprtreenode.h"
#include "symtable.h"
#include <vector>
using namespace std;

class Parser {
public:
    vector<ExprTreeNode*> expr_trees;
    SymbolTable* symtable;

    Parser();
    ~Parser();
    
    // Should parse the expression and 
    // push the root to the exp_trees
    // Also make necessary changes to the symtable
    void parse(vector<string> expression);
};