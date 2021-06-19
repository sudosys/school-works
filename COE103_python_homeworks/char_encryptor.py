import random, time, os

def main():

    print("*******************")
    print("Character Encryptor")
    print("*******************")

    choice = input("Encrypt(1)\nDecrypt(2)\nSelect an action to execute:")

    def encrypt():

        item = input("Enter the text to encrypt:")
        encrypt_rate = int(random.randrange(2, 9))
        encrypted_text = ""
        
        for snippet in item:
            
            ascii_code = ord(snippet)
            ascii_code = ascii_code + encrypt_rate
            char_code = chr(ascii_code)
            encrypted_text = encrypted_text + char_code
        encrypted_text = encrypted_text + str(encrypt_rate)

        f = open("encrypted.txt", "w")
        f.write(encrypted_text)
        f.close()
        time.sleep(2)
        print("Text encrypted and saved!")
        time.sleep(1)
        any_other()

    def decrypt():

        print("Do you want to decrypt from the \"encrypted.txt\" or enter a text yourself?")
        encrtxt_user_choice = input("From \"encrypted.txt\"(1)\nEnter text(2)\nSelect an option to continue:")
        if encrtxt_user_choice == "1":
            with open("encrypted.txt", "r") as f_encrtxt:      
                input_item = f_encrtxt.read()
        elif encrtxt_user_choice == "2":
            input_item = input("Enter the text to decrypt:")
        else:
            print("Enter 1 or 2 to continue!")
            return decrypt()

        def split():
            return [char for char in input_item]

        a = [char for char in input_item]

        caesar_decoeff = int(a[-1])

        a.pop()

        item = "".join(a)

        decrypted_text = ""

        for snippet in item:

            ascii_code = ord(snippet)
            ascii_code = ascii_code - caesar_decoeff
            char_code = chr(ascii_code)
            decrypted_text = decrypted_text + char_code

        f = open("decrypted.txt", "w")
        f.write(decrypted_text)
        f.close()
        time.sleep(2)
        print("Text decrypted and saved!")
        time.sleep(1)
        any_other()

    def any_other():
        print("Do you have any other encryption/decryption operation?")
        other = input("Yes(1) or No(2):")
        if other == "1":
            return main()
        elif other == "2":
            print("Program is shutting down...")
            time.sleep(2)
            exit()
        else:
            print("Enter 1 or 2!")

    if choice == "1":
        encrypt()
    elif choice == "2":
        decrypt()
    else:
        print("Enter 1 or 2!")
        return main()

main()
