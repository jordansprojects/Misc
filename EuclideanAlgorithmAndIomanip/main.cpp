/*********************************************
*	SETUP STATEMENTS and PURPOSE:
*  To demonstrate how to implement the Euclidean
* Algorithm in code. 
*********************************************/
#include <iostream> //to output to console
#include <iomanip> // to make output look slightly nicer

//function prototypes
int EuclideanAlgorithm(int, int);
/*********************************************
*	MAIN PROGRAM:
*********************************************/
int main() {
  int a, b; // for user input - obviously doesnt work if the user enters a char or something.
   std::string DOTS = "\n* * * * * * * * * * * * * * * * * * * * * * * *\n";

  //print pretty dots, then 
  //prompt user to enter integers, 
  std::cout << DOTS;
  std::cout << "Enter an integer : ";
  std::cin >> a;
  std::cout<< "Enter another integer: ";
  std::cin >> b;
  
 //make output pretty
  std::cout << DOTS;               

 //tell user what function is doing
  std::cout << "Euclidean Algorithm : \n";
  
  //Euclidean Algorithm will print out each step and then
  // return the gcd
  int gcd = EuclideanAlgorithm(a,b); 
  
  //compute lcm by multiplying a and b and dividing it by gcd
  int lcm = (a * b) / gcd; 

  //print results nicely to user
  std::cout << DOTS;
  std::cout<< "GCD : " << gcd;
  std::cout<< "\nLCM : " << lcm << "\n";
  std::cout << DOTS;
 
 // exit program
 return 0;
}

/*********************************************
*	FUNCTIONS:
 int EuclideanAlgorithm(int,int )
*********************************************/
/**DESCRIPTION: finds gcd by following euclidean algorithm.
  1 - if b is zero, we stop. return a.
  2 - if a is less than b, swap them 
  3 - find a dividided by b, store difference 
  4 - find remainder by subtracting the difference from a
  5 - nicely print out equation to user.
  6 - call itself, but with b and the remainder 
        as parameter .
************************************************************ */
int EuclideanAlgorithm(int a, int b){
  //stopping case, we can get our last nonzero remainder from a.
  if( b == 0 ) {
    return a;
  }
  // if a is less than b, swap values
  if(a < b){
    int temp = a;
    a = b;
    b = temp;
  }
  // basically find what * b = a ? (most closely)
  // int division drops true remainder
  int difference = a/b; 
  // what + (difference * b) = a ?
  int remainder = a - (difference * b);

  //the setw() calls only do so much if the number is very large. 
  std::cout << std::setw(10)<< a
   << std::setw(5) <<"=" 
   << std::setw(5)<<"(" 
   << std::setw(5)<< b 
   << std::setw(3)<<" * "
   <<std::setw(3)<< difference
   <<std::setw(3)<< ")"
   << std::setw(3) << "+" << 
   std::setw(5) <<remainder << "\n"; 
  
  //call function again, except gcd(b, remainder) -> b = (r * ? ) + ? 
  return EuclideanAlgorithm(b, remainder); 
}
