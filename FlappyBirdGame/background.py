from turtle import Turtle
from random import randint, random
import time

class Background(Turtle):
    def __init__(self):
        super().__init__()
        self.shape("square")
        self.color("red")
        self.penup()
        self.tubes_in_game = []

class Tubes(Background):
    def __init__(self, tube, wid):
        super().__init__()
        self.spd = 0.02
        self.distance_center = wid*10
        if tube == "upper":
            self.goto(x=765, y=400)
            self.shapesize(stretch_len=1.5, stretch_wid=wid)
        elif tube == "lower":
            self.goto(x=765, y=-320)
            self.shapesize(stretch_len=1.5, stretch_wid=wid)
        elif tube == 0:
            self.hideturtle()
        else:
            pass
        
    def move(self):
        for tube in self.tubes_in_game: 
            tube.back(7)

    def new_tube(self):
        random_upper_wid = randint(1,52)*random()
        random_lower_wid = 53 - random_upper_wid
        upper_tube = Tubes(tube="upper", wid=random_upper_wid)
        lower_tube = Tubes(tube="lower", wid=random_lower_wid)
        self.tubes_in_game.append(upper_tube)
        self.tubes_in_game.append(lower_tube)
