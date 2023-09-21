from turtle import Screen
from player import Player
from background import Tubes
from scoreboard import Scoreboard
import time


def game():
    screen = Screen()
    #bird = r""
    bg = r"C:\Users\gaioo\OneDrive\Ambiente de Trabalho\Code\Flappy_Bird_Game\bg.gif"
    #tube_shape = r""
    #screen.addshape(bird)
    #screen.addshape(tube_shape)
    screen.title("Flappy Bird")
    screen.bgpic(bg)
    screen.setup(width=1530, height=800, startx=1, starty=1)
    screen.tracer(0)
    
    player = Player()
    #player.shape(bird)
    tubes = Tubes(0, wid=0)
    scoreboard = Scoreboard()

    screen.listen()
    screen.onkey(player.boost, "space")

    game_over = False
    chance = 0
    reductor = 1
    while not game_over:
        time.sleep(tubes.spd)
        screen.update()
        player.gravity(reductor)
        tubes.move()
        scoreboard.update_score()
        scoreboard.update_high_score()

        if chance % 100 == 0:
            tubes.new_tube()
        chance += 1

        for tube in tubes.tubes_in_game:
            if player.xcor() == tube.xcor() + 26:
                scoreboard.score += 0.5
                if tubes.spd >= 0.01:
                    tubes.spd *= 0.98
                    reductor *= 0.9875
                elif tubes.spd > 0.001:
                    tubes.spd *= 0.95
                    reductor *= 0.96755

            if tube.xcor() - 15 <= player.xcor() <= tube.xcor() + 15:
                if player.distance(tube) <= tube.distance_center:
                    screen.update()
                    scoreboard.update_score()
                    scoreboard.update_high_score()
                    game_over = True
                    scoreboard.game_over()
                    screen.update()
                    
            if player.ycor() <= -380:
                player.goto(x=0, y=-380)
                game_over = True
                screen.update()
                scoreboard.update_score()
                scoreboard.update_high_score()
                scoreboard.game_over()
                screen.update()
    
    time.sleep(2)
    done = False
    while not done:
        restart_question = screen.textinput(title="Restart Game?", prompt="Do you want to restart and try again?(Y/N)\n").lower()
        if restart_question == "y":
            done = True
            screen.clear()
            game()
        elif restart_question == "n":
            done = True

game()