#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BST.h"

void display(TreeItemType& anItem) {
    std::cout << anItem.getKey() << std::endl;
}

int main() {

    srand(time(NULL));

    BinarySearchTree bst;
    BinarySearchTree bst2;
    
    for (int i = 0; i < 10000; i++) {
        bst.AVLSearchTreeInsert(rand()%10000);
    }

    for (int i = 0; i < 10000; i++) {
        bst2.searchTreeInsert(rand()%10000);
    }

    std::cout << "Height of AVL Tree -> " << bst.height() << std::endl;
    std::cout << "Height of Binary Search Tree -> " << bst2.height() << std::endl;

    return 0;
}
