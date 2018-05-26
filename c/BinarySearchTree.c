#include <stdio.h>
#include <malloc.h>

typedef struct _treeNode* TreeNode;
typedef struct _treeNode {
	int key, val;
	TreeNode left, right;
} treeNode;

typedef struct _binarySearchTree {
	TreeNode root;
	int size;
} binarySearchTree;
typedef binarySearchTree* BinarySearchTree;

BinarySearchTree newBinarySearchTree() {
	BinarySearchTree ret = (BinarySearchTree)malloc(sizeof(binarySearchTree));
	ret->root = NULL;
	ret->size = 0;
	return ret;
}

TreeNode newTreeNode(int key, int val) {
  TreeNode ret = (TreeNode)malloc(sizeof(treeNode));
  ret->key = key;
  ret->val = val;
  ret->left = ret->right = NULL;
  return ret;
}

TreeNode _put(BinarySearchTree bst, TreeNode root, int key, int val) {
	if(!root) {
		bst->size++;
		return newTreeNode(key, val);
	}

	if(key < root->key) root->left = _put(bst, root->left, key, val);
	else if(key > root->key) root->right = _put(bst, root->right, key, val);
	else root->val = val;
	return root;
}

void put(BinarySearchTree bst, int key, int val) {
	bst->root = _put(bst, bst->root, key, val);
}

void removeTreeNode(TreeNode tn) {
	if(!tn) return;
	removeTreeNode(tn->left);
	removeTreeNode(tn->right);
	free(tn);
}

TreeNode getMin(BinarySearchTree bst) {
	if(!bst->root) return NULL;
	TreeNode iter = bst->root;
	while(iter->left) iter = iter->left;
	return iter;
}

TreeNode getMax(BinarySearchTree bst) {
	if(!bst->root) return NULL;
	TreeNode iter = bst->root;
	while(iter->right) iter = iter->right;
	return iter;
}

void removeBinarySearchTree(BinarySearchTree bst) {
	removeTreeNode(bst->root);
	bst = NULL;
}

void printInorder(TreeNode tn) {
	if(!tn) return;
	printInorder(tn->left);
	printf("(%d, %d) ", tn->key, tn->val);
	printInorder(tn->right);
}

void testBinarySearchTree() {
	BinarySearchTree bst = newBinarySearchTree();
	put(bst, 3, 1);
	put(bst, 2, 4);
	put(bst, 6, 3);
	put(bst, 1, 7);
	put(bst, 2, 5);
	printf("<BinarySearchTree>\n");
	printf("size: %d\n", bst->size);
	printInorder(bst->root);
	printf("\n");
	TreeNode max = getMax(bst);
	TreeNode min = getMin(bst);
	printf("max: (%d, %d)\n", max->key, max->val);
	printf("min: (%d, %d)\n", min->key, min->val);
	removeBinarySearchTree(bst);
}

int main() {
	testBinarySearchTree();
	return 0;
}
