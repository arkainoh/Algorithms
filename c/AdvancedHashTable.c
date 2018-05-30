#include <stdio.h>
#include <malloc.h>
#define BUCKETS 5
#define NODES 3

typedef struct _treeNode* TreeNode;
typedef struct _treeNode {
  int key, val;
  TreeNode left, right, parent;
} treeNode;

typedef struct _binarySearchTree {
  TreeNode root;
  int size;
} binarySearchTree;
typedef binarySearchTree* BinarySearchTree;

typedef struct _advancedHashTable {
  BinarySearchTree bucket[BUCKETS];
  int valid[BUCKETS];
  int used[BUCKETS];
  int size;
} advancedHashTable;
typedef advancedHashTable* AdvancedHashTable;

AdvancedHashTable newAdvancedHashTable() {
  AdvancedHashTable ret = (AdvancedHashTable)malloc(sizeof(advancedHashTable));
  for(int i = 0; i < BUCKETS; i++) {
    ret->valid[i] = 0;
    ret->bucket[i] = NULL;
    ret->used[i] = 0;
  }
  ret->size = 0;
  return ret;
}

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
  ret->left = ret->right = ret->parent = NULL;
  return ret;
}

int getHash(int data) {
  return data;
}

int getBucket(int key) {
  return getHash(key) % BUCKETS;
}

int isFullAdvancedHashTable(AdvancedHashTable aht) {
  return aht->size == BUCKETS * NODES;
}

int isEmptyAdvancedHashTable(AdvancedHashTable aht) {
  return !aht->size;
}

TreeNode _put(BinarySearchTree bst, TreeNode root, int key, int val, int* added) {
  if(!root) {
    if(bst->size == NODES) return NULL;
    bst->size++;
    *added = 1;
    return newTreeNode(key, val);
  }

  if(key < root->key) {
    TreeNode l = _put(bst, root->left, key, val, added);
    if(l) l->parent = root;
    root->left = l;
  }
  else if(key > root->key) {
    TreeNode r = _put(bst, root->right, key, val, added);
    if(r) r->parent = root;
    root->right = r;
  }
  else {
    root->val = val;
    *added = 1;
  }
  return root;
}

int put(BinarySearchTree bst, int key, int val) {
  int added = 0;
  bst->root = _put(bst, bst->root, key, val, &added);
  return added;
}

void add(AdvancedHashTable aht, int key, int val) {
  int bucket = getBucket(key), added = 0, prev_size;
  while(!added) {
    if(aht->bucket[bucket] && aht->bucket[bucket]->size) {
      prev_size = aht->bucket[bucket]->size;
      added = put(aht->bucket[bucket], key, val);
      aht->size += aht->bucket[bucket]->size - prev_size;
    }
    else {
      if(!aht->bucket[bucket]) aht->bucket[bucket] = newBinarySearchTree();
      added = put(aht->bucket[bucket], key, val);
      aht->size++;
    }
    bucket = (bucket + 1) % BUCKETS;
  }
}

TreeNode _search(BinarySearchTree bst, int key) {
  TreeNode iter = bst->root;
  while(iter) {
    if(key < iter->key) iter = iter->left;
    else if(key > iter->key) iter = iter->right;
    else return iter;
  }
  return NULL;
}

int search(AdvancedHashTable aht, int key) {
  int bucket = getBucket(key), cnt = 0;
  TreeNode tmp;
  while(aht->bucket[bucket] && aht->bucket[bucket]->size) {
    if(cnt == BUCKETS) return -1;
    tmp = _search(aht->bucket[bucket], key);
    if(tmp) return tmp->val;
    cnt++;
    bucket = (bucket + 1) % BUCKETS;
  }

  return -1;
}

void removeTreeNode(TreeNode root) {
  if(!root) return;
  removeTreeNode(root->left);
  removeTreeNode(root->right);
  free(root);
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

TreeNode _floor(TreeNode root, int key) {
  TreeNode iter = root, tmp = NULL;
  while(iter) {
    if(key < iter->key) iter = iter->left;
    else if(key > iter->key) {
      tmp = _floor(root->right, key);
      if(tmp) return tmp;
      break;
    } else return iter;
  }
  return iter;
}

TreeNode _ceiling(TreeNode root, int key) {
  TreeNode iter = root, tmp = NULL;
  while(iter) {
    if(key > iter->key) iter = iter->right;
    else if(key < iter->key) {
      tmp = _ceiling(root->left, key);
      if(tmp) return tmp;
      break;
    } else return iter;
  }
  return iter;
}

TreeNode getFloor(BinarySearchTree bst, int key) {
  return _floor(bst->root, key);
}

TreeNode getCeiling(BinarySearchTree bst, int key) {
  return _ceiling(bst->root, key);
}

void removeBinarySearchTree(BinarySearchTree bst) {
  removeTreeNode(bst->root);
  bst = NULL;
}

void _printInorder(TreeNode tn) {
  if(!tn) return;
  _printInorder(tn->left);
  printf("(%d, %d) ", tn->key, tn->val);
  _printInorder(tn->right);
}

void printInorder(BinarySearchTree bst) {
  if(!bst) return;
  _printInorder(bst->root);
  printf("\n");
}

void printAdvancedHashTable(AdvancedHashTable aht) {
  for(int bucket = 0; bucket < BUCKETS; bucket++) {
    printf("bucket[%d]: ", bucket);
    printInorder(aht->bucket[bucket]);
  }
}

void removeAdvancedHashTable(AdvancedHashTable aht) {
  for(int bucket = 0; bucket < BUCKETS; bucket++)
    if(aht->bucket[bucket]) removeBinarySearchTree(aht->bucket[bucket]);
  free(aht);
  aht = NULL;
}

void testAdvancedHashTable() {
  AdvancedHashTable aht = newAdvancedHashTable();
  if(isEmptyAdvancedHashTable(aht)) printf("AdvancedHashTable is empty\n");
  else printf("AdvancedHashTable is not empty\n");

  int keys[] = {1, 46, 2, 45, 23, 73, 12, 64, 11, 16, 21, 21, 33, 13, 23, 14, 24, 29};
  int vals[] = {64, 23, 14, 54, 25, 95, 21, 43, 3, 2, 4, 7, 31, 22, 15, 13, 52, 21};

  for(int i = 0; ; i++) {
    if(!isFullAdvancedHashTable(aht)) {
      add(aht, keys[i], vals[i]);
      printf("add(%d, %d)\n", keys[i], vals[i]);
    }
    else {
      printf("AdvancedHashTable is full\n");
      break;
    }
  }
  printf("\n");
  printf("<AdvancedHashTable>\n");
  printf("size: %d\n", aht->size);
  printAdvancedHashTable(aht);
  printf("\n");
  printf("search(%d): %d\n", 45, search(aht, 45));
  printf("search(%d): %d\n", 21, search(aht, 21));
  printf("search(%d): %d\n", 7, search(aht, 7));
  printf("search(%d): %d\n", 73, search(aht, 73));
  removeAdvancedHashTable(aht);
}

int main() {
  testAdvancedHashTable();
  return 0;
}