/****************************************************************
*	Integer Binary Search Tree
***************************************************************
*	Pg 808 #5
* Given a binary search tree and an item,
* locate or add this item to the binary search tree
****************************************************************/
#include "bst.h"
#include <iostream>

// no arg constuctor
bst::bst(){
  root = NULL ;
}

// accepts data for root as parameter
bst::bst(int rootData){
  root = new node(rootData); //create new node at root 
}

/**************************************************************
 travels all paths until all nodes are deleted.
**************************************************************/
void bst::recursive_destructor(node *current){
  if (current != NULL){ //check if current node is null
    recursive_destructor(current->left);
    recursive_destructor(current->right);
    delete current;
  }
}
/**************************************************************
* destructor, calls recursive destructor that destroys all the
nodes. 
***************************************************************/
bst::~bst(){
  recursive_destructor(this->root);
}

/****************************************************************
recursively travereses the tree until it finds a null spot. 
travels left if the data is less than the current nodes data
travels right if the data is greater than the current nodes data
****************************************************************/
bool bst::recursively_insert(int inputData, node *current){
  if(root == NULL){
    root = new node(inputData);
    return true;
  }
  if(current != NULL){
    if(inputData == current->data){  
      return false;
    }
    if(inputData > current->data){
      if(current->right == NULL){
        current->right = new node(inputData);
        return true;
      }
     // std::cout<< "\nDEBUG: CURRENT DATA : " <<current->data;
      return recursively_insert(inputData, current->right);
    }else if (inputData < current->data){
      if(current->left == NULL){
        current->left = new node(inputData);
        return true;
      }
     // std::cout<< "\nDEBUG: CURRENT DATA : " <<current->data;
      return recursively_insert(inputData, current->left);
    }
  }
  //std::cout<<"ITS POSSIBLE TO REACH HERE?!?! OH NO!\n";
  // of course theres a better way to format this function
  // my head hurts so i am leaving it this way for now.
  return false; //if somehow you make it here, the node was not added.
}

bool bst::insert(int inputData){
   return recursively_insert(inputData, root);
}
/****************************************************************
What it sounds like, recursively searches until it finds an item
****************************************************************/
bool bst::recursiveSearch(int item, node *current){
  if(current !=NULL){
    if (item == current->data){
      return true;
    }else{
      if(item > current->data){ 
        std::cout<<"walking right....\n";
        return recursiveSearch(item, current->right);
      }else{
        std::cout<<"walking left...\n";
        return recursiveSearch(item, current->left);
      }
    }
  }
  return false; //if reaching this point, item could not be found
}
/**************************************************************
wrapper function, calls recursivelySearch
***************************************************************/
bool bst::findItem(int item){
  return recursiveSearch(item, root);
  
}
/***********************************************************************
pretty tree printing function from stackOverFlow
https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c 

I made a  few modifications, for some reason they have it positioned so that
smaller values are on the right and larger values are on the left.
if you tilt the tree upwards, I mean.
***********************************************************************/
void bst::printBranches(const std::string& prefix, const node* current, bool isRight){
  if(current != nullptr){
    std::cout<<prefix;
    std::cout << (isRight ? "├──" : "└──" );
    std::cout<< current->data << std::endl;

    //enter next tree level
    printBranches( prefix + (isRight ? "│   " : "    "), current->right, true);
    printBranches( prefix + (isRight ? "│   " : "    "), current->left, false);
  }
}
/************************************************************
* calls recursive tree printing function from stack overflow, to walk and print
* each subtree nicely 
*************************************************************/
void bst::printTree(){
  printBranches("", root, false);
}

/****************************************************************
* node constructors 
*****************************************************************/
node::node(int nodeData){
  this->data = nodeData;
  this->left = NULL;
  this->right = NULL;
}

node::node(int nodeData, node *left, node *right){
  this->data = nodeData;
  this->left = left;
  this->right = right;
}
