# Basic Calculator in Python [Programmed by Ahmed Taha Ergin - 190726069]

# First we define operation functions (summation, subtraction, multiplication and divison).
# And we return them to have the result.

def add(number1, number2):
     return number1+number2 

def subtract(number1, number2):
     return number1-number2 

def multiply(number1, number2):
    return number1*number2

def divide(number1, number2):
    if number2 == 0:
        print("You can't divide by zero!") #When the user does division and enters 0 as the second number, the calculator will give an error!
    else:
        return number1/number2

# The calculator is going to ask "What is your desired operation?".

def basic_calculator():

    print("--------------------------------")
    print("Welcome to the Basic Calculator!") # Also a warm welcome!
    print("--------------------------------") 
    print("What is your desired operation?")
    print("1)Summation (+)")
    print("2)Subtraction (-)")
    print("3)Multiplication (*)")
    print("4)Division (/)")
    print("5)Exit the Basic Calculator")


    # User is going to select the desired operation.

    desired_operation = input("Select operation (1/2/3/4/5):") #User input

    # User is going to plug the desired numbers to the calculator.
    # I plug "float" to also print the decimal places.

    if desired_operation == "1":
     number1 = float(input("Enter the first number:"))
     number2 = float(input("Enter the second number:"))
     
    elif desired_operation == "2":
     number1 = float(input("Enter the first number:"))
     number2 = float(input("Enter the second number:"))

    elif desired_operation == "3":
     number1 = float(input("Enter the first number:"))
     number2 = float(input("Enter the second number:"))
     
    elif desired_operation == "4":
     number1 = float(input("Enter the first number:"))
     number2 = float(input("Enter the second number:"))
      
    elif desired_operation == "5":
     exit()
            
    else:
     print("Input invalid! Returning to the main screen.") #If the user enters a character other than 1,2,3,4 or 5; the calculator will give an error!
     basic_calculator()

    # The calculator gives the result according to the selected operation by user.

    if desired_operation == "1":
     print(number1, "+" , number2, "=", add(number1, number2))

    elif desired_operation == "2":
     print(number1, "-" , number2, "=", subtract(number1, number2))

    elif desired_operation == "3":
     print(number1, "*" , number2, "=", multiply(number1, number2))

    elif desired_operation == "4":
     print(number1, "/" , number2, "=", divide(number1, number2))
     

    #Start of the loop for if there are any other calculations to be done.

    print("Do you have any other calculations?")   

    other_calc = input("Yes (1) or No (0):") #User input

    if other_calc == "1": #If user says "Yes", the main menu of the calculator will reappear.
        basic_calculator()
    elif other_calc == "0":
        exit()
    else:
        print("Enter 1 or 0!") #If user enters something other than 1 or 0, the calculator will warn the user to enter 1 or 0!
        
      
  
basic_calculator()
