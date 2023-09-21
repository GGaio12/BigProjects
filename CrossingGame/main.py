import time
from turtle import Screen
from player import Player
from car_manager import CarManager
from scoreboard import Scoreboard
from random import randint

screen = Screen()
screen.setup(width=600, height=600)
screen.title("Crossing Game")
screen.tracer(0)

player = Player()
scoreboard = Scoreboard()
cars = []

screen.listen()
screen.onkeypress(player.move, "Up")

cars_speed = 0.1

game_is_on = True
while game_is_on:
    time.sleep(cars_speed)
    screen.update()
    should_spawn = randint(0,6)
    if should_spawn == 1:
        new_car = CarManager()
        cars.append(new_car)
    for car in cars:
        car.move()
        if car.xcor() < -340:
            cars.remove(car)
        if player.distance(car) < 30 and player.ycor() > -250 and player.ycor() < 250 and car.ycor() - 25 < player.ycor() < car.ycor() + 20:
            screen.update()
            scoreboard.game_over()
            game_is_on = False
    if player.ycor() == 280:
        scoreboard.level += 1
        cars_speed *= 0.7
        scoreboard.update_level()
        player.next_level()
           
screen.exitonclick()