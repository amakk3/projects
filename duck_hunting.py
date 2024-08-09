"""
This is the Template Repl for Python with Turtle.

Python with Turtle lets you make graphics easily in Python.

Check out the official docs here: https://docs.python.org/3/library/turtle.html
"""
########################################################
# Final Project
# CS 111, Reckinger
# TODO: Comment here

import turtle
import random
import image
import threading
from colour import Color

def background():
    
    pass

def foreground():

    pass

b = threading.Thread(name='background', target=background)
f = threading.Thread(name='foreground', target=foreground)

b.start()
f.start()
## Write your code here.
global switch
global killed
global sun
global duck
global score
global scoreboard
global time
global colors
global day_to_night_intervals
killed = False
switch = False

day_to_night_intervals = 20
t = 0
day = Color("#00d4ff")
colors = list(day.range_to(Color("#0b0e7a"),day_to_night_intervals))

def bgcolor():
    global sun
    global time
    if time == 2:
        turtle.bgcolor("deep sky blue")
    elif time == 3:
        turtle.bgcolor("cornflower blue")
    elif time == 4:
        turtle.bgcolor("royal blue")
    elif time == 5:
        turtle.bgcolor("navy")
        
    pass


def Score():
    global score
    global scoreboard
    score += 1
    scoreboard.clear()
    scoreboard.write(f"Score: {score}",
                     False,
                     align='center',
                     font=('Comic Sans MS', 20, 'bold'))
    pass


def add_moon(x, y):
    
    moon = turtle.Turtle()
    moon.shape("moon.gif")
    moon.hideturtle()
    moon.penup()
    moon.goto(x, y)
    moon.showturtle()

def draw_sun(x, y): # FIX
    global sun
    turtle.tracer(0)
    sun = turtle.Turtle()
    sun.penup()
    sun.goto(x, y)
    sun.shape("sun.gif")
    turtle.tracer(1)
    pass


def sun_sets(x, y):
    global sun
    sun = turtle.Turtle()
    sun.shape("sun.gif")
    sun.hideturtle()
    sun.penup()
    sun.goto(x, y)
    sun.showturtle()
    sun.speed(1)
    sun.goto(-x, y)
    print('Rendered sun')
    pass

  
def spawn_ducks(j, k):
    global sun
    global switch
    global time
    while t < day_to_night_intervals:
        print('Time here', t)
        global duck
        duck = turtle.Turtle()
        duck.penup()
        duck.hideturtle()
        x = random.randint(0, 1)
        duck.shape(ducks[x])
        duck.shapesize(10.0, 10.0, 1.0)
        duck.onclick(kill)
        if x == 1:
            duck.goto(400, random.randint(0, 200))
            duck.showturtle()
            duck.speed(1)
            duck.goto(duck.position()[0] - 800, duck.position()[1])
            duck.hideturtle()
        else:
            duck.goto(-400, random.randint(0, 200))
            duck.showturtle()
            duck.speed(1)
            duck.goto(duck.position()[0] + 800, duck.position()[1])
            duck.hideturtle()
    s1.clear()
    #end game logic
    endgame()

def set_interval(func, sec):
    global t
    if t >= day_to_night_intervals - 1:
      return
    def func_wrapper():
        set_interval(func, sec)
        func()
    thread = threading.Timer(sec, func_wrapper)
    thread.start()
    return t

def changeBgColor():
  global t
  s1.bgcolor(
    colors[t].rgb[0],
    colors[t].rgb[1],
    colors[t].rgb[2]
  )
  t += 1
  return

def startgame(x, y):
    global scoreboard
    global score
    global sun

    set_interval(changeBgColor, 5)
  
    score = 0
    s1.clear()
    draw_background()
    spawn_trees()
    s1.bgcolor("sky blue")
    scoreboard = turtle.Turtle()
    scoreboard.penup()
    scoreboard.hideturtle()
    scoreboard.goto(0, 200)
    scoreboard.color("white")
    scoreboard.write(f"Score: {score}",
                     False,
                     align='center',
                     font=('Comic Sans MS', 20, 'bold'))
    if x < -100:
        turtle.shape("Gun.gif")
    if x > -100 and x < 100:
        turtle.shape("Gun2.gif")
    if x > 100:
        turtle.shape("Gun3.gif")
    turtle.penup()
    turtle.goto(200, -200)
    #sun_sets(250, 150)
    spawn_ducks(165, 100)
    # sun_sets(165, 269)
    # END GAME
    pass


