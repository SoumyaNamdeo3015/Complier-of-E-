# Complier for language E++
Note : This project is an extension for the previous one.
## Things Relevant to previous Project
## Old Headers
Classes `UnlimitedInt` and `UnlimitedRational` are not needed in this project (for simplicity, we will be working with `int`s only). Class `Evaluator` is now just `Parser`, no `eval()` function. Additionally, there is support for two new statements in the syntax of E++: `delete` and `return`.

## Delete Statement

In addition to normal E++ expressions, there is a new statement called `delete`.

## Syntax `del := variable_name`

In the form of a tokens array: `["del", ":=", "variable_name"]`

The delete statements will be semantically correct, meaning the variable must have been assigned a value before.

### Modifications to ExprTreeNode and Parser

The expression tree for the delete statement would be a simple tree consisting of three nodes: the root node as `":="` with the left node of a new type `DEL` and the right node of type `VAR`, storing the variable name.

## Return Statement

Every set of E++ expressions will have the last statement of type `return`. The semantics of `return` would be to stop the execution of the program and return the value of the expression after `return`.

## Syntax `ret := E++ expression`

For example: `ret := (a x (b + c))`, in tokenized form: `["ret", ":=", "(", "a", "x", "(", "b", "+", "c", ")", ")"]`

The `ret` node in the expression tree will have the type `RET`.

## Class Parser (parser.h)

### Parameters

- `int last_deleted`: An optional parameter to maintain the address of the last deleted symbol.
- `vector<ExprTreeNode*> expr_trees`: Stores the roots of the parsed expressions.
- `SymbolTable* symtable`: New modified symbol table (see section below for more details).

### Functions to Implement (parser.cpp)

- `parse(vector<string> expression)`: Read an input vector of tokenized expression, parse it and convert it to a parse tree and push the root into `expr_trees`. Also, make necessary changes to the `symtable` depending upon the expression (if it’s a variable assignment then insert the symbol, for a delete statement it deletes the symbol, and does nothing to the `symtable` for the return statement).

**Note:**
- You can assign any garbage value to the nodes of type `RET`, `DEL`, or `:=`; their values don’t matter like other operator nodes. For nodes of type `VAR` and `VAL`, we would only check parameters `id` and `num` respectively.
- Immutability no longer holds now; that is, a variable can be reassigned a value. It’s also not necessary for a variable to be deleted before reassigning.

# Improving the Expression Evaluator

In previous projected , we implemented an expression evaluator for the language E++. For storing the values of variables, we had created a symbol table using Binary Search Trees. What if the BST used to implement the symbol table is unbalanced? The lookup could then be O(n) in the worst case, where n is the number of variables in the program. In turn, n can be as large as the code, which can end up being a huge overhead.

Now task is to convert the BSTs we implemented for into AVL Trees. Note that now each node will no longer store a value since we are not evaluating but compiling the code. Instead, it will store an address, as described below. 

## The AVL Tree Node Class (symnode.h)

### Parameters

- `string key`: Stores the key (variable name).
- `int height`: Stores the height of the node in the SymbolTable.
- `int address`: Memory address (or index) allocated to the symbol while compiling by the compiler. Default value is set to -1, implying no mapping.
- `SymNode* par`: Pointer to the parent of the node in the symbol table. If the node is root, then set it to `NULL`.
- `SymNode* left`: Pointer to the left child of the node in the symbol table. If it is leaf, then set it to `NULL`.
- `SymNode* right`: Pointer to the right child of the node in the symbol table. If it is leaf, then set it to `NULL`.

### Functions  to Implement (in symnode.cpp)

Any unbalanced tree can be balanced by using simple four rotations. You are free to implement and use these as your helper functions in the symbol table or not use them at all. If you are not going to implement any of the given optional functions, then do not delete their definitions; just write `return NULL` in those.

- `LeftLeftRotation()`: Performs the single left rotation on the node and returns a pointer to the new root.
- `RightRightRotation()`: Performs the single right rotation on the node and returns a pointer to the new root.
- `LeftRightRotation()`: Performs a left and then right rotation on the node and returns a pointer to the new root.
- `RightLeftRotation()`: Performs a right and then left rotation on the node and returns a pointer to the new root.

## Symbol Table (symtable.h)

There is an addition of a new function: `assign_address(string k, int idx)` which will assign a memory index to the input symbol while compiling. Other functions remain the same, implement all of them, instructions similar to Assignment 4. Note that now `search`, `insert`, and `remove` along with `assign_address` should take log(n) time.

**Important:** After each `insert()` and `delete()` function call, the symbol table must be an AVL Tree.

**Things to Note:**
- In `search`, if the key is not found, then return -2.
- For `remove`, if the key doesn’t exist, then it shouldn’t modify the table.
- It can be assumed that `insert` is called for a distinct set of keys only.

# Code Generator

In this part, we will actually generate code in the target language Targ. We will assume that Targ will execute on a stack machine.

## Stack Machine

