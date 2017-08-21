//http://www.geeksforgeeks.org/merge-two-balanced-binary-search-trees/

/*
attempting to merge and maintain the order established by data. while keeping the extraData still present in the merge
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDSIZE 32

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
    char data[MAXWORDSIZE+1];
    int extraData;
    struct node* left;
    struct node* right;
};

// A utility unction to merge two sorted arrays into one
char **merge(char** arr1, char** arr2, int m, int n);

// A helper function that stores inorder traversal of a tree in inorder array
void storeInorder(struct node* node, char** inorder, int *index_ptr);

/* A function that constructs Balanced Binary Search Tree from a sorted array
   See http://www.geeksforgeeks.org/archives/17138 */
struct node* sortedArrayToBST(char **arr, int start, int end, int extraDataTempt);

/* This function merges two balanced BSTs with roots as root1 and root2.
   m and n are the sizes of the trees respectively */
struct node* mergeTrees(struct node *root1, struct node *root2, int m, int n, int extraDataTempt)
{
    // Store inorder traversal of first tree in an array arr1[]
    int k;
    char **arr1 = (char **)malloc(m * sizeof(char *));
    for (k=0; k<m; k++)
         arr1[k] = (char *)malloc((MAXWORDSIZE+1) * sizeof(char));

    int i = 0;
    storeInorder(root1, arr1, &i);

    // Store inorder traversal of second tree in another array arr2[]
    char **arr2 = (char **)malloc(n * sizeof(char *));
    for (k=0; k<n; k++)
         arr2[k] = (char *)malloc((MAXWORDSIZE+1) * sizeof(char));
    int j = 0;
    storeInorder(root2, arr2, &j);

    // Merge the two sorted array into one
    char **mergedArr = merge(arr1, arr2, m, n);

    // Construct a tree from the merged array and return root of the tree
    return sortedArrayToBST (mergedArr, 0, m+n-1, extraDataTempt);
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(char data[], int extraDataTempt)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    strcpy(node->data, data);
    node->extraData = extraDataTempt;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

// A utility function to print inorder traversal of a given binary tree
void printInorder(struct node* node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    printInorder(node->left);

    printf("%s ", node->data);

    /* now recur on right child */
    printInorder(node->right);
}

// A utility unction to merge two sorted arrays into one
char **merge(char** arr1, char** arr2, int m, int n)
{
    // mergedArr[] is going to contain result

    int x;
    char **mergedArr = (char **)malloc((m+n) * sizeof(char *));
    for (x=0; x<(m+n); x++)
         mergedArr[x] = (char *)malloc((MAXWORDSIZE+1) * sizeof(char));

    int i = 0, j = 0, k = 0;

    // Traverse through both arrays
    while (i < m && j < n)
    {
        // Pick the smaler element and put it in mergedArr
        if (strcmp(arr1[i], arr2[j])<0)
        {
            strcpy(mergedArr[k], arr1[i]);
            i++;
        }
        else
        {
            strcpy(mergedArr[k], arr2[j]);
            j++;
        }
        k++;
    }

    // If there are more elements in first array
    while (i < m)
    {
        strcpy(mergedArr[k], arr1[i]);
        i++; k++;
    }

    // If there are more elements in second array
    while (j < n)
    {
        strcpy(mergedArr[k], arr2[j]);
        j++; k++;
    }

    return mergedArr;
}

// A helper function that stores inorder traversal of a tree rooted with node
void storeInorder(struct node* node, char **inorder, int *index_ptr)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    storeInorder(node->left, inorder, index_ptr);

    strcpy(inorder[*index_ptr], node->data);
    (*index_ptr)++;  // increase index for next entry

    /* now recur on right child */
    storeInorder(node->right, inorder, index_ptr);
}

/* A function that constructs Balanced Binary Search Tree from a sorted array
   See http://www.geeksforgeeks.org/archives/17138 */
struct node* sortedArrayToBST(char **arr, int start, int end, int extraDataTempt)
{
    /* Base Case */
    if (start > end)
      return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct node *root = newNode(arr[mid], extraDataTempt);

    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1, extraDataTempt);

    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end, extraDataTempt);

    return root;
}

/* Driver program to test above functions*/
int main()
{
    /* Create following tree as first balanced BST
           100
          /  \
        50    300
       / \
      20  70
    */
    struct node *root1  = newNode("x",1);
    root1->left         = newNode("s",1);
    root1->right        = newNode("z",1);
    root1->left->left   = newNode("m",1);
    root1->left->right  = newNode("u",1);

    /* Create following tree as second balanced BST
            80
           /  \
         40   120
    */
    struct node *root2  = newNode("w",1);
    root2->left         = newNode("r",1);
    root2->right        = newNode("y",1);

    int constantExtraData=5;

    struct node *mergedTree = mergeTrees(root1, root2, 5, 3, constantExtraData);

    printf ("Following is Inorder traversal of the merged tree \n");
    printInorder(mergedTree);

    printf("%d",mergedTree->extraData);

    return 0;
}
