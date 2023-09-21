from turtle import Turtle

class Scoreboard(Turtle):
    def __init__(self):
        super().__init__()
        self.hideturtle()
        self.color("white")
        self.penup()
        self.l_score = 0
        self.r_score = 0
    
    def show_scoreboard(self):
        self.goto(-100, 200)
        self.write(self.l_score, align="center", font=("Courier", 60, "normal"))
        self.goto(100, 200)
        self.write(self.r_score, align="center", font=("Courier", 60, "normal"))

    def game_over(self):
        self.goto(x=0, y=0)
        self.write("GAME OVER!", move=False, align="center", font=("Courier", 60, "normal"))

