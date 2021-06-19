from mp5 import *

def main():

    root = tk.Tk()

    window_width, window_height = 1200, 530

    root.geometry("{}x{}".format(window_width,window_height))

    app = DataScrapeFilter(root, window_width, window_height)

    app.mainloop()

main()