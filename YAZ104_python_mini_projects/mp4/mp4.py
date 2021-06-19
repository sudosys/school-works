import tkinter as tk
import math, random, sys
from tkinter import scrolledtext
from tkinter import messagebox
from collections import Counter, OrderedDict
from io import StringIO

def read_from_terminal(function):
    def wrapper(*args,**kwargs):
        old_stdout = sys.stdout
        sys.stdout = mystdout = StringIO()
        function(*args, **kwargs)
        sys.stdout = old_stdout
        contents = mystdout.getvalue()
        mystdout.close()
        return contents
    return wrapper

class DataExtractCluster(tk.Frame):

    def __init__(self, parent, width, height):
        tk.Frame.__init__(self, parent)
        self.parent = parent
        self.width = width
        self.height = height
        self.first_frame = tk.Frame(self.parent, width = self.width, height = self.height)
        self.second_frame = tk.Frame(self.parent, width = self.width, height = self.height)
        self.first_frame.pack()
        self.second_frame.pack()
        self.initUI()
        self.categories_listbox.bind("<<ListboxSelect>>", self.category_selection)
        self.category1 = None
        self.category2 = None
        self.first_selected_index = None

    def initUI(self):
        self.parent.title("Data Extraction and Clustering")
        self.frame1()
        self.frame2()

    def frame1(self):
        self.button_label = tk.Label(self.first_frame, text = "You can import the given file by using this button:")
        self.txt_button = tk.Button(self.first_frame, text = "Select TXT File", command = self.fill_category)
        self.button_label.pack(side = tk.LEFT)
        self.txt_button.pack(side = tk.LEFT)
    
    def frame2(self):
        self.clustering_screen = tk.Label(self.second_frame, text = "Clustering Screen", font = ("Helvetica", 18, "bold"))
        self.categories = tk.Label(self.second_frame, text = "Select 2 Categories:")
        self.categories_listbox = tk.Listbox(self.second_frame, selectmode = "multiple", exportselection = 0, width = 40)
        self.clustering_type = tk.IntVar()
        self.hierarchical_clustering_rbutton = tk.Radiobutton(self.second_frame, text = "Hierarchical Clustering", variable = self.clustering_type, value = 1)
        self.kmeans_clustering_rbutton = tk.Radiobutton(self.second_frame, text = "K-means Clustering", variable = self.clustering_type, value = 2)
        self.kmeans_cluster_amount_label = tk.Label(self.second_frame, text = "Amount of K-means Clusters")
        self.kmeans_cluster_amount = tk.IntVar()
        self.kmeans_cluster_amount_entry = tk.Entry(self.second_frame, textvariable = self.kmeans_cluster_amount)
        self.cluster_button = tk.Button(self.second_frame, text = "Cluster!", command = lambda: self.cluster("cust_seg.txt", self.category1, self.category2))
        self.cluster_scrolledtextbox = scrolledtext.ScrolledText(self.second_frame)
        self.clustering_screen.place(x = 270, y = 30)
        self.categories.place(x = 120, y = 90)
        self.categories_listbox.place(x = 53, y = 120)
        self.hierarchical_clustering_rbutton.place(x = 330, y = 160)
        self.kmeans_clustering_rbutton.place(x = 330, y = 220)
        self.kmeans_cluster_amount_label.place(x = 480, y = 190)
        self.kmeans_cluster_amount_entry.place(x = 500, y = 223)
        self.cluster_button.place(x = 650, y = 180)
        self.cluster_scrolledtextbox.place(x = 0, y = 290, width = self.width, height = self.height-315)

    def preprocess_txt(self, filename, category1 = None, category2 = None, fill_category = 0):
        
        txt_file = open(filename, "r")

        txt_file_content = txt_file.readlines()

        self.preprocessed_txt = {}

        self.categories = [category for category in txt_file_content[0].split(",")]

        if fill_category == 0:
            cat1_index = self.categories.index(category1)
            cat2_index = self.categories.index(category2)

            txt_cat_key_pairs =  []

            general_inner_keys = set()
            
            del txt_file_content[0]

            for row in txt_file_content:

                txt_cat_key_pairs.append("{},{}".format(row.split(",")[cat1_index],row.split(",")[cat2_index]))

                general_inner_keys.add(row.split(",")[cat2_index])

            number_of_occurrences = dict(Counter(txt_cat_key_pairs))
            
            for key, value in number_of_occurrences.items():

                cat1_key = key.split(",")[0]
                cat2_key = key.split(",")[1]

                try:
                    self.preprocessed_txt[cat1_key].update({cat2_key : value})
                except KeyError:
                    self.preprocessed_txt[cat1_key] = {cat2_key : value}
            
            for key, value in self.preprocessed_txt.items():

                cat2_inner_keys = set(value.keys())

                non_existing_keys = general_inner_keys - cat2_inner_keys

                if len(non_existing_keys) == 0:
                    continue

                for non_existing_key in non_existing_keys:

                    try:
                        self.preprocessed_txt[key].update({non_existing_key : 0})
                    except KeyError:
                        self.preprocessed_txt[key] = {non_existing_key : 0}
                
            for key in self.preprocessed_txt:

                temp = self.preprocessed_txt[key]

                self.preprocessed_txt[key] = dict(OrderedDict(sorted(temp.items())))

            return self.preprocessed_txt   
        else:
            return self.categories
    
    def fill_category(self):

        categories = self.preprocess_txt("cust_seg.txt", fill_category = 1)

        self.categories_listbox.delete(0, tk.END)

        for kategori in categories:
            self.categories_listbox.insert(tk.END, kategori)
    
    def pearson_correlation(self, v1, v2):

        sum1 = sum(v1)
        sum2 = sum(v2)

        sqare_sum1 = sum([v**2 for v in v1])
        sqare_sum2 = sum([v**2 for v in v2])

        product_sum = sum([v1[i]*v2[i] for i in range(len(v1))])

        numerator = product_sum - ((sum1*sum2)/len(v1))

        denominator = math.sqrt(((sqare_sum1-(sum1**2))/len(v1))*((sqare_sum2-(sum2**2))/len(v1)))

        if denominator == 0:
            return 0

        self.r = numerator/denominator

        return 1-self.r

    class bicluster:

        def __init__(self, vec, left = None, right = None, distance = 0.0, id = None):
            self.left = left
            self.right = right
            self.vec = vec
            self.id = id
            self.distance = distance

    def hcluster(self, rows):

        distances = {}
        current_clust_id = -1

        self.clust = [self.bicluster(rows[i], id = i) for i in range(len(rows))]

        while len(self.clust) > 1:

            lowest_pair = (0,1)
            closest_distance = self.pearson_correlation(self.clust[0].vec, self.clust[1].vec)

            for i in range(len(self.clust)):
                for j in range(i+1, len(self.clust)):

                    if (self.clust[i].id,self.clust[j].id) not in distances:
                        distances[(self.clust[i].id,self.clust[j].id)] = self.pearson_correlation(self.clust[i].vec, self.clust[j].vec)
                    
                    selected_distance = distances[(self.clust[i].id,self.clust[j].id)]

                    if selected_distance < closest_distance:
                        closest_distance = selected_distance
                        lowest_pair = (i, j)
            
            merge_vec = [(self.clust[lowest_pair[0]].vec[i]+self.clust[lowest_pair[1]].vec[i])/2.0 for i in range(len(self.clust[0].vec))]

            new_cluster = self.bicluster(merge_vec, left = self.clust[lowest_pair[0]], right = self.clust[lowest_pair[1]], distance = closest_distance, id = current_clust_id)

            current_clust_id -= 1

            del self.clust[lowest_pair[1]]
            del self.clust[lowest_pair[0]]

            self.clust.append(new_cluster)
        
        return self.clust[0]

    @read_from_terminal
    def printcluster_from_terminal(self, clust, labels, n = 0):
        self.print_clust(clust, labels, n)
    
    def print_clust(self, clust, labels = None, n = 0):

        for _ in range(n):
            print("\t".expandtabs(2), end = "")
        
        if clust.id < 0:

            print("-")
        else:

            if labels == None:
               print(clust.id)
            else:
                print(labels[clust.id])
        
        if clust.left != None:
            self.print_clust(clust.left, labels = labels, n = n+1)
        
        if clust.right != None:
            self.print_clust(clust.right, labels = labels, n = n+1)

    def prepare_data(self, filename, category1, category2):
    
        data, rows, columns = [], [], []
        temp_list = []

        preprocessed_txt = self.preprocess_txt(filename, category1, category2)

        for key, value in preprocessed_txt.items():
            
            rows.append(key)

            temp_list = []
            
            for innerkey in value.keys():
                
                columns.append(innerkey)

                temp_list.append(preprocessed_txt[key][innerkey])

            data.append(temp_list)
        
        del data[0]
        data.append(temp_list)

        return data, rows, columns

    def category_selection(self, cat = None):

        categories = self.preprocess_txt("cust_seg.txt", fill_category = 1)
        
        current_selections = list(self.categories_listbox.curselection())
        
        if len(current_selections) == 1:
            self.first_selected_index = current_selections[0]
            self.category1 = categories[current_selections[0]]
        else:
            if self.first_selected_index < current_selections[-1]:
                del current_selections[0]
            else:
                del current_selections[-1]
            self.category2 = categories[current_selections[0]]

    def kcluster(self, rows, k = None):

        k = self.kmeans_cluster_amount.get()
        
        ranges = [(min([row[i] for row in rows]), max([row[i] for row in rows])) for i in range(len(rows[0]))]

        clusters = [[random.random()*(ranges[i][1]-ranges[i][0])+ranges[i][0] for i in range(len(rows[0]))] for j in range(k)]

        lastmatches = None

        for _ in range(100):

            bestmatches = [[] for i in range(k)]

            for j in range(len(rows)):

                row = rows[j]
                bestmatch = 0

                for i in range(k):
                    d = self.pearson_correlation(clusters[i], row)
                    if d < self.pearson_correlation(clusters[bestmatch], row):
                        bestmatch = i
                
                bestmatches[bestmatch].append(j)
            
            if bestmatches == lastmatches:
                break

            lastmatches = bestmatches

            for i in range(k):

                avgs = [0.0]*len(rows[0])

                if len(bestmatches[i]) > 0:
                    for rowid in bestmatches[i]:
                        for m in range(len(rows[rowid])):
                            avgs[m] += rows[rowid][m]
                    for j in range(len(avgs)):
                        avgs[j] /= len(bestmatches[i])
                    clusters[i] = avgs
        
        return bestmatches
    
    def hierarchical_clustering(self, filename, category1, category2):

        data, rows, _ = self.prepare_data(filename, category1, category2)

        clust = self.hcluster(data)
        
        contents = self.printcluster_from_terminal(clust, rows)

        for content in contents:
            self.cluster_scrolledtextbox.insert(tk.END, content)

    def kmeans_clustering(self, filename, category1, category2):

        self.cluster_scrolledtextbox.delete(1.0, tk.END)
        
        data, rows, _ = self.prepare_data(filename, category1, category2)
        
        kclust = self.kcluster(data)
        
        for item in range(len(kclust)):
            line = "{} {}\n".format(item, [rows[r] for r in kclust[item]])
            self.cluster_scrolledtextbox.insert(tk.INSERT, line)
    
    def cluster(self, filename, category1, category2):

        if (len(self.categories_listbox.curselection()) > 2): messagebox.showerror(title = "Error", message = "You have selected more than 2 categories!")

        self.cluster_scrolledtextbox.delete(1.0, tk.END)

        if self.clustering_type.get() == 1:
            self.hierarchical_clustering(filename, category1, category2)
        elif self.clustering_type.get() == 2:
            self.kmeans_clustering(filename, category1, category2)