# Author: Nick Chandler
# Date: 2/10/2021
# Description: Draws a sierpinski triangle

import turtle
import random

def turtle_setup(canv_width, canv_height):
    """ Set up the canvas and a turtle for coloring pixels. Return a turtle
        object in hidden state with its pen up. The canvas has size canv_width
        by canv_height, with a coordinate system where (0,0) is in the bottom
        left corner, and automatic re-drawing of the canvas is disabled so that
        turtle.update() must be called to update the drawing.
   """
    
    # create a turtle to color pixels with
    t = turtle.Turtle()

    # set the screen size, coordinate system, and color mode:
    screen = t.getscreen()
    screen.setup(canv_width, canv_height)
    screen.setworldcoordinates(0, 0, canv_width, canv_height)
    turtle.colormode(255) # specify how colors are set: we'll use 0-255
    t.pensize(.5)
    t.up() # lift the pen
    t.hideturtle() # hide the turtle triangle
    t.goto(0,0)
   # screen.tracer(0, 0) # turn off redrawing after each movement

    return t


def midpoint(a, b):
    """ Return the midpoint between points a = (ax, ay) and b = (bx, by)
        Precondition: a and b must be defined.
    """
    ax, ay = a
    bx, by = b
    mx = (ax + bx) / 2
    my = (ay + by) / 2
    return mx, my

def chaosgame(t, canv_width, canv_height, corn):
    """ This function uses the given data to to create the sierpinski triangle.
        Precondition: Screen height/ width are defined. Turtle is defined. Corn ahs been defined.
        Postcondition: The turtle is hidden at origin
    """
    #Corners - via tuple unpacking
    top_corner, left_corner, right_corner = corn
    
    # Let p be a random point in the window
    p = (random.randint(0, (canv_width + 1)), random.randint(0, canv_height + 1))
    corners = [top_corner, left_corner, right_corner]
    turtle.tracer(0,0)
    # loop 10000 times:
    for x in range(10000):
        #c = a random corner of the triangle
        c = corners[random.randint(0,2)]
        #m = the midpoint between p and c
        m = midpoint(p,c)
        #choose a color for m black
        t.pencolor("black")
        #color the pixel at m
        t.goto(m)
        t.pendown()
        t.dot()
        t.penup()
        p = m
    t.penup()
    t.goto(0,0)
    turtle.update()
    
    
def cornerCalculate(canv_width, canv_height):
    """ Takes the dimensions of the canvas and determines
        the three corners of an equilateral triangle.
        Precondition: Canvas height and width must be defined.
        Postcondition: top, left, and right corner are assigned.
    """
    top_corner = midpoint((0, canv_height),(canv_width, canv_height)) #Corner 1
    left_corner = (0,0) #Corner 2
    right_corner = (canv_width,0) #Corner 3
    
    return(top_corner, left_corner, right_corner)
    
    
def main():
    """Main program"""
    import sys
    
    # width and height are given as command line arguments:
    canv_width = int(sys.argv[1]) #Given variable
    canv_height = int(sys.argv[2]) #Given variable
    
    t = turtle_setup(canv_width, canv_height)
    
    #Defines corners (corn is short for corners... I had a list named corners)
    corn = cornerCalculate(canv_width, canv_height) #Corn as in corn-er is where the coordinates fr the corners are stored
    #Runs sierpinski draw funciton
    chaosgame(t, canv_width, canv_height, corn)
    
#this is called a main guard
if __name__ == "__main__":    
    main()
    
    
    
    
    
