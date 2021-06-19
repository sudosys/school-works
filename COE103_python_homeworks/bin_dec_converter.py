import math

print("-------------------------------------------")
print("Welcome to the Binary <> Decimal Converter!")
print("-------------------------------------------")

def converter():

    choice = int(input("•Decimal to Binary(1)\n•Binary to Decimal(2)\nSelect an action:"))
    
    def dec2bin():

        print("---------------------------")
        print("Decimal to Binary Converter")
        print("---------------------------")

        ini_dec_num = int(input("Enter a decimal number to convert to binary:"))

        bin_val = ""

        dec_num = ini_dec_num

        while dec_num > 0:

            remainder = dec_num % 2
            bin_val = bin_val + str(remainder)
            dec_num = math.floor(dec_num / 2)

        bin_val = bin_val[::-1]

        print(ini_dec_num, "in binary:", bin_val)

        any_other()

    def bin2dec():

        print("---------------------------")
        print("Binary to Decimal Converter")
        print("---------------------------")

        binary_val = input("Enter a binary number to convert to decimal:")

        rev_binary_val = binary_val[::-1]

        decimal_val = 0

        exp = 0

        for i in rev_binary_val:

            decimal_val = decimal_val + (int(i) * (2 ** exp))

            exp = exp + 1

        print(binary_val, "in decimal:", decimal_val)

        any_other()


    def any_other():
        
       print("Do you have any other conversions to do?")

       other_conversion = int(input("Yes(1) or No(2):"))

       if other_conversion == 1:
           
           print("------------------------------------------------")
           print("Welcome back to the Binary <> Decimal Converter!")
           print("------------------------------------------------")

           return converter()
        
       elif other_conversion == 2:

           exit()

       else:

           print("Enter (1) or (2)!")
        
               
    if choice == 1:

        dec2bin()

    elif choice == 2:
        
        bin2dec()

    else:
        print("Invalid entry! Enter 1 or 2")
        return converter()


converter()
