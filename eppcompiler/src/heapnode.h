#pragma once
using namespace std;

class HeapNode{
  public:
  int val;
  HeapNode* par;
  HeapNode* left;
  HeapNode* right;
  
  HeapNode();
  HeapNode(int _val);
  
  ~HeapNode();
};