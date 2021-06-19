from tkinter import *
from tkinter import messagebox

class MonthlyBudget:

    def __init__(self, budget_inputs, budget_percentages, budget_categories, budget_limit):
        self.budget_inputs = budget_inputs
        self.budget_percentages = budget_percentages
        self.budget_categories = budget_categories
        self.budget_limit = budget_limit
        self.spending_list = []
        self.spending_total = 0
        for i in range(len(budget_inputs)):
            self.to_be_added = [j for j in [budget_inputs[i].split(',')]]
            self.spending_total += int(self.to_be_added[i-i][3])
            self.spending_list.append([self.to_be_added[i-i][0], self.to_be_added[i-i][1], self.to_be_added[i-i][2], self.to_be_added[i-i][3]])

    def categorize_spending(self):

        self.food_spendings = []
        self.drink_spendings = []
        self.clothing_spendings = []
        self.electronic_spendings = []
        self.home_spendings = []

        for i in range(len(self.spending_list)):

            if self.spending_list[i][2] == " Yiyecek":
                self.food_spendings.append(self.spending_list[i])
            elif self.spending_list[i][2] == " Icecek":
                self.drink_spendings.append(self.spending_list[i])
            elif self.spending_list[i][2] == " Giyim":
                self.clothing_spendings.append(self.spending_list[i])
            elif self.spending_list[i][2] == " Elektronik":
                self.electronic_spendings.append(self.spending_list[i])
            elif self.spending_list[i][2] == " Ev":
                self.home_spendings.append(self.spending_list[i])
        
        self.food_total, self.drink_total, self.clothing_total, self.electronic_total, self.home_total = 0, 0, 0, 0, 0
        self.food_limit = self.budget_limit * (int(self.budget_percentages[0]) / 100)
        self.drink_limit = self.budget_limit * (int(self.budget_percentages[1]) / 100)
        self.clothing_limit = self.budget_limit * (int(self.budget_percentages[2]) / 100)
        self.electronic_limit = self.budget_limit * (int(self.budget_percentages[3]) / 100)
        self.home_limit = self.budget_limit * (int(self.budget_percentages[4]) / 100)

        for i in range(len(self.spending_list)):

            if self.spending_list[i][2] == " Yiyecek":
                if(self.food_total > self.food_limit):
                    self.food_total += int(self.spending_list[i][3])
                    continue
                else:
                    self.food_total += int(self.spending_list[i][3])
                if(self.food_total > self.food_limit):
                    self.food_excess_index = i
            elif self.spending_list[i][2] == " Icecek":
                if(self.drink_total > self.drink_limit):
                    self.drink_total += int(self.spending_list[i][3])
                    continue
                else:
                    self.drink_total += int(self.spending_list[i][3])
                if(self.drink_total > self.drink_limit):
                    self.drink_excess_index = i
            elif self.spending_list[i][2] == " Giyim":
                if(self.clothing_total > self.clothing_limit):
                    self.clothing_total += int(self.spending_list[i][3])
                    continue
                else:
                    self.clothing_total += int(self.spending_list[i][3])
                if(self.clothing_total > self.clothing_limit):
                    self.clothing_excess_index = i
            elif self.spending_list[i][2] == " Elektronik":
                if(self.electronic_total > self.electronic_limit):
                    self.electronic_total += int(self.spending_list[i][3])
                    continue
                else:
                    self.electronic_total += int(self.spending_list[i][3])
                if(self.electronic_total > self.electronic_limit):
                    self.electronic_excess_index = i
            elif self.spending_list[i][2] == " Ev":
                if(self.home_total > self.home_limit):
                    self.home_total += int(self.spending_list[i][3])
                    continue
                else:
                    self.home_total += int(self.spending_list[i][3])
                if(self.home_total > self.home_limit):
                    self.home_excess_index = i

        self.category_usage_percentages = [round(self.food_total / self.food_limit * 100, 2), round(self.drink_total / self.drink_limit * 100, 2),
        round(self.clothing_total / self.clothing_limit * 100, 2), round(self.electronic_total / self.electronic_limit * 100, 2), round(self.home_total / self.home_limit * 100, 2)]
    
    def limit_excess(self):

        if (self.food_total > self.food_limit):
                          
            food_msg = "This spending (\"{}\") excesses the limit in the following category -> \"Yiyecek\" (Spending Amount: {}, Categoric Budget Limit: {}, Used Categoric Budget: {})".format(self.spending_list[self.food_excess_index][1].strip(), self.spending_list[self.food_excess_index][3].strip(), int(self.food_limit), self.food_total)
            messagebox.showerror(title = "Limit Excess", message = food_msg)
        if (self.drink_total > self.drink_limit):
            drink_msg = "This spending (\"{}\") excesses the limit in the following category -> \"İçecek\" (Spending Amount: {}, Categoric Budget Limit: {}, Used Categoric Budget: {})".format(self.spending_list[self.drink_excess_index][1].strip(), self.spending_list[self.drink_excess_index][3].strip(), int(self.drink_limit), self.drink_total)
            messagebox.showerror(title = "Limit Excess", message = drink_msg)
        if (self.clothing_total > self.clothing_limit):
            clothing_msg = "This spending (\"{}\") excesses the limit in the following category -> \"Giyim\" (Spending Amount: {}, Categoric Budget Limit: {}, Used Categoric Budget: {})".format(self.spending_list[self.clothing_excess_index][1].strip(), self.spending_list[self.clothing_excess_index][3].strip(), int(self.clothing_limit), self.clothing_total)
            messagebox.showerror(title = "Limit Excess", message = clothing_msg)
        if (self.electronic_total > self.electronic_limit):
            electronic_msg = "This spending (\"{}\") excesses the limit in the following category -> \"Elektronik\" (Spending Amount: {}, Categoric Budget Limit: {}, Used Categoric Budget: {})".format(self.spending_list[self.electronic_excess_index][1].strip(), self.spending_list[self.electronic_excess_index][3].strip(), int(self.electronic_limit), self.electronic_total)
            messagebox.showerror(title = "Limit Excess", message = electronic_msg)
        if (self.home_total > self.home_limit):
            home_msg = "This spending (\"{}\") excesses the limit in the following category -> \"Ev\" (Spending Amount: {}, Categoric Budget Limit: {}, Used Categoric Budget: {})".format(self.spending_list[self.home_excess_index][1].strip(), self.spending_list[self.home_excess_index][3].strip(), int(self.home_limit), self.home_total)
            messagebox.showerror(title = "Limit Excess", message = home_msg)

