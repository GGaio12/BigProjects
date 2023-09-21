from turtle import Turtle
from random import randint
from scoreboard import Scoreboard

COLORS = ["red", "orange", "yellow", "green", "blue", "purple"]
STARTING_MOVE_DISTANCE = 5
MOVE_INCREMENT = 10


class CarManager(Turtle):
    def __init__(self):
        super().__init__()
        self.penup()
        self.shape("square")
        self.shapesize(stretch_wid=1, stretch_len=2)
        self.setheading(180)
        random_color = COLORS[randint(0,5)]
        self.color(random_color)
        random_y = randint(-250, 250)
        self.goto(x=300, y=random_y)
        self.move_speed = STARTING_MOVE_DISTANCE
    
    def move(self):
        self.forward(self.move_speed)
    
    def increment_speed(self):
        self.move_speed += MOVE_INCREMENT