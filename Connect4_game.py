import random
import os

dimension_col = 6 #flexible column global variable
dimension_row = 6 #flexible row global variable
show_board = [] #the board displayed on screen
valid_guess = [] #list where guesses are stored
num_of_players = (input("Please enter the number of players: ")) #ask for the number of players & saves value as integer

while len(num_of_players) != 1 or (not num_of_players.isdigit() == True) or (int(num_of_players) < 2 or int(num_of_players) > 5): 
    if len(num_of_players) != 1:
        print("Please enter a 1-character number as the number of players!") 
        num_of_players = (input("Please try again: ")) #user needs to re-input the valid number of players
        os.system("clear") 
    elif num_of_players.isdigit() == False: #makes sure the entered value is a number
        print("Please enter a number!") 
        num_of_players = (input("Please try again: "))
        os.system("clear")
    else:
        if int(num_of_players) < 2 or int(num_of_players) > 5: #this line is the problem...
            print("There can only be a minimum of 2 and maximum of 5 players!")
            num_of_players = (input("Please try again: "))
            os.system("clear") 

num_of_players1 = int(num_of_players)

players_list = ["X", "O", "V", "H", "M"] #list with players, will only accomodate up to 5 players
playing_people = [] + players_list[0:num_of_players1] #depending on the number of players entered, the corresponding player characters will be placed into empty list
first_player = random.randint(0, num_of_players1 -1) #it will randomly generate the first player, -1 is there bcs index starts with 0
os.system("clear")
print("Player",playing_people[first_player]+", you go first!\n") #statement which opens game

for row in range(dimension_row): #creating 2D board 
    row_list = []
    for col in range(dimension_col):
        row_list.append(" ") #empty space to accomodate the letter to be placed later on in the game
    show_board.append(row_list) #space is appended into the row_list list

def print_board(board): #the function to print board
    for col in range(dimension_col):
        print("   ",chr(65+col),"",end="", sep="") #prints the horizontal alphabet letters
    print() #space
    print(" ",("+---")*dimension_col,"+",end="",sep="") #prints horizontal rows
    print() #space

    for row in range(dimension_row):
        print(" |",end="",sep="") 
        for col in range(dimension_col):
             print(" "+ show_board[row][col] + " ","|",end="",sep="") #prints vertial columns
        print()
        print(" ",("+---")*dimension_col,"+",end="",sep="") #prints the last horzontal row line
        print() 

def check_horizontal_board(checking, board): #function which check for a win horizontally
    for row in range(dimension_row): 
        for col in range(dimension_col - 3): #the last 3 columns no need to check since it will go out of board
            if board[row][col] == checking and board[row][col+1] == checking and board[row][col+2] == checking and board[row][col+3] == checking:
                return True    

def check_vertical_board(checking, board): #function which check for a win vertically
    for col in range(dimension_col):
        for row in range(dimension_row - 3): #the last 3 rows no need to check since it will go out of board
            if board[row][col] == checking and board[row+1][col] == checking and board[row+2][col] == checking and board[row+3][col] == checking:
                return True 

def check_negative_diagonal_board(checking, board): #function which check for a win negative slope diagonally
    for col in range(dimension_col - 3): #the last 3 columns no need to check since it will go out of board
        for row in range(dimension_row - 3): #the last 3 rows no need to check since it will go out of board
            if board[row][col] == checking and board[row+1][col+1] == checking and board[row+2][col+2] == checking and board[row+3][col+3] == checking:
                return True 

def check_positive_diagonal_board(checking, board): #function which check for a win positive slope diagonally
    for col in range(3,dimension_col): #the first three columns no need to check since it will go out of board
        for row in range(dimension_row - 3): #the last three rows no need to check since it will go out of board
            if board[row][col] == checking and board[row+1][col-1] == checking and board[row+2][col-2] == checking and board[row+3][col-3] == checking:
                return True 
counter = 0 

print_board(show_board)
while len(valid_guess) != (dimension_col*dimension_row): #the draw occurs when the board is full and the while loop ends
    lost_turn = True #default designation for lost_turn to later use for when a player chooses a full column
    draw = True #draw remains True and will change when there is a win to False
    guess = input("Please choose a column: ")
    
    while not (len(guess) == 1 and 65 <= ord(guess) <= (65+dimension_col-1) and guess not in valid_guess): #checks the validity of the user's input
        if len(guess) != 1: 
            guess = input("Input the value as a 1-character guess! Please try again:")
        elif guess.islower() == True: #the first character should be uppercase
            guess = input("Please enter an uppercase letter for answer! Please try again: ")
        elif guess.isalpha() == False: #the first character should be an alphabet
            guess = input("Please enter an alphabet for your answer! Please try again: ")
        elif 65 > ord(guess) or ord(guess) > (65+dimension_col-1): #range not within the allowed values/corresponding ASCII values/flexible column dimensions accomodated
            guess = input("Input is out of range! Please try again: ")
        else: #last condition for repeated values
            guess = input("You've already entered this value! Please enter a new coordinate: ")
    
    guess_col = (ord(guess)-65) #guess is converted into an integer / if guess is A, its corresponding integer is 0 after you subtract 65

    for spot in range(dimension_row - 1, -1, -1): #checking for available space in board
        if show_board[spot][guess_col] == " ": #checking if space is empty to place checker
            show_board[spot][guess_col] = playing_people[first_player] #places player's checker in the found position
            valid_guess.append(guess+str(spot)) #appends the guess input by the user with corresponding row position as well
            lost_turn = False #in this case the player has chosen a column which is not full / if the column is full the if statement will not run therefore the player will lose their turn since lost_turn remains to be True
            os.system("clear")
            print_board(show_board) 
            break #breaks out of the if statement
    if lost_turn == True:
        print("The column is full, you lost your turn!")
    
    if check_horizontal_board(playing_people[first_player], show_board) == True: #checks for a horizontal win
        print("Congratulations Player",playing_people[first_player]+", you have won!")
        draw = False #it is not a draw since there is a winner
        break

    if check_vertical_board(playing_people[first_player], show_board) == True: #checks for a vertical win
        print("Congratulations Player",playing_people[first_player]+", you have won!")
        draw = False #it is not a draw since there is a winner
        break

    if check_negative_diagonal_board(playing_people[first_player], show_board) == True: #checks for a negative diagonal win
        print("Congratulations Player",playing_people[first_player]+", you have won!")
        draw = False #it is not a draw since there is a winner
        break

    if check_positive_diagonal_board(playing_people[first_player], show_board) == True: #checks for a positive diagonal win
        print("Congratulations Player",playing_people[first_player]+", you have won!")
        draw = False #it is not a draw since there is a winner
        break
    first_player = (first_player +1) % num_of_players1 #the turn goes to the next player after checking for a win

if draw != False: #if the draw is not False, it is true therefore there is a draw
    print("The board is full...It's a draw!") #the draw occurs when the board is full