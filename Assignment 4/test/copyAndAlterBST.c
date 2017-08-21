#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node* getNewNode(int data) {
  /* dynamically allocate memory for a new node */
  struct node* newNode = (struct node*)malloc(sizeof(struct node));

  /* populate data in new Node */
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

/*
This function returns below tree
            1
           / \
         9    12
        / \    \
       4  50    -7
      / \
     18  9
*/
struct node* generateBTree(){
    // Root Node
    struct node* root =  getNewNode(1);

    root->left = getNewNode(9);
    root->right = getNewNode(12);

    root->left->left = getNewNode(4);
    root->left->right = getNewNode(50);
    root->right->right = getNewNode(-7);

    root->left->left->left = getNewNode(18);
    root->left->left->right = getNewNode(9);

    return root;
}

/* Returns a tree which is exact copy of passed tree */
struct node* cloneBinaryTree(struct node *root){
    if(root == NULL)
        return NULL;
    /* create a copy of root node */
    struct node* newNode = getNewNode(root->data);

    //add alterations here

    /* Recursively create clone of left and right sub tree */
    newNode->left = cloneBinaryTree(root->left);
    newNode->right = cloneBinaryTree(root->right);
    /* Return root of cloned tree */
    return newNode;
}

/*
 Prints inOrder Traversal of a binary tree
*/
void inOrderTraversal(struct node *nodeptr){
    if(nodeptr != NULL){
        /* First, recursively prints in Order traversal of left sub-tree */
        inOrderTraversal(nodeptr->left);
        /* Prints current node */
        printf("%d ", nodeptr->data);
        /* Recursively prints in Order traversal of right sub-tree */
        inOrderTraversal(nodeptr->right);
    }
}
int main() {
    struct node *clone, *root = generateBTree();

 /*InOrder traversal of original tree */
    printf("Original Tree\n");
    inOrderTraversal(root);

    clone = cloneBinaryTree(root);

 /*InOrder traversal of clone tree */
    printf("\nClone Tree\n");
    inOrderTraversal(clone);

    return 0;
}
