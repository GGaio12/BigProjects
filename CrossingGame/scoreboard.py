from turtle import Turtle

FONT = ("Courier", 24, "normal")


class Scoreboard(Turtle):
    def __init__(self):
        super().__init__()
        self.penup()
        self.hideturtle()
        self.goto(-200, 250)
        self.level = 1
        self.update_level()
    
    def update_level(self):
        self.clear()
        self.write(f"Level: {self.level}", move=False, align="center", font=FONT)
        
    def game_over(self):
        self.goto(x=0, y=0)
        self.write("GAME OVER!", move=False, align="center", font=FONT)