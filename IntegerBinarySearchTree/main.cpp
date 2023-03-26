/****************************************************************
*	Integer Binary Search Tree
****************************************************************
*	PROGRAM DESCRIPTION: Demo program to a simple binary search
* tree.
* Also see : 
* bst.h  - header file for the binary search tree
* bst.cpp - defines functions for the binary search tree
* bst files contain the node struct, as well as functions for
* the bst.
****************************************************************
***************************************************************
*	SETUP STATEMENTS and PURPOSE:
* For this project you can choose any of the Computer Projects 
* from the text (end of each chapter has a few) that you 
*have not already submitted.
****************************************************************
*	Pg 808 #5
* Given a binary search tree and an item,
* locate or add this item to the binary search tree
****************************************************************/
#include <iostream> //to output to console
#include "bst.h"

//function prototypes
void populateTree(bst &, int);

/****************************************************************
*	MAIN PROGRAM:
****************************************************************/
int main() {
  int value;
  const int NUM_VERTICIES = 55;
  srand(time(NULL));   //seed random number generator 
  bst tree; //create empty tree
  populateTree(tree, NUM_VERTICIES);
  tree.printTree();
  std::cout<<"Here is a populated tree.\n";
  std::cout<<"Enter a value to add to it : ";
  std::cin>>value;
  bool didYaAdd = tree.insert(value);
  tree.printTree();

  if (!didYaAdd){
     std::cout<< "It appears that " <<value<< " is a already a vertex on this tree.\n";
  }else{
    std::cout<<"Successfully added " << value <<" to the tree.\n";
    std::cout<<"Here is your tree after adding your value.\n";
  }
 
  std::cout<<"Enter value to search for : ";
  std::cin >> value;

  if(tree.findItem(value)){
    std::cout<<"Yep, " << value << " is on this tree.\n";
  }else{
    std::cout<<"No, " << value << " is not on this tree.\n";
  }
  
}

/*****************************************************
*	FUNCTIONS:
******************************************************/
// accepts tree and number of vertices as paramater, 
//randomly generates integers to be added to the tree
void populateTree(bst &tree, int numVerticies){
  //generates number between 1 and 100
  int number = (rand() % 100) + 1;

  for(int i =0; i < numVerticies; i++){
    tree.insert(number);
    number = (rand() % 100) + 1;
  }

}
