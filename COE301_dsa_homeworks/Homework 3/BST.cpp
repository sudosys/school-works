#include "BST.h"
#include <cstddef>
#include <iostream>

BinarySearchTree::BinarySearchTree() : root(NULL) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& tree) {
   copyTree(tree.root, root);
}

BinarySearchTree::~BinarySearchTree() {
   destroyTree(root);
}

int BinarySearchTree::height() const {
    return heightRecursive(root);
}

int BinarySearchTree::heightRecursive(TreeNode* root) const {
    int left = 0, right = 0;
    if(root == NULL) {
        return 0;
    }
    else {
        left = heightRecursive(root->leftChildPtr);
        right = heightRecursive(root->rightChildPtr);
        if(left > right)
            return left+1;
        else
            return right+1;
    }
}

bool BinarySearchTree::isEmpty() const {
   return (root == NULL);
}

void BinarySearchTree::searchTreeInsert(const TreeItemType& newItem) {
   insertItem(root, newItem);
}

//////////////////
void BinarySearchTree::AVLSearchTreeInsert(const TreeItemType& newItem) {
   root = AVLTreeInsert(root, newItem);
}
//////////////////

void BinarySearchTree::searchTreeDelete(KeyType searchKey) throw(TreeException) {
   deleteItem(root, searchKey);
}

void BinarySearchTree::searchTreeRetrieve(KeyType searchKey, TreeItemType& treeItem) const throw(TreeException) {
   retrieveItem(root, searchKey, treeItem);
}

void BinarySearchTree::searchTreeRetrieve(KeyType searchKey, TreeNode*& treeNode) const throw(TreeException) {
   retrieveItem(root, searchKey, treeNode);
}

void BinarySearchTree::preorderTraverse(FunctionType visit) {
   preorder(root, visit);
}

void BinarySearchTree::inorderTraverse(FunctionType visit) {
   inorder(root, visit);
}

void BinarySearchTree::postorderTraverse(FunctionType visit) {
   postorder(root, visit);
}

TreeNode* BinarySearchTree::getRootPtr() const {
   rootPtr();
}

void BinarySearchTree::insertItem(TreeNode*& treePtr, const TreeItemType& newItem) throw(TreeException) {
   if (treePtr == NULL) 
      treePtr = new TreeNode(newItem, NULL, NULL);
   else if (newItem.getKey() < treePtr->item.getKey())
      insertItem(treePtr->leftChildPtr, newItem);
   else
      insertItem(treePtr->rightChildPtr, newItem);
}

void BinarySearchTree::deleteItem(TreeNode *& treePtr, KeyType searchKey) throw(TreeException) {
   if (treePtr == NULL)
      throw TreeException("TreeException: delete failed");
   else if (searchKey == treePtr->item.getKey())
      deleteNodeItem(treePtr);
   else if (searchKey < treePtr->item.getKey())
      deleteItem(treePtr->leftChildPtr, searchKey);
   else
      deleteItem(treePtr->rightChildPtr, searchKey);
}

void BinarySearchTree::deleteNodeItem(TreeNode *& nodePtr) {
   TreeNode     *delPtr;
   TreeItemType replacementItem;

   if ( (nodePtr->leftChildPtr == NULL) && (nodePtr->rightChildPtr == NULL)) {
      delete nodePtr;
      nodePtr = NULL;
   } else if (nodePtr->leftChildPtr == NULL) { 
      delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL;
      delete delPtr;
   } else if (nodePtr->rightChildPtr == NULL) {
      delPtr = nodePtr;
      nodePtr = nodePtr->leftChildPtr;
      delPtr->leftChildPtr = NULL;
      delete delPtr;
   }

   else { 
      processLeftmost(nodePtr->rightChildPtr, replacementItem);
      nodePtr->item = replacementItem;
   }
}

void BinarySearchTree::processLeftmost(TreeNode *& nodePtr, TreeItemType& treeItem) {
   if (nodePtr->leftChildPtr == NULL) {
      treeItem = nodePtr->item;
      TreeNode *delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = NULL;
      delete delPtr;
   } else
      processLeftmost(nodePtr->leftChildPtr, treeItem);
}

void BinarySearchTree::retrieveItem(TreeNode *treePtr, KeyType searchKey, TreeItemType& treeItem) const throw(TreeException) {
   if (treePtr == NULL)
      throw TreeException("TreeException: searchKey not found");
   else if (searchKey == treePtr->item.getKey())
      treeItem = treePtr->item;
   else if (searchKey < treePtr->item.getKey())
      retrieveItem(treePtr->leftChildPtr, searchKey, treeItem);
   else
      retrieveItem(treePtr->rightChildPtr, searchKey, treeItem);
}

void BinarySearchTree::retrieveItem(TreeNode *treePtr, KeyType searchKey, TreeNode*& treeNode) const throw(TreeException) {
   if (treePtr == NULL)
      throw TreeException("TreeException: searchKey not found");
   else if (searchKey == treePtr->item.getKey())
      treeNode = treePtr;
   else if (searchKey < treePtr->item.getKey())
      retrieveItem(treePtr->leftChildPtr, searchKey, treeNode);
   else
      retrieveItem(treePtr->rightChildPtr, searchKey, treeNode);
}

void BinarySearchTree::copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const {
   if (treePtr != NULL) {
      newTreePtr = new TreeNode(treePtr->item, NULL, NULL);
      copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
      copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
   } else
      newTreePtr = NULL;
}

