from tkinter import *
from tkinter import messagebox
import csv, sqlite3, math

class SpendingSuggestion(Frame):

    def __init__(self, parent, width, height):
        Frame.__init__(self, parent)
        self.parent = parent
        self.width = width
        self.height = height
        self.username = "User"
        self.user_included_data = self.fetch_from_database(create_data=1)
        self.first_frame = Frame(self.parent, width = self.width, height = self.height)
        self.second_frame = Frame(self.parent, width = self.width, height = self.height)
        self.third_frame = Frame(self.parent, width = self.width, height = self.height)
        self.first_frame.pack()
        self.second_frame.pack()
        self.third_frame.pack()
        self.initUI()

    def initUI(self):
        self.parent.title("Spending Suggestion System")
        self.frame1()
        self.frame2()
        self.frame3()
        self.fetch_from_database()

    def frame1(self):
        self.button_label = Label(self.first_frame, text = "You can import other users by using this button:")
        self.csv_button = Button(self.first_frame, text = "Select CSV File", command = self.csv_categories_import)
        self.button_label.pack(side = LEFT)
        self.csv_button.pack(side = LEFT)
    
    def frame2(self):
        self.user_info = Label(self.second_frame, text = "User Informations", font = ("Helvetica", 18, "bold"))
        self.categories = Label(self.second_frame, text = "Categories")
        self.total_amount = Label(self.second_frame, text = "Total Amount")
        self.user_spendings = Label(self.second_frame, text = "User Spendings")
        self.categories_listbox = Listbox(self.second_frame, selectmode = "single", width = 32)
        self.total_amount_var = DoubleVar()
        self.total_amount_entry = Entry(self.second_frame, textvariable = self.total_amount_var)
        self.total_amount_entry.delete(0, "end")
        self.total_amount_button = Button(self.second_frame, text = " Add ", command = self.add_total_spending)
        self.user_spendings_listbox = Listbox(self.second_frame, selectmode = "single", width = 40)
        self.user_info.grid(row = 0, column = 1, pady = 20)
        self.categories.grid(row = 1, column = 0, padx = 80, pady = 10)
        self.total_amount.grid(row = 1, column = 1, padx = 80, pady = 10)
        self.user_spendings.grid(row = 1, column = 3, padx = 80, pady = 10)
        self.categories_listbox.grid(row = 2, column = 0, padx = 80, pady = 10)
        self.total_amount_entry.grid(row = 2, column = 1)
        self.total_amount_button.place(x = 458, y = 220)
        self.user_spendings_listbox.grid(row = 2, column = 3, padx = 80, pady = 10)

    def frame3(self):
        self.suggestion_section = Label(self.third_frame, text = "Suggestion Section", font = ("Helvetica", 18, "bold"))
        self.suggestions = Label(self.third_frame, text = "Suggestions")
        self.suggestions_listbox = Listbox(self.third_frame, selectmode = "single", width = 40)
        self.shops = Label(self.third_frame, text = "Shops")
        self.shops_listbox = Listbox(self.third_frame, selectmode = "single", width = 40)
        self.suggestion_type = IntVar()
        self.category_based = Radiobutton(self.third_frame, text = "Cat. Based Suggestion", variable = self.suggestion_type, value = 1)
        self.shop_based = Radiobutton(self.third_frame, text = "Shop Based Suggestion", variable = self.suggestion_type, value = 2)
        self.suggestion_button = Button(self.third_frame, text = "        Suggest        ", command = lambda: self.suggestions_listbox_import(self.user_included_data, self.username, self.cosine_similarity))
        self.similar_shop_button = Button(self.third_frame, text = "Find Similar Shop", command = lambda: self.shop_listbox_import(self.user_included_data, self.username, self.cosine_similarity))
        self.suggestion_section.place(x = 370, y = 0)
        self.category_based.place(x = 70, y = 150)
        self.suggestion_button.place(x = 230, y = 150)
        self.shop_based.place(x = 70, y = 200)
        self.similar_shop_button.place(x = 230, y = 200)
        self.suggestions.place(x = 460, y = 50)
        self.suggestions_listbox.place(x = 380, y = 100)
        self.shops.place(x = 725, y = 50)
        self.shops_listbox.place(x = 630, y = 100)
    
    def preprocess(self, item, is_file = 1):
        
        if is_file == 1:
            csv_file = open(item, "r")
            read_content = csv.reader(csv_file)
        elif is_file == 0:
            read_content = item

        content = []

        self.preprocessed = {}

        self.categories, companies = {}, {}

        category_sum = 0

        increment = 0

        for row in read_content:
            content.append(row)
        else:
            if is_file == 1:
                del content[0]

        content.sort()

        for row in content:
            self.categories.setdefault(row[0], 0)
            companies.setdefault(row[1], 0)

        for key in self.categories.keys():
            self.categories[key] = increment
            increment += 1
        else:
            increment = 0

        for key in companies.keys():
            companies[key] = increment
            increment += 1

        self.categories = {value : key for key, value in self.categories.items()}
        companies = {value : key for key, value in companies.items()}

        cat_inc, com_inc = 0, 0

        for row in content:
            while(True):
                if row[0] == self.categories[cat_inc] and row[1] == companies[com_inc] and float(row[3]) > 0:
                    category_sum += float(row[3])
                    if content[-1] == row:
                        try:
                            self.preprocessed[companies[com_inc]].update({self.categories[cat_inc] : category_sum})
                        except KeyError:
                            self.preprocessed[companies[com_inc]] = {self.categories[cat_inc] : category_sum}
                        category_sum = 0
                    break
                elif float(row[3]) < 0:
                    break
                elif row[0] == self.categories[cat_inc] and row[1] != companies[com_inc]:
                    try:
                        self.preprocessed[companies[com_inc]].update({self.categories[cat_inc] : category_sum})
                    except KeyError:
                        self.preprocessed[companies[com_inc]] = {self.categories[cat_inc] : category_sum}
                    category_sum = 0
                    com_inc += 1
                    if com_inc > len(companies):
                        com_inc = 0
                elif row[0] != self.categories[cat_inc] and row[1] == companies[com_inc]:
                    try:
                        self.preprocessed[companies[com_inc]].update({self.categories[cat_inc] : category_sum})
                    except KeyError:
                        self.preprocessed[companies[com_inc]] = {self.categories[cat_inc] : category_sum}
                    category_sum = 0
                    cat_inc += 1
                    if cat_inc > len(self.categories):
                        cat_inc = 0
                elif row[0] != self.categories[cat_inc] and row[1] != companies[com_inc]:
                    try:
                        self.preprocessed[companies[com_inc]].update({self.categories[cat_inc] : category_sum})
                    except KeyError:
                        self.preprocessed[companies[com_inc]] = {self.categories[cat_inc] : category_sum}
                    category_sum = 0
                    cat_inc += 1
                    if cat_inc > len(self.categories):
                        cat_inc = 0
                    com_inc = 0
        
        return self.preprocessed

    def csv_categories_import(self):
        self.categories_listbox.delete(0, END)
        self.preprocess("kredikarti_veri.csv")
        for category in self.categories.values():
            self.categories_listbox.insert(END, category)
    
    def add_total_spending(self):
        try:
            self.spending_input = self.categories[self.categories_listbox.curselection()[0]] + ": " + str(self.total_amount_var.get())
            self.user_spendings_listbox.insert(END, self.spending_input)
            self.database_sync()
            self.total_amount_entry.delete(0, "end")
        except IndexError:
            messagebox.showwarning(title = "Error", message = "You didn't choose any category!")
    
    def database_sync(self):

        db_connection = sqlite3.connect("kullanıcı.db")

        cursor = db_connection.cursor()

        create_table_command = """CREATE TABLE IF NOT EXISTS toplam_harcamalar(kategori TEXT, toplam_miktar REAL)"""

        cursor.execute(create_table_command)

        data_input = """INSERT INTO toplam_harcamalar(kategori, toplam_miktar) VALUES(?, ?)"""

        cursor.execute(data_input, (self.categories[self.categories_listbox.curselection()[0]], self.total_amount_var.get()))

        db_connection.commit()

        db_connection.close()
    
    def fetch_from_database(self, create_data = 0):

        db_connection = sqlite3.connect("kullanıcı.db")

        cursor = db_connection.cursor()

        fetch = """SELECT * FROM toplam_harcamalar"""

        try:
            cursor.execute(fetch)
        except sqlite3.OperationalError:
            return

        all_data = cursor.fetchall()

        if create_data == 0:

            for data in all_data:
                self.spending_input = data[0] + ": " + str(data[1])
                self.user_spendings_listbox.insert(END, self.spending_input)

        elif create_data == 1:
            
            user_data = []

            for data in all_data:
                user_data.append([data[0], self.username, "01/01/2014", str(data[1])])
            
            preprocessed_user = self.preprocess(user_data, is_file = 0)

            preprocessed_csv = self.preprocess("kredikarti_veri.csv")

            preprocessed_csv[self.username] = preprocessed_user[self.username]

            self.user_included_data = preprocessed_csv

            return self.user_included_data

        db_connection.close()
    
    def cosine_similarity(self, data, entity1, entity2):

        intersection = {entity for entity in data[entity1] if entity in data[entity2]}

        entity1_amounts = {entity : amount for entity, amount in data[entity1].items() if entity in data[entity2]}
        entity2_amounts = {entity : amount for entity, amount in data[entity2].items() if entity in data[entity1]}

        if len(intersection) == 0:
            return 0

        amount_dot_product = 0

        for entity in intersection:
            amount_dot_product += entity1_amounts[entity]*entity2_amounts[entity]

        entity1_norm = math.sqrt(sum(square_value**2 for square_value in entity1_amounts.values()))
        entity2_norm = math.sqrt(sum(square_value**2 for square_value in entity2_amounts.values()))

        self.cos_sim = amount_dot_product/(entity1_norm*entity2_norm)

        return self.cos_sim

    def get_recommendations(self, data, entity, similarity_function, top = 3):

        totals, sim_sums = {}, {}

        for other in data:

            if other == entity:
                continue
                
            similarity =  similarity_function(data, entity, other)

            if similarity <= 0:
                continue

            for item in data[other]:

                if item not in data[entity] or data[entity][item] == 0:

                    totals.setdefault(item, 0)
                    totals[item] += data[other][item] * similarity
                    
                    sim_sums.setdefault(item, 0)
                    sim_sums[item] += similarity
        
        recommendations = [(total / sim_sums[item], item) for item, total in totals.items()]

        recommendations.sort()
        recommendations.reverse()
        return recommendations[0:top]
    
    def swap_data(self, data):

        self.swapped = {}

        for entity in data:
            for item in data[entity]:
                self.swapped.setdefault(item, {})
                self.swapped[item][entity] = data[entity][item]
        
        return self.swapped

    def calc_similar_items(self, data, similarity_function, n = 3):

        top_matches = {}

        item_data = self.swap_data(data)

        for item in item_data:

            totals = self.top_matches(item_data, item, similarity_function, top = n)

            top_matches[item] = totals
        
        return top_matches

    def get_recommended_items(self, data, sim_items, entity):
        
        user_totals = data[entity]
        totals, sim_sums = {}, {}

        for (item, total) in user_totals.items():

            for (similarity, item2) in sim_items[item]:

                if item2 in user_totals:
                    continue

                totals.setdefault(item2, 0)
                totals[item2] += similarity * total

                sim_sums.setdefault(item2, 0)
                sim_sums[item2] += similarity

        spendings = [(total / sim_sums[item], item) for item, total in totals.items()]

        spendings.sort()
        spendings.reverse()

        return spendings
    
    def top_matches(self, data, entity, similarity_function, top = 3):

        top_matches = [(similarity_function(data, entity, other), other) for other in data if other != entity]

        top_matches.sort()
        top_matches.reverse()

        return top_matches[0:top]

    def shop_listbox_import(self, data, entity, similarity_function, top = 3):

        top_matches = self.top_matches(data, entity, similarity_function, top)

        self.shops_listbox.delete(0, END)

        for match in top_matches:
            shop_input = match[1] + ": " + str(match[0])
            self.shops_listbox.insert(END, shop_input)

    def suggestions_listbox_import(self, data, entity, similarity_function, top = 3):

        if self.suggestion_type.get() == 1: # Category Based Suggestion

            similar_items = self.calc_similar_items(self.user_included_data, similarity_function)

            recommendations = self.get_recommended_items(data, similar_items, entity)

            self.suggestions_listbox.delete(0, END)

            for recommendation in recommendations:
                suggestion_input = recommendation[1] + ": " + str(recommendation[0])
                self.suggestions_listbox.insert(END, suggestion_input)

        elif self.suggestion_type.get() == 2: # Shop Based Suggestion

            recommendations = self.get_recommendations(data, entity, similarity_function, top)

            self.suggestions_listbox.delete(0, END)

            for recommendation in recommendations:
                suggestion_input = recommendation[1] + ": " + str(recommendation[0])
                self.suggestions_listbox.insert(END, suggestion_input)