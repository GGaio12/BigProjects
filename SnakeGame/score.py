from turtle import Turtle

FONT = ('Courier New', 20, 'normal')
ALIGNMENT = "center"

class Score(Turtle):
    
    def __init__(self):
        super().__init__()
        with open("Snake_Game\Snake_Game_Data.txt") as high_score_tracker:
            self.high_score = int(high_score_tracker.read())
        self.points = 0
        self.penup()
        self.goto(x=0, y=265)
        self.pencolor("white")
        self.hideturtle()
        self.write_score()
        
    def write_score(self):
        self.clear()
        self.write(f"Score: {self.points}  High Score: {self.high_score}", move=False, align=ALIGNMENT, font=FONT)
        
    def restart(self):
        if self.points > self.high_score:
            self.high_score = self.points
            with open("Snake_Game\Snake_Game_Data.txt", mode="w") as high_score_tracker:
                high_score_tracker.write(str(self.points))
        self.points = 0
        self.write_score()
    
    def add_score(self):
        self.points += 1
        self.write_score()
        