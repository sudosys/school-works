from mp4 import *

def main():

    root = tk.Tk()

    window_width, window_height = 750, 750

    root.geometry("{}x{}".format(window_width,window_height))

    app = DataExtractCluster(root, window_width, window_height)

    app.mainloop()

main()