from turtle import Turtle
import time

class Ball(Turtle):
    def __init__(self):
        super().__init__()
        self.shape("circle")
        self.color("white")
        self.speed("slowest")
        self.penup()
        self.x_pos = 0
        self.y_pos = 0
        self.move_y = 10
        self.move_x = 10
        self.move_speed = 0.1

    def move(self):
        self.x_pos += self.move_x
        self.y_pos += self.move_y
        self.goto(x=self.x_pos, y=self.y_pos)
        
    def bounce_y(self):
        self.move_y *= -1
        
    def bounce_x(self):
        self.move_x *= -1
        
    def restart(self):
        self.move_speed = 0.1
        self.goto(x=0, y=0)
        self.x_pos = 0
        self.y_pos = 0
        self.bounce_x()

    def add_speed(self):
        self.move_speed *= 0.9