class SpendingGUI(Frame, MonthlyBudget):

    def __init__(self, parent, budget_inputs, budget_percentages, budget_categories, budget_limit):
        Frame.__init__(self, parent)
        MonthlyBudget.__init__(self, budget_inputs, budget_percentages, budget_categories, budget_limit)
        self.parent = parent
        self.second_frame = Frame(self.parent)
        self.second_frame.pack(side = BOTTOM)
        self.initUI()

    def initUI(self):
        self.parent.title("Spending Report")
        self.frame1()
        self.frame2()
    
    def frame1(self):
        self.listbox = Listbox(self, selectmode = "single")
        self.import_ = Button(self, text = "Import", command = self.import_)
        self.remove_selected = Button(self, text = "Remove Selected", command = self.remove_selected)
        self.remove_all = Button(self, text = "Remove All", command = self.remove_all)
        self.listbox.pack(fill = BOTH, expand = True)
        self.import_.pack(side = LEFT)
        self.remove_selected.pack(side = LEFT)
        self.remove_all.pack(side = LEFT)
        self.pack(fill = BOTH, expand = True)

    def frame2(self):
        self.canvas_width = 120*len(self.budget_percentages)-20
        self.canvas_height = 400
        self.canvas = Canvas(self.second_frame, width = self.canvas_width, height = self.canvas_height)
        self.canvas.pack()
    
    def bar_diagram(self):

        self.categorize_spending()

        self.bar_length = []
        self.rec_obj = []
        self.txt_obj = []
        self.increment = 0

        for i in range(len(self.category_usage_percentages)):
            self.length = (self.canvas_height*self.category_usage_percentages[i])/100
            self.bar_length.append(self.length)

            self.rec_obj.append(self.canvas.create_rectangle(0+self.increment, 0, 100+self.increment, self.bar_length[i], fill = "red"))
            self.txt_obj.append(self.canvas.create_text(50+self.increment, 390, text = self.category_usage_percentages[i], fill = "red"))

            if (self.bar_length[i] != self.canvas_height):
                self.canvas.move(self.rec_obj[i], 0, self.canvas_height-self.bar_length[i])

            self.increment += 120
        
        self.canvas.bind("<Enter>", self.show_percentage)
        self.canvas.bind("<Leave>", self.hide_percentage)
        self.canvas.bind("<Button 1>", self.make_bar_blue)
        self.canvas.bind("<ButtonRelease 1>", self.make_bar_red)

    def import_(self):
        self.listbox.delete(0, END)
        for input_ in self.spending_list:
            row = "{}, {}, {}, {}".format(input_[0], input_[1], input_[2], input_[3])
            self.listbox.insert(END, row)
        self.canvas.delete("all")
        self.bar_diagram()
        self.limit_excess()

    def remove_selected(self):
        del self.spending_list[self.listbox.curselection()[0]]
        self.listbox.delete(self.listbox.curselection())
        self.canvas.delete("all")
        self.bar_diagram()

    def remove_all(self):
        self.spending_list.clear()
        self.listbox.delete(0, END)
        self.canvas.delete("all")
        self.bar_diagram()

    def show_percentage(self, event):

        for i in range(len(self.budget_percentages)):
            self.canvas.itemconfig(self.txt_obj[i], fill = "white")

    def hide_percentage(self, event):

        for i in range(len(self.budget_percentages)):
            self.canvas.itemconfig(self.txt_obj[i], fill = "red")

    def make_bar_blue(self, event):
        self.canvas.itemconfig(self.canvas.find_closest(event.x, event.y), fill = "blue")
    
    def make_bar_red(self, event):
        self.canvas.itemconfig(self.canvas.find_closest(event.x, event.y), fill = "red")