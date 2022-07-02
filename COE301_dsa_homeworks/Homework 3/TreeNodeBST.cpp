#include "TreeNodeBST.h"

int TreeNode::getHeight(TreeNode* nodePtr) {
    if (nodePtr == NULL) { return 0; }
    return nodePtr->height;
}