void BinarySearchTree::destroyTree(TreeNode *& treePtr) {
   if (treePtr != NULL) { 
      destroyTree(treePtr->leftChildPtr);
      destroyTree(treePtr->rightChildPtr);
      delete treePtr;
      treePtr = NULL;
   }
}

void BinarySearchTree::preorder(TreeNode *treePtr, FunctionType visit) {
   if (treePtr != NULL) { 
      visit(treePtr->item);
      preorder(treePtr->leftChildPtr, visit);
      preorder(treePtr->rightChildPtr, visit);
   }
}

void BinarySearchTree::inorder(TreeNode *treePtr, FunctionType visit) {
   if (treePtr != NULL) {
      inorder(treePtr->leftChildPtr, visit);
      visit(treePtr->item);
      inorder(treePtr->rightChildPtr, visit);
   }
}

void BinarySearchTree::postorder(TreeNode *treePtr, FunctionType visit) {
   if (treePtr != NULL) { 
      postorder(treePtr->leftChildPtr, visit);
      postorder(treePtr->rightChildPtr, visit);
      visit(treePtr->item);
   }
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs) {
   if (this != &rhs) { 
      destroyTree(root);
      copyTree(rhs.root, root);
   }
   return *this;
}

//////////////////
TreeNode* BinarySearchTree::rootPtr() const {
   return this->root;
}

void BinarySearchTree::findMaxHeight(int item1, int item2, int& maxItem) {
   maxItem = (item1 > item2) ? item1 : item2;
}

void BinarySearchTree::findBalanceFactor(TreeNode* nodePtr, int& balanceFactor) {

   if (nodePtr == nullptr) {
      balanceFactor = 0;
   } else {
      balanceFactor = heightRecursive(nodePtr->leftChildPtr) - heightRecursive(nodePtr->rightChildPtr);
   }

}

TreeNode* BinarySearchTree::singleLeftRotation(TreeNode* nodePtr) {
   
   TreeNode* nodePtr2 = nodePtr->rightChildPtr;
   TreeNode* nodePtr3 = nodePtr2->leftChildPtr;

   nodePtr2->leftChildPtr = nodePtr;
   nodePtr->rightChildPtr = nodePtr3;

   int maxHeight;

   findMaxHeight(TreeNode::getHeight(nodePtr->leftChildPtr), TreeNode::getHeight(nodePtr->rightChildPtr), maxHeight);
   
   nodePtr->height = maxHeight + 1;

   findMaxHeight(TreeNode::getHeight(nodePtr2->leftChildPtr), TreeNode::getHeight(nodePtr2->rightChildPtr), maxHeight);
   
   nodePtr2->height = maxHeight + 1;

   return nodePtr2;

}

TreeNode* BinarySearchTree::singleRightRotation(TreeNode* nodePtr) {
   
   TreeNode* nodePtr2 = nodePtr->leftChildPtr;
   TreeNode* nodePtr3 = nodePtr2->rightChildPtr;

   nodePtr2->rightChildPtr = nodePtr;
   nodePtr->leftChildPtr = nodePtr3;

   int maxHeight;

   findMaxHeight(TreeNode::getHeight(nodePtr->leftChildPtr), TreeNode::getHeight(nodePtr->rightChildPtr), maxHeight);

   nodePtr->height = maxHeight + 1;

   findMaxHeight(TreeNode::getHeight(nodePtr2->leftChildPtr), TreeNode::getHeight(nodePtr2->rightChildPtr), maxHeight);

   nodePtr2->height = maxHeight + 1;

   return nodePtr2;

}

TreeNode* BinarySearchTree::doubleLeftRightRotation(TreeNode* nodePtr) {
   nodePtr->leftChildPtr = singleLeftRotation(nodePtr->leftChildPtr);
   return singleRightRotation(nodePtr);
}

TreeNode* BinarySearchTree::doubleRightLeftRotation(TreeNode* nodePtr) {
   nodePtr->rightChildPtr = singleRightRotation(nodePtr->rightChildPtr);
   return singleLeftRotation(nodePtr);
}

TreeNode* BinarySearchTree::AVLTreeInsert(TreeNode* nodePtr, const TreeItemType& newItem) {
   
   if (nodePtr == NULL) {
      return new TreeNode(newItem, NULL, NULL);
   } else if (newItem.getKey() < nodePtr->item.getKey()) {
      nodePtr->leftChildPtr = AVLTreeInsert(nodePtr->leftChildPtr, newItem);
   } else if (newItem.getKey() > nodePtr->item.getKey()) {
      nodePtr->rightChildPtr = AVLTreeInsert(nodePtr->rightChildPtr, newItem);
   } else {
      return nodePtr;
   }

   int maxHeight;

   findMaxHeight(TreeNode::getHeight(nodePtr->leftChildPtr), TreeNode::getHeight(nodePtr->rightChildPtr), maxHeight);

   nodePtr->height = maxHeight + 1;

   int balanceFactor;

   findBalanceFactor(nodePtr, balanceFactor);

   if (balanceFactor < -1 && newItem.getKey() > nodePtr->rightChildPtr->item.getKey()) {
      return singleLeftRotation(nodePtr);
   } else if (balanceFactor > 1 && newItem.getKey() < nodePtr->leftChildPtr->item.getKey()) {
      return singleRightRotation(nodePtr);
   } else if (balanceFactor > 1 && newItem.getKey() > nodePtr->leftChildPtr->item.getKey()) {
      return doubleLeftRightRotation(nodePtr);
   } else if (balanceFactor < -1 && newItem.getKey() < nodePtr->rightChildPtr->item.getKey()) {
      return doubleRightLeftRotation(nodePtr);
   }

   return nodePtr;

}
//////////////////