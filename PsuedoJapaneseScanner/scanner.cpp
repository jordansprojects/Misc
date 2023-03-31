#include<iostream>
#include<fstream>
#include<string>

#include<assert.h> //  assert, for testing 
#include <vector>  // vector, for containing test conditions 

using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: ** 
//=====================================================


/* word DFA helper functions */
bool is_vowel(char ch){
	string vowels = "aiIueEo";
	for (int i = 0 ; i < vowels.length(); i++){
		if(ch == vowels[i])
			return true; // Is a vowel, return true 
	}
	return false; // Not a vowel, return false
}

bool is_bghkmpr(char ch){
	string letters = "bghkmpr";
	for (int i = 0 ; i < letters.length(); i++){
		if(ch == letters[i])
			return true; // Is one of the letters, return true 
	}
	return false; // Not one of the letters, return false
}
bool is_dwzyj(char ch){
	string letters = "dwzyj";
	for (int i = 0 ; i < letters.length(); i++){
		if(ch == letters[i])
			return true; // Is one of the letters, return true 
	}
	return false; // Not one of the letters, return false
}

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Jordan Aquino
// RE:   **
bool word (string s)
{
	/********
	 * Our graph used number and characters. Since state is an int, states with char subscripts will be set
	 * to the ascii value of the char states, whereas numerical subscripted states remain integers.
	 * I.e. state q0 = 0, but state qt = 't' 
	 * */
	int q0q1 = 1; 	 // This is our final state 

	// For these two state vars I chose an arbitrary, unused  ascii value so 
	// the code can work but we stay true to the state names in the DFA diagram
	int qsa = 'z';   
	int q0qy = 'p';

	// the rest just correspond to the state # or letter
	//  I decided to define all of them to be consistent    
	int qy = 'y';
	int q0 = 0;
	int qc = 'c';
	int qt = 't';
	int qs = 's';
	// variables for looping through the word
	int state = 0;		
	int charpos = 0;

	/* replace the following todo the word dfa  **/
	while (s[charpos] != '\0') 
	{
		// store character from wordstring in ch, makes the rest of the code less ugly 
		char ch = s[charpos];
		if(state == q0q1){ 	
			if(is_vowel(ch)){
				state = q0q1;
			}else if (ch == 'n'){
				state = q0qy;
			}else if(is_bghkmpr(ch)){
				state = qy;			
			}else if(is_dwzyj(ch)){
				state = qsa;
			}else if(ch == 's'){
				state = qs;	
			}else if (ch == 'c'){
				state = qc;
			}else if (ch == 't'){
				state = qt;
			}else return false;
		}else if(state == q0){ 
			if(is_vowel(ch)){
				state = q0q1;
			}else if(is_bghkmpr(ch)){
				state = qy;
			}else if (is_dwzyj(ch)){
				state = qsa;
			}else if (ch == 's'){
				state = qs;
			}else if (ch == 'c'){
				state = qc;
			}else if (ch == 't'){
				state = qt;
			}

		}else if (state == qy){	
			if(is_vowel(ch)){
				state = q0q1;
			}else if(ch == 'y'){
				state =qsa;
			}else return false;
		}else if (state == qt ){
			if(is_vowel(ch)){
				state = q0q1;
			}else if(ch == 's'){
				state = qsa;
			}
		}else if (state == qs ){	
			if(is_vowel(ch)){
				state = q0q1;
			}else if( ch == 'h'){
				state = qsa;
			}
		}else if (state == qc ){
			if(ch == 'h'){
				state = qsa;
			}
		}else if (state == qsa){
			if(is_vowel(ch)){
				state = q0q1;
			}else{
				return false;
			}
		}else if(state == q0qy){	
			if (is_vowel(ch)){
				state = q0q1;
			}else if( is_bghkmpr(ch) || ch == 'n'){
				state = qy;
			}else if(is_dwzyj(ch)){
				state = qsa;
			}else if (ch == 's'){
				state = qs;
			}else if (ch == 'c'){
				state = qc;
			}else if (ch == 't'){
				state = qt;
			}

		} //end of states if-else branching 

		charpos++;

	}//end of while

	// where did I end up????
	if (state == q0q1 || state == q0 || state == q0qy) return(true);  // end in a final state
	else return(false);
}

// PERIOD DFA 
// Done by: Jordan Aquino
bool period (string s)
{  
	return(s == ".");

}

// ------ Three  Tables -------------------------------------

// TABLES Done by: **

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, };

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = { }; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.


// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: 
int scanner(tokentype& tt, string& w)
{

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   
  //
 	fin >> w;
	if(w == "eofm") return -1;    

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */

}//the end of scanner



void jordans_DFA_tester(){
	// Delibrate choice to hardcode test cases so this can run without an input file.
	// I compile with -std=c++11 so that I can use an initialization list for the vector here
	vector<string> valids = {"watashi","toire","aoi", "okashii","agE","tatakI", "nyuuryoku","panda","hon", "wa", "rika","desu", "sensei", "tesuto","o", "mashita", "dakara", "soshite","ni", "dakara", "shikashi", "sieto","ikI", "deshita", "masendeshita", "anata", "kare","kanojo","sore","mata", "gyuunyuu","sukiyaki","tenpura","sushi","tomodachi","jidoosha", "biiru","sake","tokyo", "kyuushuu","Osaka","coucho","yasashii","muzukashii","ureshii","shiwase","kanashii","omoi","oishii","tennen", "nakI","tabE","ikI","kakI","yomI","nomI","agE","moraI","butsI","kerI","shaberI", "gohan","ryouri", "yorokobI","seito"};

	vector<string> invalids = {"cry","hit","college","class","book","test","home*","chair","student","teacher","friend","car","milk","beer", "butterfly", "easy","difficult", "pleased","happy","sad","delicious","natural","go*","eat","take*", "write","read", "drink","give","recieve","kick", "talk"};

	for (int i = 0; i < valids.size(); i++){
//		cout<<"On test #"<< (i+1)<< " / " << valids.size() << "\nUsing word " << valids[i] << '\n';
		assert(word(valids[i])); // These are valid, so these should return true
		// lighting a candle w a blowtorch w this period test 
		assert(!period(valids[i])); //make sure period DFA isnt giving false positives anywhere
	}

	cout << "Passed testing valids!\n";

	for(int i = 0; i < invalids.size(); i++){
//		cout<<"On test #"<< (i+1)<< " / " << invalids.size() << "\nUsing word " << invalids[i] << '\n';
		assert(!word(invalids[i])); // These are invalid, so word should return false
	}
	cout << "Passed testing invalids!\n";
	// finally, check period does recognize a period when it sees one
	assert(period("."));
	cout <<"Passed testing period\n";
}



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
	// beyond adding this function call here, I leave krells tester untouched 
	jordans_DFA_tester();
/*
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();
*/
}// end

