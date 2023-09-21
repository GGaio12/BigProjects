from turtle import Turtle

ALIGNMENT = "center"
FONT = "Impact", 50, "normal"
FONT_HIGH_SCORE = "Impact", 20, "normal"
FONT_GAME_OVER = "Courier New", 40, "normal"

class Scoreboard(Turtle):
    def __init__(self):
        super().__init__()
        self.penup()
        self.hideturtle()
        self.score = 0
        
    def update_score(self):
        self.clear()
        self.goto(x=0, y=300)
        self.write(f"{int(self.score)}", move=False, align=ALIGNMENT, font=FONT)
        
    def update_high_score(self):
        self.goto(x=-600, y=-350)
        with open(r"Flappy_Bird_Game\data.txt", mode="r") as data_file:
            self.high_score = data_file.read()
        self.write(f"High Score: {int(self.high_score)}", move=False, align=ALIGNMENT, font=FONT_HIGH_SCORE)
        if self.score > float(self.high_score):
            with open(r"Flappy_Bird_Game\data.txt", mode="w") as data_file:
                data_file.write(str(int(self.score)))

    def game_over(self):
        self.goto(x=0, y=0)
        self.write(f"GAME OVER!", move=False, align=ALIGNMENT, font=FONT_GAME_OVER)
        
    def restart_game(self):
        pass
