from turtle import Turtle, Screen, xcor, ycor
import turtle
import time

class Snake:
    def __init__(self):
        self.body_parts = []
        self.create_snake()
    
    def create_snake(self):
        self.x_pos = 0
        self.y_pos = 0
        self.body_height = 3
        for snakebody in range(self.body_height):
            self.append_block()
            self.x_pos -= 20
            
    def append_block(self):
            new_block = Turtle(shape="square")
            new_block.color("white")
            new_block.penup()
            new_block.goto(x=self.x_pos, y=self.y_pos)
            self.body_parts.append(new_block)
            
    def extend_body(self):
        self.x_pos = self.body_parts[-1].xcor()
        self.y_pos = self.body_parts[-1].ycor()
        self.append_block()
         
    def restart(self):
        for body_part in self.body_parts:
            body_part.goto(x=1000,y=1000)
        self.body_parts.clear()
        self.create_snake()

    def move(self):
        for body_part in range(len(self.body_parts) - 1, 0, -1):
            new_x = self.body_parts[body_part - 1].xcor()
            new_y = self.body_parts[body_part - 1].ycor()
            self.body_parts[body_part].goto(new_x, new_y)
        self.body_parts[0].forward(20)
           
            
    def up(self):
        if self.body_parts[0].heading() != 270:
            self.body_parts[0].setheading(90)
        
        
    def down(self):
        if self.body_parts[0].heading() != 90:
            self.body_parts[0].setheading(270)
        
        
    def left(self):
        if self.body_parts[0].heading() != 0:
            self.body_parts[0].setheading(180)
        
        
    def right(self):
        if self.body_parts[0].heading() != 180:
            self.body_parts[0].setheading(0)
        
