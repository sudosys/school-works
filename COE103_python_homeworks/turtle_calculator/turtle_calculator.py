# Turtle Calculator in Python [Programmed by Ahmed Taha Ergin - 190726069]
# WARNING: This is NOT the homework itself...
# ...This one is sent to you because of the chance of you may give extra points.

from turtle import * # Here we import "turtle library"
import math # Here I import "math library". (for "math.ceil" command)

# Here I define four mathematical functions (summation, subtraction, multiplication and division).

def add(number1, number2):
    global result # I typed "global" to be able to use it within other functions with no error.
    result = number1+number2
    return result
        
def subtract(number1, number2):
    global result
    result = number1-number2
    return result
        
def multiply(number1, number2):
    global result
    result = number1*number2
    return result
        
def divide(number1, number2):
    global result
    result = int(number1/number2) # I put "int" there to not to get the floating part.
    return result

# Here we define the function called "turtle_calculator"

def turtle_calculator():

    print("----------------------------------")
    print("Welcome to the Turtle Calculator!") # A warm welcome as always.
    print("----------------------------------")

    operation = int(input("1)Summation\n2)Subtraction\n3)Multiplication\n4)Division\nSelect the desired operation (1/2/3/4):")) # User input for the desired operation
        
    # If conditions for the desired operation
        
    if operation == 1:
        number1 = int(input("Enter the first number for summation:")) # User input for the first number
        number2 = int(input("Enter the second number for summation:")) # User input for the second number
        add(number1, number2)

    elif operation == 2:
        number1 = int(input("Enter the first number for subtraction:"))
        number2 = int(input("Enter the second number for subtraction:")) 
        subtract(number1, number2)

    elif operation == 3:
        number1 = int(input("Enter the first number for multiplication:")) 
        number2 = int(input("Enter the second number for multiplication:")) 
        multiply(number1, number2)

    elif operation == 4:
        number1 = int(input("Enter the first number for division:")) 
        number2 = int(input("Enter the second number for division:")) 
        divide(number1, number2)

    else:
        print("You should select one of four operations which listed above\nRestart the program!")
        exit()
 
    num_edges = int(input("Enter the number of edges:")) # User input for the number of edges


    edge_size = int(input("Enter the edge size of the shape:"))


    shape_gap = int(input("Enter the gap between the shapes:"))

    
    global angle
    angle = 360 / num_edges # Here is the "angle" variable. If we divide 360 degrees by the number of edges we get the internal degree of that shape. For instance, 360 / 4 = 90 (internal degree of square)

    def draw_shape(num_edges):

        for i in range(num_edges):
            forward(edge_size)
            left(angle)

    if num_edges > 4:
        shape_gap = shape_gap*(num_edges+(num_edges/2)) # The program tailors the gap between the shapes to not let them collapse.

    def making_gap(shape_gap):

        for i in range(result-(result-1)):
            penup()
            forward(edge_size)
            forward(shape_gap)
            pendown()

    global x
    x = edge_size+shape_gap
    
    def making_canvas(x):
        penup()
        goto(0, -x) # Here this code line lets the "turtle" to move to a specific coordinate when required.
        pendown()

    global iter_count
    iter_count = 0 # I use this variable to be able to draw the relevant canvas sizes.

    global canvas_no
    canvas_no = 1

    global canvas_coeff
    canvas_coeff = iter_count/canvas_no # This is the coefficient of the y component of the "making_canvas" function

    # Here the "canvas_no" value is calculated by taking the square root of result and rounding it up to nearest higher value.

    canvas_no = math.ceil(result ** 0.5)


    print("The program is going to draw" + " " + str(result) + " " + "shape(s) which has/have" + " " +  str(num_edges) + " " + "edge(s)!\n(" + "Shape Size:" + str(edge_size) + " / " + "Shape Gap:" + str(shape_gap) + ")") 

# Here the loop starts to be able to draw the required canvas sizes according to the calculation result.

    for i in range(result):
        iter_count += 1
        canvas_coeff = iter_count/canvas_no
        draw_shape(num_edges)
        making_gap(shape_gap)
        if iter_count % canvas_no == 0:
            making_canvas(canvas_coeff*x)
                
turtle_calculator()
