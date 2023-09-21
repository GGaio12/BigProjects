from turtle import Turtle

class Paddle(Turtle):
    def __init__(self, x, y):
        super().__init__()
        self.shape("square")
        self.speed("fastest")
        self.penup()
        self.shapesize(stretch_wid=5, stretch_len=1)
        self.color("white")
        self.x_pos = x
        self.y_pos = y
        self.goto(x=self.x_pos, y=self.y_pos)
        
    def move_up(self):
        self.y_pos += 20
        self.goto(x=self.x_pos, y=self.y_pos)
        
    def move_down(self):
        self.y_pos -= 20
        self.goto(x=self.x_pos, y=self.y_pos)


