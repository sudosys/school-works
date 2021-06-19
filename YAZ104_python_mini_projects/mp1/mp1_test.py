import yaml
from mp1 import *

def parse_yaml():

    yaml_file = open("march_budget.yaml", "r")

    parsed_yaml_file = yaml.full_load(yaml_file)

    return parsed_yaml_file

def main():
    
    parsed_yaml_file = parse_yaml()

    budget_inputs = parsed_yaml_file["Butce_Girdileri"]

    budget_categories = parsed_yaml_file["Butce_Kategorileri"].split(",")

    root = Tk()

    root.geometry("700x500")

    app = SpendingGUI(root, budget_inputs, budget_categories)

    app.mainloop()

main()