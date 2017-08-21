/* ====Merge Two Balanced BST into a single Balanced BST (Duplicates are NOT included in the created Balanced BST)==== */

/* temp data container */
struct dataCon
{
    char data[MAXWORDSIZE+1];
    struct TNode* synPointer;
};

// A utility unction to merge two sorted arrays into one
struct dataCon *merge(struct dataCon* arr1, struct dataCon* arr2, int m, int n);

// A helper function that stores inorder traversal of a tree in inorder array
void storeInorder(struct TNode* TNode, struct dataCon* inorder, int *index_ptr);

/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(struct dataCon*arr, int start, int end);

/* This function merges two balanced BSTs with roots as root1 and root2.
   m and n are the sizes of the trees respectively */
struct TNode* mergeTrees(struct TNode *root1, struct TNode *root2, int m, int n)
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

// A helper function that stores inorder traversal of a tree rooted with TNode
void storeInorder(struct TNode* TNode, struct dataCon *inorder, int *index_ptr)
{
    if (TNode == NULL)
        return;

    /* first recur on left child */
    storeInorder(TNode->left, inorder, index_ptr);

    //store the TNode data in a struct
    struct dataCon temp;
    strcpy(temp.data,TNode->data);
    temp.synPointer=TNode->synPointer;

    //store struct data in inorder array
    inorder[*index_ptr]=temp;
    (*index_ptr)++;  // increase index for next entry

    /* now recur on right child */
    storeInorder(TNode->right, inorder, index_ptr);
}

/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(struct dataCon *arr, int start, int end)
{
    /* Base Case */
    if (start > end)
      return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct TNode *root = newNodeBST(arr[mid].data, arr[mid].synPointer);

    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);

    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);

    return root;
}
