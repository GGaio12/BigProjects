from turtle import Turtle

class Player(Turtle):
    def __init__(self):
        super().__init__()
        self.shape("classic")
        self.color("yellow")
        self.penup()
        self.goto(x= 0, y=0)
        self.shapesize(stretch_len=2, stretch_wid=2)
        self.spd = 2.5
        self.look = 1

    def gravity(self, reductor):
        if 75 <= self.heading() <= 290:
            pass
        else:
            heading = self.heading()
            self.setheading(heading - self.look*reductor)
            self.look += 0.75
        self.goto(x=0, y=self.ycor()-self.spd*reductor)
        if self.spd < 50:
            self.spd *= 1.05
        else:
            self.spd *= 1.01
             
    def boost(self):
        self.goto(x=0, y=self.ycor()+100)
        if self.ycor() > 400:
           self.goto(x=0, y=400) 
        self.spd = 5
        self.setheading(40)
        self.look = 1
        
