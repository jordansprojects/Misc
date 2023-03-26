/****************************************************************
*	Integer Binary Search Tree
***************************************************************
*	Pg 808 #5
* Given a binary search tree and an item,
* locate or add this item to the binary search tree
****************************************************************/
#ifndef BST_H
#include<string> // so we can use strings : - ) 

 struct node{

  struct node *left;
  struct node *right;
  int data;
  node(int nodeData);
  node(int nodeData, node *left, node *right);

};
//more descriptive explanations are provided in the bst.cpp file .
class bst{
  private:
    node *root;
    void recursive_destructor(node *current);
    bool recursively_insert(int inputData, node *current);
    void printBranches(const std::string& prefix, const node* current, bool isLeft);
    void middleMan(const node* n);
  public:
    bst(); // no arg constructor
    bst(int rootData);
    ~bst();
    bool insert(int inputData);
    void printTree();
    bool findItem(int item);
    bool recursiveSearch(int item, node *current);
   
  

};

#endif