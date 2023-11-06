import random
import os 

ship_size = 4 #ship size
dimension = 10 #board size
ship_board = [] #board that is hidden which stores the coordinates of the randomly generated ship
show_board = [] #board that is shown to the user and tracks the game's progression
valid_guess = [] #collects the valid coordinate inputs

print("\nWelcome to The Battleship Game!\nPlease enter a capital alphabet from A-J and a number between 0-9 to guess the coordinates.\nA valid coordinate example is 'A0'.")
print("When your guess is correct, the board will display an 'X' on the grid, but if it is wrong, it will display a '#'.")
for row in range(dimension): #creating 2D board for board that is shown
    row_list = []
    for col in range(dimension):
        row_list.append(" ") #has a blank space where the X or # can be inserted without distorting the board display 
    show_board.append(row_list)

for row in range(dimension): #creating 2D board for the hidden board
    row_list = []
    for col in range(dimension):
        row_list.append(" ") #has a blank space in which the X can be "hidden"
    ship_board.append(row_list)

def print_board(board):
    for col in range(dimension):
        print("   ",chr(65+col),"",end="", sep="") #prints the horizontal alphabet letters
    print() #space
    print(" ",("+---")*dimension,"+",end="",sep="") #prints horizontal rows
    print() #space

    for row in range(dimension):
        print(str(row),"|",end="",sep="") #prints vertical column numbers
        for col in range(dimension):
             print(" "+ board[row][col] + " ","|",end="",sep="") #prints vertial columns
        print()
        print(" ",("+---")*dimension,"+",end="",sep="") #prints the last horzontal row line
        print() 

if random.randint(1,2) == 1: #determines horizontal or vertical: 1 is horizontal
    a = random.randint(0,6) #horizontal & determines column
    b = random.randint(0,9) #row, does not change after generated
    for i in range(ship_size):
        ship_board[a+i][b] = "X" #in the hidden board the ship's coordinates are stored with Xs 
else:
    a = random.randint(0,9) #vertical & determines column
    b = random.randint(0,6) #row
    for i in range(ship_size):
        ship_board[a][b+i] = "X" #in the hidden board the ship's coordinates are stored with Xs

counter = 0 #counter starts at 0, to denote 0 guesses
while counter != 4: #until the battleship is sunk(4 cells), the loop continues
    print("\n")
    guess = input("Enter your guess: ") 

    while not (len(guess) == 2 and guess[0] in 'ABCDEFGHIJ' and guess[1] in '0123456789' and guess not in valid_guess): #checks the validity of the user's input
        if len(guess) != 2: 
            guess = input("Input the value as a 2-character guess! Please try again:")
        elif guess[0].islower() == True: #the first character should be uppercase
            guess = input("Please enter an uppercase letter for the first character! Please try again: ")
        elif guess[0].isdigit() == True: #the first character should be an alphabet
            guess = input("Please enter an alphabet for your first character! Please try again: ")
        elif guess[1].isalpha() == True: #the second character should be a number/integer
            guess = input("Please enter a number for the second character! Try again: ")
        elif guess[0] not in 'ABCDEFGHIJ' or guess[1] not in '0123456789': #range not within the allowed values
            guess = input("Input is out of range! Please try again: ")
        else: #last condition for repeated values
            guess = input("You've already entered this value! Please enter a new coordinate: ")

    valid_guess.append(guess) #appends user's guess into the list valid_guess to make sure no repeat values can be entered(refer to the conditions in the else statement above)

    guess_column = (ord(guess[0])-65) #converts string integer corresponding the ASCII code, then subtract 65 to achieve the desired range of numbers 0-9
    guess_row = int(guess[1]) #converts string to integer to be used in the following if statement

    if ship_board[guess_row][guess_column] == "X": #ship_board contains the coordinates of the consecutive cell values for the ship
        os.system("clear") #clears the page for a better display of the game
        print("Your guess is correct! Battleship hit!")
        show_board[guess_row][guess_column] = "X" #inserts X in the inputted coordinate location
        print("Number of guesses:", len(valid_guess),"\n") #displays number of guesses
        print_board(show_board) #board will be reprinted with the X in the place of the coordinate
        counter += 1 #counter goes up to 4, will stop once the entire ship is sunk since it is 4 consecutive cells
    else: #Either the input value is in the ship_board or not, this is for the case of Not, in other words, when the guess is incorrect
        os.system("clear") #clears the page for a better display of the game
        print("Your guess is incorrect! You missed:(")
        show_board[guess_row][guess_column] = "#" #inserts # in the inputted coordinate location
        print("Number of guesses:", len(valid_guess),"\n") #displays number of guesses
        print_board(show_board) #board reprinted with the #

os.system("clear") #clears screen
print("\nCongratualtions you have sunk the battleship!","\nNumber of guesses:",len(valid_guess),"\n") #marks end of game with guess score
print_board(show_board) #reprints image of final board