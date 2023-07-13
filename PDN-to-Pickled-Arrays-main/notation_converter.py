''' 
-------------------------------------------------------------------------------------------------
notation_converter.py - responsible for converting checkers game notation into arrays of integers
-------------------------------------------------------------------------------------------------
        * Data class  - encapsulates checker game data
        * converter   - modifes array based on checker notation input
        * main        - accepts file to read from and convert to acceptable data
-------------------------------------------------------------------------------------------------
'''

# TO-DO : Make main method more dynamic so other users can use the script by entering in a file name.

# Imports
import re  # for parsing data
import pickle #for pickling our data
# Regex constants
REGEX_RESULT = '(?<=Result ")\d(?=-)|(?<=Result ")\d\/\d(?=-)'
REGEX_GAME = '(?<=]).1.[^[]+'
REGEX_ROUND = '(\d+\.)'
REGEX_MOVES ='\d+x\d+x\d+x\d+|\d+x\d+x\d+|\d+x\d+|\d+-\d+'


# Indexing Constants
# This grouping is important for calculating a "taken" piece's index
ODD_ROW_INDICIES = {0, 1 , 2 , 3, 8 ,9, 10, 11, 10, 16,17, 18, 19, 24,25,26,27}
EVEN_ROW_IDICIES = {4,5,6,7,12,13,14,15,20,21,22,23,28,29,30,31}

# constants to determine whether a piece is kinged
BLACK_KINGZONE = 28 #indices >= 28 (28-31) for black indicate "kinging"
WHITE_KINGZONE = 3 #indices <= 3 (0-3) for white indicate "kinging"
''' 
------------------------------------------------------------------------------------------------
DATA CLASS: 
------------------------------------------------------------------------------------------------
    Encapsulates board state data arrays and the game outcome
    Created with the intention to interface with training Deep Learning model 
------------------------------------------------------------------------------------------------
'''
class GameData:
    LOSE = 0    # Player 1 loses. Of course this means Player 2 wins
    DRAW = 1    
    WIN = 2     # Player 1 wins. Of course this means Player 2 loses
    UNDETERMINED = -1
    STATE_0 = [1,1,1,1,
            1,1,1,1,
            1,1,1,1,
            0,0,0,0,
            0,0,0,0,
            2,2,2,2,
            2,2,2,2,
            2,2,2,2]
    # Constructor
    # Accepts state array, move strings, result and number of rounds
    def __init__(self, move_strings = [], result =UNDETERMINED ,num_rounds = UNDETERMINED):
        self.states = [GameData.STATE_0]  # array of arrays, will consist of each board state
        #self.states.append(GameData.STATE_0)
        self.num_rounds = num_rounds      # how many rounds per game
        self.move_strings = move_strings  # strings to contain game in checker notation form
        self.result = result
    # adds board state to state array
    def append(self, board_state):
        self.states.append(board_state)

# Python's toString. Prints data nicely, useful for error checking!      
    def __str__(self):
      states_str = ""
      for i in range(len(self.states)):
        states_str = states_str +'STATE ' +str(i) + '\n'
        for j in range(len(self.states[i])):
          states_str = states_str + " " +  str(self.states[i][j])
          if ((j+1) % 4 == 0): # new line 
            states_str = states_str + "\n"
        
      return "Result = " + str(self.result) + "\nRounds = " + str(self.num_rounds) + '\nBoard matrices = \n'+states_str
# end of class data


def remove_comments(string):
  start = -2
  while(start != -1):
    start = string.find('{')
    stop = string.find('}')
    string = string[0:start] + string[stop+1::]
  return string

''' 
------------------------------------------------------------------------------------------------
DATA CONVERTVER FUNCTION.
------------------------------------------------------------------------------------------------
accepts string filename, returns GameData array
------------------------------------------------------------------------------------------------
'''
def create_viable_data(file_name):      
  games = []
  try:
    f = open(file_name, "r")
    raw_data = f.read().replace('\n', ' ')
    better_data= remove_comments(raw_data) # gets rid of curly braces and text in between
    #print(raw_data)
    f.close()
    checker_notation_str = re.findall(REGEX_GAME, better_data)
    for i in range(len(checker_notation_str)):
      # add games
      move_strings = re.findall(REGEX_MOVES,checker_notation_str[i])
      last = move_strings[len(move_strings)-1] 
      if last == '0-1':
        result = GameData.LOSE
      elif last == '1-0':
        result = GameData.WIN
      else:
        result = GameData.DRAW
      # now pop last element as we no longer need it
      move_strings.pop()
      # the new length divided by two tells us how many rounds
      num_rounds = int(len(move_strings)/2)
      games.append(GameData(move_strings,result,num_rounds))
      all_game_states = []
      all_results = []
      for x in games:
          all_game_states.append(x.states)
          all_results.append(x.result)
  # failed to open file
  except(FileNotFoundError, IOError): 
        print("Failed to open file titled :", file_name)
        print("Perhaps it is in the wrong directory, or you wrote the path incorrectly?")
        print("Exiting program.")
        exit()

  for i in range (len(games)):
        generateAllStates(games[i])
  print("Game generation successful")    
  return (all_game_states, all_results)