def draw_background():
    d = turtle.Turtle()
    turtle.tracer(0)
    d.pendown()
    d.begin_fill()
    d.color("green", "green")
    d.goto(550, -50)
    d.goto(550, -525)
    d.goto(-550, -525)
    d.goto(-550, -50)
    d.goto(0, 0)
    d.end_fill()
    d.hideturtle()
    turtle.tracer(1)
    pass


def spawn_trees():
    trees = ["tree1.gif", "tree2.gif", "tree3.gif"]
    for i in range(0, 50):
        turtle.tracer(0)
        x = random.randint(0, 2)
        tree = turtle.Turtle()
        tree.shape(trees[x])
        tree.penup()
        tree.goto(random.randint(-400, 400), random.randint(-200, 0))
    turtle.tracer(1)
    pass


def kill(x, y):
    global killed
    global duck
    killed = True
    duck.hideturtle()
    turtle.addshape("explosion.gif")
    t = turtle.Turtle()
    t.shape("explosion.gif")
    t.penup()
    t.hideturtle()
    t.goto(x, y)
    t.showturtle()
    turtle.ontimer(Score(), 1000)
    t.hideturtle()
    pass

def endgame():
  end = turtle.Turtle()
  end.shape("endgame.gif")
  end.penup()
  over = turtle.Turtle()
  over.goto(0, 150)
  over.shape("gameover.gif")
  scoreboard.color("black")
  scoreboard.goto(0,0)
  scoreboard.write(f"You Scored: {score}",
                   False,
                   align='center',
                   font=('Comic Sans MS', 20, 'bold'))


s1 = turtle.Screen()
s1.colormode(255)
s1.bgcolor("light blue")
turtle.addshape("duck_l.gif")
turtle.addshape("duck_r.gif")
turtle.addshape("tree1.gif")
turtle.addshape("tree2.gif")
turtle.addshape("tree3.gif")
turtle.addshape("s_Gun.gif")
turtle.addshape("s_Gun2.gif")
turtle.addshape("s_Gun3.gif")
turtle.addshape("Gun.gif")
turtle.addshape("Gun2.gif")
turtle.addshape("Gun3.gif")
turtle.addshape("moon.gif")
turtle.addshape("sun.gif")
turtle.addshape("endgame.gif")
turtle.addshape("gameover.gif")
g = turtle.Turtle()
g.penup()
g.shape("s_Gun.gif")
g.showturtle()
g.penup()
g.goto(-200, -50)
g2 = turtle.Turtle()
g2.penup()
g2.shape("s_Gun2.gif")
g2.showturtle()
g2.penup()
g2.goto(0, -50)
g3 = turtle.Turtle()
g3.penup()
g3.shape("s_Gun3.gif")
g3.showturtle()
g3.penup()
g3.goto(200, -50)
text = turtle.Turtle()
text.penup()
text.hideturtle()
text.goto(0, 100)
text.color("black")
text.write("Pick a gun:",
           False,
           align='center',
           font=('Comic Sans MS', 30, 'bold'))
text.goto(0, 170)
text.write("Let's go duck hunting!",
           False,
           align='center',
           font=('Comic Sans MS', 40, 'underline', 'bold'))
text.goto(-200, -200)
text.color("blue")
text.write("1", False, align='center', font=('Arial', 30, 'bold'))
text.goto(0, -200)
text.color("red")
text.write("2", False, align='center', font=('Arial', 30, 'bold'))
text.goto(200, -200)
text.color("yellow")
text.write("3", False, align='center', font=('Arial', 30, 'bold'))
s1.listen()
guns = ["Gun.gif", "Gun2.gif", "Gun3.gif"]
g.onclick(startgame)
g2.onclick(startgame)
g3.onclick(startgame)
ducks = ["duck_r.gif", "duck_l.gif"]

#
#
#
#

turtle.mainloop()
