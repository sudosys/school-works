#include "KeyedItem.h"
#include <cstddef>
typedef KeyedItem TreeItemType;

class TreeNode {
   public: 
      TreeNode() {}
      TreeNode(const TreeItemType& nodeItem,
               TreeNode *left = NULL, TreeNode *right = NULL) : item(nodeItem), leftChildPtr(left), rightChildPtr(right), height(1) {}

      TreeItemType item;
      TreeNode* leftChildPtr, *rightChildPtr;

      int static getHeight(TreeNode* nodePtr);

      friend class BinarySearchTree;
   private:
      int height;
};