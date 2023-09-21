from turtle import Screen
from snake import Snake
import time
from food import Food
from score import Score

screen = Screen()
screen.setup(width=600, height=600)
screen.bgcolor("black")
screen.title("My Snake Game")
screen.tracer(0)

snake = Snake()
food = Food()
score = Score()

screen.listen()
screen.onkey(snake.up, "Up")
screen.onkey(snake.down, "Down")
screen.onkey(snake.left, "Left")
screen.onkey(snake.right, "Right")

over = False
while not over:
    screen.update()
    time.sleep(0.1)
    
    snake.move()
    
    if snake.body_parts[0].distance(food) < 15:
        food.refresh()
        score.add_score()
        snake.extend_body()
        
    if snake.body_parts[0].xcor() > 280 or snake.body_parts[0].xcor() < -290 or snake.body_parts[0].ycor() > 290 or snake.body_parts[0].ycor() < -280:
        score.restart()
        snake.restart()
       
    for segments in snake.body_parts[1:]:
        if snake.body_parts[0].distance(segments) < 10:
            score.restart()
            snake.restart()
            
        
screen.exitonclick()
