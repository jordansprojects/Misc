/********************************************
*	DEVELOPER:	Jordan
* COLLABORATORS: <name of peer, tutor, instructor>
*	COURSE:	CS226 Discrete Structures
*	PROJECT:	<project #4>
*	LAST MODIFIED:	5/16/2021
********************************************/
/********************************************
*	PERMUTATION AND COMBINATION  COUNTER
*********************************************
*	PROGRAM DESCRIPTION:
*	a program that takes integers n and r where 0  < r ≤ n and booleans for whether repetition is allowed and whether order matters then outputs the number of r-permutations or r-combinations accordingly
NOTE: This program struggles with accuracy once the
 values become too large, due to overflow. 
*********************************************
*	FUNCTIONS:
* int r_combinations(int n, int r);
* int r_permutations(int n, int r);
* int factorial(int);
*********************************************/

#include <iostream> //to output to console
#include <math.h> // for exponents

//function prototypes
int r_combinations(int n, int r, bool);
int r_permutations(int n, int r, bool);
int factorial(int);

/*********************************************
*	MAIN PROGRAM:
*********************************************/
int main() 
{
  int r,n;
  bool repeats_allowed = true;
  bool order_matters = true;
  std::string ans;
  const std::string DOTS = "\n************************************\n";
  std::cout<< DOTS <<"COMBINATION AND PERMUTATION COUNTER" << DOTS;
  std::cout<<"Enter an n value : n = ";
  std::cin>>n;
  std::cout<< "Enter an r value, it must be larger than 0 \nand less than or equal to n : r = ";
  std::cin>> r;

  if( r > n  || r < 0 ){
    std::cout<< "Invalid values given.\n r must be larger than 0,\n     and n must be greater than or equal to r.";
    std::cout << "Exiting program.\n";
    return 0;
  }

  std::cout<< "Does order matter? y/n : ";
  std::cin>>ans;
  ans[0] = tolower(ans[0]);   // convert first character in ans to lowercase
  if(ans[0] == 'n') order_matters = false;

  std::cout<< "Repeats allowed? y/n : ";
  std::cin>>ans;
  ans[0] = tolower(ans[0]);   // convert first character in ans to lowercase
  if(ans[0] == 'n') repeats_allowed = false;

  if(order_matters){
    std::cout<< "Number of Permutations : " << r_permutations(n, r, repeats_allowed) <<std::endl;
  }else{
    std::cout<< "Number of Combinations: " << r_combinations(n, r, repeats_allowed) <<std::endl;
  }
}
/*********************************************
*	FUNCTIONS:
*********************************************/

int r_combinations(int n, int r, bool repeats_allowed){
  //(n + r - 1)! / r! * (n-1)!
  if(repeats_allowed){
    int fact_r = factorial(r);
    int numerator = factorial(n+r -1);
    int denominator = fact_r * factorial(n-1);
    return (numerator/ denominator);
  }
  // C(n,r) = n!/ r! * (n-r)!
  return (factorial(n) / ( factorial(r) * factorial(n - r)));
}

int r_permutations(int n, int r, bool repeats_allowed){
  // n^r
  if(repeats_allowed) return pow(n,r); 
  // P(n,r) = n!/(n-r)!
  int numerator = factorial(n);
  int denominator = factorial(n - r);
  return (numerator / (denominator));
}
//computes factorial . ex : 5! = 5 * 4 * 3 * 2 * 1 
int factorial( int val){
   if ((val == 0 )||(val == 1)) return 1;
   else
   return val * factorial(val - 1);
}