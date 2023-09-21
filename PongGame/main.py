from turtle import Screen, Turtle
from paddle import Paddle
from ball import Ball
from scoreboard import Scoreboard
import time

screen = Screen()
screen.bgcolor("black")
screen.setup(height=600, width=800)
screen.title("Pong Game")
screen.tracer(0)

r_paddle = Paddle(x=350, y=0)
l_paddle = Paddle(x=-350, y=0)
ball = Ball()
scoreboard = Scoreboard()

screen.listen()
screen.onkeypress(r_paddle.move_up, "Up")
screen.onkeypress(r_paddle.move_down, "Down")
screen.onkeypress(l_paddle.move_up, "w")
screen.onkeypress(l_paddle.move_down, "s")

over=False
while not over:
    time.sleep(ball.move_speed)
    scoreboard.clear()
    scoreboard.show_scoreboard()
    screen.update()
    ball.move()
    
    if ball.ycor() > 280 or ball.ycor() < -280:
        ball.bounce_y()

    if ball.xcor() > 325 and ball.distance(r_paddle) < 60 or ball.xcor() < -325 and ball.distance(l_paddle) < 60:
        ball.bounce_x()
        ball.add_speed()
        
    if ball.xcor() > 400:
        scoreboard.l_score += 1
        ball.restart()
        
    if ball.xcor() < -400:
        scoreboard.r_score += 1
        ball.restart()
        
    if scoreboard.r_score == 5 or scoreboard.l_score == 5:
        over = True
        scoreboard.clear()
        scoreboard.show_scoreboard()
        scoreboard.game_over()

screen.exitonclick()