The code in the target language generated will assume the following architecture of the stack machine:

- **Stack:** An infinite memory, with operations providing access to only the top element(s). It is used to store temporary values in the evaluation of expressions.
- **Memory:** Access to a limited indexable (random-access) memory.

Essentially, the machine will go through the program in the target language Targ, perform some operations on the operands in the stack, and finally store the results in the memory.

**Note:** There is no implement for stack machine. We just need to generate code for parse tree in the Targ language assuming it will execute on a stack machine as described.

## Targ Syntax

The syntax of the language Targ is given below.

| Syntax           | Command Description                                                                 |
|------------------|-------------------------------------------------------------------------------------|
| `PUSH x`         | Push an integer x onto the stack                                                    |
| `PUSH mem[i]`    | Push the value in the ith memory location onto the stack                            |
| `mem[i] = POP`   | Pop the value at the top of the stack and store it in the ith memory location       |
| `DEL = mem[i]`   | Delete the value stored at ith memory location and free it for future use           |
| `ADD`            | Pop and add the top two elements of the stack and push the result back onto the stack|
| `SUB`            | Pop the top two elements from the stack. Subtract the second from the top element of the stack and push the result back onto the stack |
| `MUL`            | Pop two elements from the stack. Multiply them and push the result back onto the stack |
| `DIV`            | Pop two elements from the stack. Divide the top element by the second from the top element. Push the floor of the result, i.e., ⌊res⌋, back onto the stack. If division by zero is attempted, the result is set to `NULL` |
| `RET = POP`      | Push the value on the top of the stack onto a special memory location named `ret`. The execution of the program ends after this operation. |

**Note:** Any operation performed with `NULL` as one of the operands will result in `NULL` as the output.

## Generating the Code

To generate the code in the target language, we will need to recursively iterate over the parse tree you created in Part 2.

## Handling Memory Allocation of Variables

When we do variable assignment in the E++ expressions, we don’t assign the variables a specific memory address. Instead, this part is handled by the compiler itself. We will maintain a vector (in a stack fashion) of available free memory indexes, delete or insert the memory index from the end if a new variable is assigned a value or it’s deleted respectively. We also assume 0-based indexing.

**Note:** This will make the memory address allocation random. To check the correctness of the program, we will simulate it on a “stack machine”. That is, we won’t check the memory address and symbol mapping, but only the value returned.

## Class EPPCompiler (eppcompiler.h)

### Parameters

- `Parser targ`: The main object which will store the symbol table and parsed expressions tree nodes.
- `int memory_size`: Size of the indexable memory provided to map the symbols. Set during the construction and not changed afterward. It can be assumed that the given size of the indexable memory is always sufficient for the input set of E++ expressions.
- `string output_file`: The name of the output file in which generated Targ code needs to be dumped.
- `vector<int> mem_loc`: A vector to maintain the available memory locations.
- `MinHeap least_mem_loc`: A min-heap to maintain the least available memory indexes. You can ignore this parameter if you are not attempting the Bonus part.

### Functions to Implement (in eppcompiler.cpp)

- `compile(vector<vector<string>> code)`: Parses each input tokenized expression, assigns a memory mapping if the expression is a variable assignment or frees up the memory address if it’s a delete statement, and finally compiles the code (i.e., generates and writes all the targ commands to the output file).
- `generate_targ_commands()`: Compiles the last tree node in the Parser and generates Targ commands for it and returns them.
- `write_to_file(vector<string> commands)`: A helper function to write the given set of commands to the output file.

## Writing to File

The file will be parsed line by line, strictly following the Targ syntax. All commands will be run in sequential manner on the stack machine. Empty lines will be ignored in the file. The library `fstream` is included in the header `eppcompiler.h` for your help in writing to the file.

---

# Min-Heap 

Rather than having a random memory-variable mapping while compiling the code, we will now map the variable to the least available memory address (or index). For this, we will use a min-heap. We implement a general heap that can support duplicates and also follows the properties described in the class.

## Class HeapNode (heapnode.h)

### Parameters

- `HeapNode* par`: Pointer to the parent of the node in the min-heap. Set to `NULL` if the node is root.
- `HeapNode* left`: Pointer to the left child of the node. Set to `NULL` if the child is a leaf.
- `HeapNode* right`: Pointer to the right child of the node. Set to `NULL` if the child is a leaf.

## Class MinHeap (minheap.h)

### Parameters

- `int size`: Stores the size of the min-heap.
- `HeapNode* root`: Pointer to the root of the min-heap.

### Functions to Implement (in minheap.cpp)

- `push_heap(int num)`: Pushes the element `num` into the heap.
- `get_min()`: Returns the minimum element in the heap.
- `pop()`: Deletes the minimum element (which is at root) from the heap.

We will check the memory-variable mapping in the stack machine to check the validity of the min-heap. If you are doing the Bonus section, then use the parameter `least_mem_loc` rather than `mem_loc` in your E++Compiler for mapping.




