import time

def main():

    print("Graph Representation Program".center(95, "*"))

    print("\nThe graph which the adjacency matrix and adjacency list of it showed below is the one\ntaken from the \"COE207-AI-L3-Problem-Solving-Search-Strategies.pdf\" file slide number 50.\n")

    print("Important: The numbers at the beginning of each line in the adjacency matrix is the node number,\nthey're not the part of the adjacency matrix itself!\n")

    print("Adjacency matrix and adjacency list of the specified graph are shown below\n")

    print(95*"*")

    ad_matrix = [[0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0], [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0], [4, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0],
    [5, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0], [6, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0], [7, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
    [8, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0], [9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1], [10, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
    [11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1], [12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0]]

    ad_list = [[0, 1, 2, 5, 6], [1, 0], [2, 0], [3, 4, 5], [4, 3, 5, 6], [5, 0, 3, 4], [6, 0, 4], [7, 8], [8, 7], [9, 10, 11, 12], [10, 9], [11, 9, 12], [12, 9, 11]]

    print("\nAdjacency Matrix:\n")

    def draw_matrix():
        for i in range(0, len(ad_matrix)):
            print(ad_matrix[i])
    
    draw_matrix()

    print("\nAdjacency List:\n")

    def draw_list():
        for i in range(0, len(ad_list)):
            print(ad_list[i])
    
    draw_list()

    def any_other():
        any_op = int(input("Do you want to add or remove any more nodes?(1 Add Node / 2 Remove Node / 3 Exit):"))

        if any_op == 1:
            add_node()
        elif any_op == 2:
            rm_node()
        elif any_op == 3:
            exit()
        else:
            print("Your entry is invalid, try again...")
            time.sleep(2)
            any_other()

    def add_node():
        new_node = int(input("Enter the number of the node that you want to add:"))

        ins_new_nd = []

        ins_new_nd.append(new_node)

        for i in range(len(ad_matrix)):
            new_rel = int(input("Enter the relation of the new node with respect to node {} (type 1 for connected, 0 for not):".format(i)))
            ins_new_nd.append(new_rel)
        
        ad_matrix.append(ins_new_nd)

        new_list = []
        new_list.append(new_node)
        new_node_ref = ad_matrix[len(ad_matrix)-1][1:]

        global iter
        iter = 0
        
        for i in range(len(ad_matrix)):  
            ad_matrix[i].append(new_node_ref[iter])
            iter += 1
            if iter == len(new_node_ref):
                ad_matrix[len(ad_matrix)-1].append(0)
                break

        for i in range (len(new_node_ref)):
            if new_node_ref[i] == 1:
                new_list.append(i)
    
        ad_list.append(new_list)

        for i in ad_list[len(ad_list)-1][1:]:
            for j in range (1, len(ad_list)):
                if i == ad_list[j-1][0]:
                    ad_list[j-1].append(new_node)

        print("Please wait, adding node {}".format(new_node))
        time.sleep(2) 
        print("\nAdjacency Matrix:\n")
        draw_matrix()
        print("\nAdjacency List:\n")
        draw_list()

        print("\nNode {} has been added successfully. New adjacency matrix and list have been generated above...".format(new_node))
        any_other()

    def rm_node():
        rmd_node = int(input("Enter the number of the node that you want to remove:"))

        global se
        se = 0

        for i in range (len(ad_matrix)):
            se += 1
            if rmd_node == ad_matrix[se][0]:
                del ad_matrix[se]
                break
            
        for i in range(len(ad_matrix)):
            del ad_matrix[i-1][rmd_node+1]
        
        for i in range(len(ad_list)):
           for j in range(len(ad_list[i-1])): 
                if rmd_node == ad_list[i-1][j-1]:
                    del ad_list[i-1][j-1]
                elif rmd_node == ad_list[i-1][0]:
                    del ad_list[i-1]
           
        print("Please wait, removing node {}".format(rmd_node))
        time.sleep(2)
        print("\nAdjacency Matrix:\n")
        draw_matrix()
        print("\nAdjacency List:\n")
        draw_list()
        print("\nNode {} has been removed successfully. New adjacency matrix and list have been generated above...".format(rmd_node))
        any_other()

    print("\nSelect your operation:\n")

    print("1) Add node (vertex)\n2) Remove node (vertex)\n3) Exit")

    op_sel = int(input("\nSelection:"))

    if op_sel == 1:
        add_node()
    elif op_sel == 2:
        rm_node()
    elif op_sel == 3:
        exit()
    else:
        print("Your entry is invalid, returning back to the main menu...")
        time.sleep(2)
        main()

main()