# tells you whether the index is in an "even row"
# this is important for figuring out what aritmetic to use
# when computing a taken index
def is_odd_rowed(index):
  return (index in ODD_ROW_INDICIES)

''' 
------------------------------------------------------------------------------------------------
CONVERT ALL MOVE STRINGS TO BOARD STATES
------------------------------------------------------------------------------------------------
@param game_data_obj : GameData object with move strings
------------------------------------------------------------------------------------------------
'''
def generateAllStates(game_data_obj):
  n = len(game_data_obj.move_strings)
  for i in range (n):
    game_data_obj.append((move_piece(game_data_obj.states[i],game_data_obj.move_strings[i])))

# accepts taker and destiation indexes, returns index of taken value
def take_piece(taker, dest):
  # it is important to determine smaller number, since white or a kinged black piece
  # may be coming from a larger index to a smaller one. We still want to calculate the
  # taken index accurately
  min = taker if (taker < dest) else dest
  max = dest if (dest > taker) else taker
  # determine if it is a "left hop" or "right hop"
  # a difference of 7 indicates a left hop, difference of 9 indicates right hop
  left = True if (max - min == 7 ) else False
  # determine if starting component is an odd rowed or even rowed index
  # so we know what addition rule to follow when simulating the taking of a piece
  # during a "hop "
  if(is_odd_rowed(taker)):
    taken = min + 4 if left else min +5
  else:
    taken = min +3 if left else min + 4  
  return taken
''' 
------------------------------------------------------------------------------------------------
PIECE MOVE CONVERSION
------------------------------------------------------------------------------------------------
accepts board state array, and string denoting movement
returns new board state array after move as occured.
NOTE: We assume that the data given enforces legal moves, so this function does not do any checking
for the legality of moving
------------------------------------------------------------------------------------------------
'''
def move_piece(array, move):
  #print(move)
  start = -1
  board_state = list(array)            # make sure to make deep copy of array
  takes = move.count('x')                 
  components = []                      # holds list of each piece number and the symbol
  if '-' in move != 0 : # Piece is moving, not taking (ie 11-15)
    components = move.split('-')                
    components = [eval(i) for i in components]# convert all strings to integers   
    start = components[0]-1
    end = components[1] -1
    piece = board_state[start] # grab moving piece's value                                 
    board_state[start] = 0     # leave previous space empty 
    board_state[end] = piece   # place piece in new location
    
  elif takes != 0: # Piece is takng, not moving 
    # split up move array into a list
    components = move.split('x')
    components = [eval(i) for i in components]    # convert all strings to integers

    # record starting and ending indicies
    start = components[0]-1
  
    end = components[len(components)-1] -1
    
    piece = board_state[start]                    # grab taking piece's value 
    board_state[start] = 0                        # set taking piece's current location to 0
    taker = start
    for i in range (1, len(components)):
      dest = components[i] -1
      taken = take_piece(taker,dest)
      board_state[taken] = 0
      taker = dest                               # move taker piece to previous destination
    # place piece at destination
    board_state[end] = piece
      
  else:
    print("Something went wrong when trying to parse moves.")
    print("Either your data is not formatted correctly, or current regex implementation has a bug")
    exit() 
  # now return the new array

  # king black
  if (piece == 1 and end  >= BLACK_KINGZONE):
    board_state[end] = 3
  #king white
  elif(piece ==2 and end <= WHITE_KINGZONE):
    board_state[end] = 4
  return board_state
    

# Call to main
if __name__ == "__main__":

  (states,results) = create_viable_data("OCA_2.0.pdn")
  file1 = open("game_states.pkl",'wb')
  file2 = open("game_results.pkl",'wb')
  pickle.dump(states,file1)
  pickle.dump(results,file2)
  file1.close()
  file2.close()
