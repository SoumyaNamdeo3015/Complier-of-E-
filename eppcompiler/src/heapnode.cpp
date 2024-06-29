/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    par = nullptr; left = nullptr; right  = nullptr; val =  0;
}
HeapNode::HeapNode(int _val){
    par = nullptr; left = nullptr; right = nullptr; val = _val;
}
HeapNode::~HeapNode(){
    par = nullptr; left = nullptr; right = nullptr;
}