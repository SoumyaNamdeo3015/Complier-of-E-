/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){
    size =0;
    root = nullptr;
}

void MinHeap::push_heap(int num){
    if(root == nullptr){
        root = new HeapNode(num);
        return;}
    
}

int MinHeap::get_min(){
    int MinHeapValue  = root->val;
    return MinHeapValue;
}

void MinHeap::pop(){
}

MinHeap::~MinHeap(){
}
