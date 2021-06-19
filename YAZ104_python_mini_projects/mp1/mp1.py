from tkinter import *
from tkinter import messagebox
import pyexcel

class SpendingGUI(Frame):

    def __init__(self, parent, budget_inputs, budget_categories):
        Frame.__init__(self, parent)
        self.budget_inputs = budget_inputs
        self.budget_categories = budget_categories 
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
        self.to_excel = Button(self, text = "Export to Excel", command = self.to_excel)
        self.listbox.pack(fill = BOTH, expand = True)
        self.import_.pack(side = LEFT)
        self.remove_selected.pack(side = LEFT)
        self.remove_all.pack(side = LEFT)
        self.to_excel.pack(side = RIGHT)
        self.pack(fill = BOTH, expand = True)

    def frame2(self):
        self.date = Label(self.second_frame, text = "Date:")
        self.name = Label(self.second_frame, text = "Name:")
        self.category = Label(self.second_frame, text = "Category:")
        self.amount = Label(self.second_frame, text = "Amount:")
        self.date_var = StringVar()
        self.date_box = Entry(self.second_frame, textvariable = self.date_var)
        self.name_var = StringVar()
        self.name_box = Entry(self.second_frame, textvariable = self.name_var)
        self.category_box = Listbox(self.second_frame, selectmode = "single")
        for category in self.budget_categories:
            self.category_box.insert(END, category)
        self.amount_var = StringVar()
        self.amount_box = Entry(self.second_frame, textvariable = self.amount_var)
        self.add = Button(self.second_frame, text = "  Add  ", command = self.add)
        self.date.grid(row = 0, column = 0, padx = 50, pady = 25)
        self.date_box.grid(row = 1, column = 0)
        self.name.grid(row = 0, column = 1, padx = 50, pady = 25)
        self.name_box.grid(row = 1, column = 1)
        self.category.grid(row = 0, column = 2, padx = 50, pady = 25)
        self.category_box.config(height = 0)
        self.category_box.grid(row = 1, column = 2)
        self.amount.grid(row = 0, column = 3, padx = 50, pady = 25)
        self.amount_box.grid(row = 1, column = 3)
        self.add.grid(row = 1, column = 4, padx = 25, pady = 25)

    def import_(self):
        self.listbox.delete(0, END)
        for input in self.budget_inputs:
            self.listbox.insert(END, input)

    def remove_selected(self):
        del self.budget_inputs[self.listbox.curselection()[0]]
        self.listbox.delete(self.listbox.curselection())

    def remove_all(self):
        self.budget_inputs.clear()
        self.listbox.delete(0, END)
    
    def to_excel(self):
        try:
            self.budget_inputs_xls = []
            for i in range(len(self.budget_inputs)):
                self.budget_inputs_xls += [j for j in [self.budget_inputs[i].split(',')]]
            pyexcel.save_as(array = self.budget_inputs_xls, dest_file_name = "budget_inputs.xlsx") # To be able to save it in .xlsx format, "pyexcel-xlsx" module has to be installed along with the "pyexcel" module.
        except:
            messagebox.showerror(title = "Error", message = "An error occured while exporting the budget inputs to Excel!")
        else:                                             
            messagebox.showinfo(title = "Success", message = "Budget inputs have successfully exported to the Excel file!")
                                                            
    def add(self):
        self.budget_input = self.date_var.get() + ", " + self.name_var.get() + ", " + self.budget_categories[self.category_box.curselection()[0]].strip() + ", " + self.amount_var.get()
        self.budget_inputs.append(self.budget_input)
        self.listbox.insert(END, self.budget_input)
        self.date_box.delete(0, "end")
        self.name_box.delete(0, "end")
        self.category_box.selection_clear(0, END)
        self.amount_box.delete(0, "end")