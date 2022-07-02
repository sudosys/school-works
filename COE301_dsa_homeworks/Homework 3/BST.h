#include "TreeException.h"
#include "TreeNodeBST.h"
typedef void (*FunctionType) (TreeItemType& anItem);

class BinarySearchTree {
   public:
      BinarySearchTree();
      BinarySearchTree(const BinarySearchTree& tree);
      virtual ~BinarySearchTree();

      int height() const;
      int heightRecursive(TreeNode *root) const;

      virtual bool isEmpty() const;

      virtual void searchTreeInsert(const TreeItemType& newItem);

      //////////////////
      virtual void AVLSearchTreeInsert(const TreeItemType& newItem);
      //////////////////

      virtual void searchTreeDelete(KeyType searchKey) throw(TreeException);

      virtual void searchTreeRetrieve(KeyType searchKey, TreeItemType& treeItem) const throw(TreeException);

      virtual void searchTreeRetrieve(KeyType searchKey, TreeNode*& treeItem) const throw(TreeException);

      virtual void preorderTraverse(FunctionType visit);

      virtual void inorderTraverse(FunctionType visit);

      virtual void postorderTraverse(FunctionType visit);

      virtual TreeNode* getRootPtr() const;

      virtual BinarySearchTree& operator=(const BinarySearchTree& rhs);

   protected:
      void insertItem(TreeNode*& treePtr, const TreeItemType& newItem) throw(TreeException);

      void deleteItem(TreeNode *& treePtr, KeyType searchKey) throw(TreeException);

      void deleteNodeItem(TreeNode *& nodePtr);

      void processLeftmost(TreeNode *& nodePtr, TreeItemType& treeItem);

      void retrieveItem(TreeNode *treePtr, KeyType searchKey, TreeItemType& treeItem) const throw(TreeException);

      void retrieveItem(TreeNode *treePtr, KeyType searchKey, TreeNode*& treeNode) const throw(TreeException);

      void copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const;
      
      void destroyTree(TreeNode *& treePtr);

      void preorder(TreeNode *treePtr, FunctionType visit);
      void inorder(TreeNode *treePtr, FunctionType visit);
      void postorder(TreeNode *treePtr, FunctionType visit);
      
      void setRootPtr(TreeNode *newRoot);

      void getChildPtrs(TreeNode *nodePtr, TreeNode *& leftChildPtr, TreeNode *& rightChildPtr) const;

      void setChildPtrs(TreeNode *nodePtr, TreeNode *leftChildPtr, TreeNode *rightChildPtr);

      //////////////////

      TreeNode* rootPtr() const;

      void findMaxHeight(int item1, int item2, int& maxItem);

      void findBalanceFactor(TreeNode* nodePtr, int& balanceFactor);

      TreeNode* singleLeftRotation(TreeNode* nodePtr);
      TreeNode* singleRightRotation(TreeNode* nodePtr);
      TreeNode* doubleLeftRightRotation(TreeNode* nodePtr);
      TreeNode* doubleRightLeftRotation(TreeNode* nodePtr);

      TreeNode* AVLTreeInsert(TreeNode* nodePtr, const TreeItemType& newItem);

   private:
      TreeNode *root;
};