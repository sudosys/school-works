from mp3 import *

def main():

    root = Tk()

    window_width, window_height = 1000, 600

    root.geometry("{}x{}".format(window_width,window_height))

    app = SpendingSuggestion(root, window_width, window_height)

    app.mainloop()

main()