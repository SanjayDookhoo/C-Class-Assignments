//http://www.geeksforgeeks.org/merge-two-balanced-binary-search-trees/

/*
attempting to merge and maintain the order established by data. while keeping the extraData still present in the merge
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDSIZE 32

struct dataCon
{
    char data[MAXWORDSIZE+1];
    int extraData;
};

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
struct dataCon *merge(struct dataCon* arr1, struct dataCon* arr2, int m, int n);

// A helper function that stores inorder traversal of a tree in inorder array
void storeInorder(struct node* node, struct dataCon* inorder, int *index_ptr);

/* A function that constructs Balanced Binary Search Tree from a sorted array
   See http://www.geeksforgeeks.org/archives/17138 */
struct node* sortedArrayToBST(struct dataCon*arr, int start, int end);

/* This function merges two balanced BSTs with roots as root1 and root2.
   m and n are the sizes of the trees respectively */
struct node* mergeTrees(struct node *root1, struct node *root2, int m, int n)
{
    // Store inorder traversal of first tree in an array arr1[]
    struct dataCon *arr1 = (struct dataCon*) malloc(m * sizeof(struct dataCon));;

    int i = 0;
    storeInorder(root1, arr1, &i);

    // Store inorder traversal of second tree in another array arr2[]
    struct dataCon *arr2 = (struct dataCon*) malloc(n * sizeof(struct dataCon));;

    int j = 0;
    storeInorder(root2, arr2, &j);

    // Merge the two sorted array into one
    struct dataCon* mergedArr = merge(arr1, arr2, m, n);

    // Construct a tree from the merged array and return root of the tree
    return sortedArrayToBST (mergedArr, 0, m+n-1);
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

    printf("%s:%d ", node->data,node->extraData);

    /* now recur on right child */
    printInorder(node->right);
}

// A utility unction to merge two sorted arrays into one
struct dataCon* merge(struct dataCon* arr1, struct dataCon* arr2, int m, int n)
{
    // mergedArr[] is going to contain result
    struct dataCon *mergedArr = (struct dataCon*) malloc((m+n) * sizeof(struct dataCon));;

    int i = 0, j = 0, k = 0;

    // Traverse through both arrays
    while (i < m && j < n)
    {
        // Pick the smaler element and put it in mergedArr (from the data aspect)
        if (strcmp(arr1[i].data, arr2[j].data)<0)
        {
            mergedArr[k]= arr1[i];
            i++;
        }
        else
        {
            mergedArr[k]= arr2[j];
            j++;
        }
        k++;
    }

    // If there are more elements in first array
    while (i < m)
    {
        mergedArr[k]= arr1[i];
        i++; k++;
    }

    // If there are more elements in second array
    while (j < n)
    {
        mergedArr[k]= arr2[j];
        j++; k++;
    }

    return mergedArr;
}

// A helper function that stores inorder traversal of a tree rooted with node
void storeInorder(struct node* node, struct dataCon *inorder, int *index_ptr)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    storeInorder(node->left, inorder, index_ptr);

    //store the node data in a struct
    struct dataCon temp;
    strcpy(temp.data,node->data);
    temp.extraData=node->extraData;

    //store struct data in inorder array
    inorder[*index_ptr]=temp;
    (*index_ptr)++;  // increase index for next entry

    /* now recur on right child */
    storeInorder(node->right, inorder, index_ptr);
}

/* A function that constructs Balanced Binary Search Tree from a sorted array
   See http://www.geeksforgeeks.org/archives/17138 */
struct node* sortedArrayToBST(struct dataCon *arr, int start, int end)
{
    /* Base Case */
    if (start > end)
      return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct node *root = newNode(arr[mid].data, arr[mid].extraData);

    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);

    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);

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
    root1->left         = newNode("s",2);
    root1->right        = newNode("z",3);
    root1->left->left   = newNode("m",4);
    root1->left->right  = newNode("u",5);

    /* Create following tree as second balanced BST
            80
           /  \
         40   120
    */
    struct node *root2  = newNode("w",6);
    root2->left         = newNode("r",7);
    root2->right        = newNode("y",8);

    int constantExtraData=5;

    struct node *mergedTree = mergeTrees(root1, root2, 5, 3);

    printf ("Following is Inorder traversal of the merged tree \n");
    printInorder(mergedTree);

    return 0;
}
