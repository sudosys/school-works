import tkinter as tk
from tkinter import scrolledtext
from bs4 import BeautifulSoup
import urllib.request, shelve, re

class DataScrapeFilter(tk.Frame):

    def __init__(self, parent, width, height):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.width = width
        self.height = height
        self.first_frame = tk.Frame(self.parent, width = self.width, height = self.height)
        self.second_frame = tk.Frame(self.parent, width = self.width, height = self.height)
        self.first_frame.pack(side = tk.LEFT)
        self.second_frame.pack(side = tk.RIGHT)
        self.initUI()

    def initUI(self):
        self.parent.title("Data Scraping and Filtering")
        self.frame1()
        self.frame2()
        self.get_fill_categories()

    def frame1(self):
        self.category_label = tk.Label(self.first_frame, text = "Book Categories")
        self.categories_listbox = tk.Listbox(self.first_frame, selectmode = "multiple", width = 40)
        self.price_min_label = tk.Label(self.first_frame, text = "Minimum Price (£ 0-100):")
        self.price_min_scale = tk.Scale(self.first_frame, from_ = 0, to = 100, length = 150, orient = tk.HORIZONTAL)
        self.price_max_label = tk.Label(self.first_frame, text = "Maximum Price (£ 0-100):")
        self.price_max_scale = tk.Scale(self.first_frame, from_ = 0, to = 100, length = 150, orient = tk.HORIZONTAL)
        self.price_max_scale.set(100)
        self.rating_label = tk.Label(self.first_frame, text = "Select Rating:")
        self.options = ["All", "1", "2", "3", "4", "5"]
        self.rating = tk.StringVar()
        self.rating.set("All")
        self.rating_optionmenu = tk.OptionMenu(self.first_frame, self.rating, *self.options, command = self.optionmenu_selection)
        self.show_button = tk.Button(self.first_frame, text = "Show", command = self.fill_textbox)
        # Packing #
        self.category_label.grid(row = 0, column = 0, pady = 10)
        self.categories_listbox.grid(row = 1, column = 0, pady = 10)
        self.price_min_label.grid(row = 2, column = 0, pady = 5)
        self.price_min_scale.grid(row = 3, column = 0, pady = 5)
        self.price_max_label.grid(row = 4, column = 0, pady = 5)
        self.price_max_scale.grid(row = 5, column = 0, pady = 5)
        self.rating_label.grid(row = 6, column = 0, pady = 10)
        self.rating_optionmenu.grid(row = 7, column = 0, pady = 5)
        self.show_button.grid(row = 8, column = 0, pady = 15)

    def frame2(self):
        self.books_scrolledtextbox = scrolledtext.ScrolledText(self.second_frame)
        # Packing #
        self.books_scrolledtextbox.pack()
        self.books_scrolledtextbox.config(width = self.width, height = self.height)

    def optionmenu_selection(self, _): return self.rating.get()

    def get_soup(self, webpage):

        page_content = (urllib.request.urlopen(webpage)).read()

        self.soup = BeautifulSoup(page_content, "html.parser")

        return self.soup

    def get_fill_categories(self, only_categories = 0):

        self.get_soup("http://books.toscrape.com/index.html")

        self.categories = {}
        categories_no_links = []

        for div_element in self.soup.find_all("div", {"class": "side_categories"}):

            a_tags = div_element.find_all("a")
            a_tags.pop(0)

            for a_tag in a_tags: self.categories.update({a_tag.string.strip(): "http://books.toscrape.com/" + a_tag.get("href")})

        for category in self.categories.keys():

            all_listbox_content = self.categories_listbox.get(0, tk.END)
            
            if category not in all_listbox_content: self.categories_listbox.insert(tk.END, category)

            categories_no_links.append(category)

        if only_categories == 0:
            return self.categories
        elif only_categories == 1:
            return categories_no_links

    def get_prices_stars(self, link):

        soup = self.get_soup(link)

        self.prices_stars = []

        book_rating = 0

        for li_element in soup.find_all("li", {"class": "col-xs-6 col-sm-4 col-md-3 col-lg-3"}):

            h3_tags = li_element.find_all("h3")
            prices = li_element.find_all("p", {"class": "price_color"})
            ratings = li_element.find_all("p", {"class": re.compile("^star-rating")})

            for h3_tag in h3_tags: pass

            for price in prices: pass

            for rating in ratings:

                if rating["class"][1] == "One": book_rating = 1
                elif rating["class"][1] == "Two": book_rating = 2
                elif rating["class"][1] == "Three": book_rating = 3
                elif rating["class"][1] == "Four": book_rating = 4
                elif rating["class"][1] == "Five": book_rating = 5

            self.prices_stars.append({"Name": h3_tag.a.get("title"), "Rating": book_rating, "Price": float(price.string[1:])})

        return self.prices_stars

    def create_db(self, db_name):

        self.database = shelve.open(db_name, flag = "c")

    def close_db(self):

        self.database.close()

    def parse(self):

        self.create_db("books.db")

        pile_of_return = []

        categories = self.get_fill_categories()

        for category, category_link in categories.items():

            page_number = 1
            page_link = category_link

            while (True):

                self.get_soup(page_link)

                if (len(self.soup.find_all("li", {"class": "next"})) != 0):

                    if page_number != 1: page_link = category_link[:-10] + "page-{}.html".format(page_number)

                    pile_of_return.extend(self.get_prices_stars(page_link))

                    page_number += 1

                    if page_number == 2: page_link = category_link[:-10] + "page-{}.html".format(page_number)

                else:
                    if page_number == 1 or page_number == 2: pile_of_return.extend(self.get_prices_stars(page_link))
                    break

            self.database[category] = pile_of_return
            pile_of_return = []

        self.close_db()

    def fill_textbox(self):

        self.books_scrolledtextbox.config(state = tk.NORMAL)
        self.books_scrolledtextbox.delete("1.0", tk.END)

        try:
            db = shelve.open("books.db", "r")
        except:
            self.parse()
            db = shelve.open("books.db", "r")

        self.choices = []

        self.only_categories = self.get_fill_categories(only_categories = 1)

        self.optmenu_sel = -1 if self.optionmenu_selection("_") == "All" else self.optionmenu_selection("_")

        if len(self.categories_listbox.curselection()) == 0: self.choices = self.only_categories[:]

        else:

            for index in self.categories_listbox.curselection():
                self.choices.append(self.only_categories[index])

        for key, dict_list in db.items():
            if key not in self.choices: continue
            for dict_ in dict_list:
                if dict_["Price"] > self.price_min_scale.get() and dict_["Price"] < self.price_max_scale.get():
                    if dict_["Rating"] == int(self.optmenu_sel) or self.optmenu_sel == -1:
                        insertion = "Book Name: {} || Price: £{} || Rating: {}\n".format(dict_["Name"], dict_["Price"], dict_["Rating"])
                        self.books_scrolledtextbox.insert(tk.INSERT, insertion)

        self.books_scrolledtextbox.config(state = tk.DISABLED) # To make the textbox read-only.

        db.close()