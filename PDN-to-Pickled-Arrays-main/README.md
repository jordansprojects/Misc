# PDN-to-Pickled-Array
Python script that accepts a .pdn [(Portable Draughts Notation)](https://checkers.fandom.com/wiki/Portable_Draughts_Notation) file and converts it to represent game states in the form of one dimensional arrays. 

This script is a reupload from several months ago, it was created to so that the checker data could be used to train a Neural Network to play checkers. 

The data available was written in PDN format, which was not readable to a Neural Network. To circumnavigate this, this script was written to convert each indivdiual move to a 1-dimnensional state array.
The program saves the content in a pickled file.


# TO-DO : 
* Edit script so that it can accept command line arguments.
* Edit script so that the pickled data is the form of integer arrays and not the encapsulated objects. 
* Edit script so that the user can choose the name of the pickle files. 
