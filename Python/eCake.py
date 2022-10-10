#Author: Nick Chandler
#Date: 1/31/2021
#Description: A3- eCake... Creates a digital cake based on cmd line inputs

#Usage:

#Argument 1 inputs # of rows
#Argument 2 inputs triangle side length
#Argument 3 inputs the number of candles (age)
#Argument 4 inputs whether(True) or not(False) to have stripes

#Variable bank and imports
import turtle
import sys
import random
import math

#input variables
rows = int(sys.argv[1])
triangle = int(sys.argv[2])
age = int(sys.argv[3])
stripes = str(sys.argv[4])

#Assigns boolean values to "stripes" variable
sTrue = "True" or "true" or "t"
sFalse = "False" or "false" or "f"
if stripes == sFalse:
    stripes = False
if stripes == sTrue:
    stripes = True

#Misc. Variables
color = ["green", "red", "purple"]  #color
stripeNum = 0  #used for determining stripe color
rc1 = color[0]
rc2 = color[1]
rc3 = color[2]

#Dimension variables
candleHigh = (3 * triangle)  #Candle height
candleWide = (rows * triangle / age / 2)  #Candle width
triangleHigh = (triangle * math.sqrt(3) / 2)  #Triangle height
cakeWide = (((age * 2) * candleWide) + candleWide)  #Cake width based on the width of candles 
cakeHigh = (candleHigh + (rows * triangleHigh))  #Cake height
triangleNumber = math.ceil((cakeWide / triangle)) #Number of triangles
actualCakeWide = (triangleNumber * triangle) #cake body width based on triangle width
candleCenter = (actualCakeWide - cakeWide) # difference in candle width and cake width

#turtle creation
wn = turtle.Screen()
dw = turtle.Turtle()
turtle.tracer(0,0)

#turtle positions itself in bottom left corner of the cake
dw.penup()
dw.setheading(180)
dw.forward((cakeWide / 2))
dw.setheading(270)
dw.forward(cakeHigh / 2)
dw.setheading(0)
dw.pendown()
dw.color(color[0])

#Draw cake body
for i in range(rows):
    triangleCounter = 0
    #Draws line the height of a triangle on the left border
    dw.setheading(90)
    dw.forward(triangleHigh)
    dw.backward(triangleHigh)
    dw.setheading(0)
    #Draws a triangle
    for x in range(triangleNumber):
        dw.forward(triangle)
        dw.left(120)
        dw.forward(triangle)
        dw.left(120)
        dw.forward(triangle)
        dw.left(120)
        dw.forward(triangle)
    #Draws a line across the top of the triangles
    dw.setheading(90)
    dw.forward(triangleHigh)
    dw.setheading(180)
    dw.forward(triangle * triangleNumber)
    dw.setheading(90)
    #Decides whether or not to follow stripe pattern
    if stripes == False:
        dw.color(random.choice(color))
    if stripeNum < 2 and stripes == True:
        stripeNum += 1
    else:
        if stripes == True:
            stripeNum = 0
    if stripeNum == 1 and stripes == True:
        dw.color(rc2)
    elif stripeNum == 2 and stripes == True:
        dw.color(rc3)
    elif stripeNum == 0 and stripes == True:
        dw.color(rc1)
        
#Candle script:
dw.setheading(0)
dw.penup()
dw.forward((candleCenter / 2))
for i in range(age):
    dw.pendown()
    dw.color("orange")
    dw.forward(candleWide)
    dw.left(90)
    dw.forward(candleHigh)
    dw.right(90)
    dw.forward((candleWide/2))
    dw.dot()
    dw.forward((candleWide/2))
    dw.right(90)
    dw.forward(candleHigh)
    dw.left(90)
dw.forward(candleWide)
dw.hideturtle()
turtle.update()


##Figure out update and tracer!


