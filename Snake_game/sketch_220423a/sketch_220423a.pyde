import os
import random
dimension_columns = dimension_rows = 20
resolution = 600
cellcol = cellrow = diameter = resolution//dimension_rows

class Snake: #stores the snake and sets/stores directions
    def __init__(self):
        self.locationx = (dimension_columns//2)*diameter #initial x location of the snakehead
        self.locationy = (dimension_rows//2)*diameter #initial y location of the snakehead
        self.snakehead = Circles(self.locationx,self.locationy,"green") #the snakehead
        self.snaketails = [] #list where the snake is stored
        self.snakebody = Circles(self.locationx - diameter, self.locationy, "green") #1st body of snake
        self.snakebody2 = Circles(self.locationx - 2*diameter, self.locationy, "green") #2nd body of snake
        self.snaketails.append(self.snakehead)
        self.snaketails.append(self.snakebody)
        self.snaketails.append(self.snakebody2)
        self.direction = "RIGHT" #default direction of the snakehead
        self.intended = None #stores intended direction
    
    def moving(self):
        for i in range (-1, -len(self.snaketails), -1): #make it follow the snake so previous replaces the location of the circle at front etc. / imaginary location
            (self.snaketails[i].x) = (self.snaketails[i-1].x)
            (self.snaketails[i].y) = (self.snaketails[i-1].y)

        if self.intended == "UP" and self.direction != "DOWN": #goes up, cannot go down from up
            self.direction = "UP"
        elif self.intended == "DOWN" and self.direction != "UP": #goes down, cannot go up from down
            self.direction = "DOWN"
        elif self.intended == "RIGHT" and self.direction != "LEFT": #goes right, cannot go left from right
            self.direction = "RIGHT"
        elif self.intended == "LEFT" and self.direction != "RIGHT": #goes left, cannot go right from left
            self.direction = "LEFT"
        
        i = self.snaketails[0] #will designate how the snake will move depending on the self.direction
        curr_cords = (i.x, i.y)
        if self.direction =="UP":
            i.y = i.y - diameter
        elif self.direction == "RIGHT":
            i.x = i.x + diameter
        elif self.direction == "LEFT":
            i.x = i.x - diameter
        elif self.direction == "DOWN":
            i.y = i.y + diameter
    
    def display(self): #will display the snake & the head's image accordingly
        for i in (self.snaketails):
            noStroke()
            self.snakeheaddisplay() 
            i.display()       
  
    def snakeheaddisplay(self): #makes sure that the head of the snake is displayed according to its respective direction
        if self.direction == "UP": 
            image(head_up, self.snaketails[0].x, self.snaketails[0].y, diameter, diameter)
        elif self.direction == "DOWN":
           image(head_down, self.snaketails[0].x, self.snaketails[0].y, diameter, diameter)
        elif self.direction == "LEFT": 
            image(head_left, self.snaketails[0].x, self.snaketails[0].y, diameter, diameter)
        elif self.direction == "RIGHT": 
           image(head_right, self.snaketails[0].x, self.snaketails[0].y, diameter, diameter)     
    
    def collision(self,x,y,food_num):  #checks the collision between a fruit and the snakehead / takes arguements from Game class
        if dist(self.snaketails[0].x, self.snaketails[0].y,x,y) < diameter:
            if food_num == 0:
                self.snaketails.append(Circles(self.snaketails[-1].x, self.snaketails[-1].y, "red"))
            elif food_num == 1:
                self.snaketails.append(Circles(self.snaketails[-1].x, self.snaketails[-1].y, "yellow"))    
            return True

class Food:
    
    def __init__(self, cords): #coordinates of the fruit, taken from Game class, is maken sure it does not overlap with the snake's location
        self.random_x = cords[0]
        self.random_y = cords[1] 
        self.food = random.randint(0,1) #banana or apple
    
    def fruits_display(self):
        if self.food == 0:
            noStroke()
            noFill()
            ellipse(self.random_x,self.random_y,diameter, diameter)
            image(apple,self.random_x,self.random_y, diameter, diameter) #places image on top of the transparent ellipse
        elif self.food == 1: 
            noStroke()
            noFill()
            ellipse(self.random_x,self.random_y, diameter, diameter)
            image(banana,self.random_x,self.random_y, diameter, diameter) #places image on top of the transparent ellipse
      
class Circles():
    def __init__(self,x,y,color): 
        self.x = x
        self.y = y
        self.c = color
     
    def display(self):
        if self.c == "green":
            fill(80,153,32) 
        elif self.c == "red":
            fill(173, 48, 32)
        elif self.c == "yellow":
            fill(251, 226, 76)
        self.snakebody = ellipse(self.x, self.y, diameter, diameter) #takes x,y location from class Snake
  
class Game():
    def __init__(self):
        self.snakeshow = Snake()
        self.fruit = Food(self.random_cord())
        self.gameend = False
    
    def snakecollision(self): #checks if the snakehead has collided with the fruit
        if self.snakeshow.collision(self.fruit.random_x, self.fruit.random_y, self.fruit.food):
            self.fruit = Food(self.random_cord()) #generates a new fruit
       
    def random_cord(self): #creates random coordinates for the fruits & generates new coordinate if it overlaps with location of the snake
        x = random.randint(0,dimension_columns-1)*cellcol  
        y = random.randint(0, dimension_rows-1)*cellrow 
        
        count = 0
        for i in range(len(self.snakeshow.snaketails)):
            flag = False
            while flag == False:
                if x == self.snakeshow.snaketails[i].x and y == self.snakeshow.snaketails[i].y:
                    x = random.randint(0,dimension_columns)*cellcol 
                    y = random.randint(0, dimension_rows)*cellrow 
                    for j in range(i):
                        if x == self.snakeshow.snaketails[j].x and y == self.snakeshow.snaketails[j].y:
                            break
                        else:
                            count += 1
                    if count == i:
                        flag = True
                else:
                    flag = True
        return [x,y]       
                

    def move(self): #updates the location of the objects inside the snaketails list
        self.snakeshow.moving()
        
    def display(self):
        self.snakeshow.display()
        self.fruit.fruits_display()
    
    def score(self): #displays the score
        textAlign(CENTER)
        fill (19, 16, 15)
        textSize(20)
        text("Score: "+str(len(self.snakeshow.snaketails)-3), (dimension_columns-3)*diameter, cellrow)

    def boundaries(self): #function to end game when the snake touches the border 
        if self.snakeshow.snaketails[0].x >= resolution:
            self.gameend = True
        elif self.snakeshow.snaketails[0].x < 0:
            self.gameend = True
        elif self.snakeshow.snaketails[0].y >= resolution:
            self.gameend = True
        elif self.snakeshow.snaketails[0].y < 0:
            self.gameend = True
        elif len(self.snakeshow.snaketails)-3 == 400: #checks when the snake's tail reaches 400
            self.gameend = True                    

    def self_boundary(self): #checking if the snake hits itself
        for i in range(3, len(self.snakeshow.snaketails)):
            if self.snakeshow.snaketails[0].x == self.snakeshow.snaketails[i].x and self.snakeshow.snaketails[0].y == self.snakeshow.snaketails[i].y:
                self.gameend = True
                break        
    
    def update(self):
        game.move()
        game.snakecollision() 


game = Game()
def setup():
    size(resolution, resolution) 
    background(205)
    colorMode(RGB)
    global head_right
    head_right = loadImage("head_right.png")
    global apple 
    apple = loadImage("apple.png")
    global banana
    banana = loadImage("banana.png")
    global head_down
    head_down = loadImage("head_down.png")
    global head_up
    head_up = loadImage("head_up.png")
    global head_left
    head_left = loadImage("head_left.png") 
    
def draw(): 
    ellipseMode(CORNER)
    if frameCount%12 == 0:
        if game.gameend == False:
            background(205)
            game.display()
            game.update()
            game.boundaries()
            game.self_boundary()
            game.score()
        elif game.gameend == True:
            textAlign(CENTER)
            fill(19, 16, 15)
            textSize(30)
            text("Game Over",(dimension_columns//2)*diameter,(dimension_rows//2)*diameter)
            textSize(20)
            text("Click on the screen to start over!",(dimension_columns//2)*diameter,(dimension_rows//2)*diameter + diameter)
            game.score()

def keyPressed(): 
    if keyCode == UP: 
        game.snakeshow.intended = "UP"
    elif keyCode == DOWN: 
        game.snakeshow.intended = "DOWN"
    if keyCode == LEFT: 
        game.snakeshow.intended = "LEFT"
    elif keyCode == RIGHT:
        game.snakeshow.intended = "RIGHT"

def mouseClicked(): #restarts the game once you click the screen after gameover (if gameend == True)
        global game
        if game.gameend == True:
            game = Game()

  
