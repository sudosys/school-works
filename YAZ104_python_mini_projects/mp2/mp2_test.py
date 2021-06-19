import yaml
from mp2 import *

def parse_yaml():

    yaml_file = open("march_budget.yaml", "r")

    parsed_yaml_file = yaml.full_load(yaml_file)

    return parsed_yaml_file

def main():
    
    parsed_yaml_file = parse_yaml()

    budget_inputs = parsed_yaml_file["Butce_Girdileri"]

    budget_percentages = parsed_yaml_file["Butce_Yuzdeleri"].split(",")

    budget_categories = parsed_yaml_file["Butce_Kategorileri"].split(",")

    budget_limit = int(parsed_yaml_file['Kullanici_Bilgileri']['aylik_gelir'])

    root = Tk()
    
    root.geometry("{}x800+400+100".format(120*len(budget_percentages)-20))

    app = SpendingGUI(root, budget_inputs, budget_percentages, budget_categories, budget_limit)

    app.mainloop()

main()