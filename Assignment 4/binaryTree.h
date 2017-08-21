/* ====Contains the data of each word represented in the balanced BST====*/

/* A Binary Tree  */
struct TNode
{
    char data[MAXWORDSIZE +1];
    int printed;
    struct TNode* synPointer; //not used until the end where all synonyms in different lines are merged
    struct TNode* left;
    struct TNode* right;
};

struct TNode* newNodeBST(char data[], struct TNode* extraDataTempt);
int countLNodes(struct LNode *head);
struct TNode* sortedListToBSTRecur(struct LNode **head_ref, int n);


/* This function counts the number of nodes in Linked List and then calls
   sortedListToBSTRecur() to construct BST */
struct TNode* sortedListToBST(struct LNode *head)
{
    /*Count the number of nodes in Linked List */
    int n = countLNodes(head);

    /* Construct BST */
    struct TNode* temp=sortedListToBSTRecur(&head, n);

    return temp;
}

/* The main function that constructs balanced BST and returns root of it.
       head_ref -->  Pointer to pointer to head LNode of linked list
       n  --> No. of nodes in Linked List */
struct TNode* sortedListToBSTRecur(struct LNode **head_ref, int n)
{
    /* Base Case */
    if (n <= 0)
        return NULL;

    /* Recursively construct the left subtree */
    struct TNode *left = sortedListToBSTRecur(head_ref, n/2);

    /* Allocate memory for root, and link the above constructed left
       subtree with root */
    struct TNode *root = newNodeBST((*head_ref)->data,NULL);
    root->left = left;

    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref)->next;

    /* Recursively construct the right subtree and link it with root
      The number of nodes in right subtree  is total nodes - nodes in
      left subtree - 1 (for root) which is n-n/2-1*/
    root->right = sortedListToBSTRecur(head_ref, n-n/2-1);

    return root;
}



/* UTILITY FUNCTIONS */

/* A utility function that returns count of nodes in a given Linked List */
int countLNodes(struct LNode *head)
{
    int count = 0;
    struct LNode *temp = head;
    while(temp)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

/* Helper function that allocates a new LNode with the
   given data and NULL left and right pointers. */
struct TNode* newNodeBST(char data[], struct TNode* extraDataTempt)
{
    struct TNode* LNode = (struct TNode*)
                         malloc(sizeof(struct TNode));
    strcpy(LNode->data, data);
    LNode->synPointer = extraDataTempt;
    LNode->left = NULL;
    LNode->right = NULL;

    return LNode;
}

/* A utility function to set printed using preorder traversal of BST */
void initPrinted(struct TNode* LNode)
{
    if (LNode == NULL)
        return;
    LNode->printed=0;
    initPrinted(LNode->left);
    initPrinted(LNode->right);
}

// C function to search a given data in a given BST
struct TNode* searchBST(struct TNode* root, char data[MAXWORDSIZE +1])
{
    // Base Cases: root is null or data is present at root
    if (root == NULL || strcmp(root->data, data)==0)
       return root;

    // Key is greater than root's data
    if (strcmp(root->data, data)<0)
       return searchBST(root->right, data);

    // Key is smaller than root's data
    return searchBST(root->left, data);
}

int countTreeNodes(struct TNode *tree)
{
    int c =  1;             //Node itself should be counted
    if (tree ==NULL)
        return 0;
    else
    {
        c += countTreeNodes(tree->left);
        c += countTreeNodes(tree->right);
        return c;
    }
}

/* Given a non-empty binary search tree, return the TNode with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct TNode * minValueNode(struct TNode* TNode)
{
    struct TNode* current = TNode;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

/* Given a binary search tree and a data, this function deletes the data
   and returns the new root */
struct TNode* deleteNodeBST(struct TNode* root, char* data)
{
    // base case
    if (root == NULL) return root;

    // If the data to be deleted is smaller than the root's data,
    // then it lies in left subtree
    if (strcmp(data, root->data)<0)
        root->left = deleteNodeBST(root->left, data);

    // If the data to be deleted is greater than the root's data,
    // then it lies in right subtree
    else if (strcmp(data, root->data)>0)
        root->right = deleteNodeBST(root->right, data);

    // if data is same as root's data, then This is the TNode
    // to be deleted
    else
    {
        // TNode with only one child or no child
        if (root->left == NULL)
        {
            struct TNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct TNode *temp = root->left;
            free(root);
            return temp;
        }

        // TNode with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct TNode* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this TNode
        strcpy(root->data, temp->data);
        root->synPointer=temp->synPointer;

        // Delete the inorder successor
        root->right = deleteNodeBST(root->right, temp->data);
    }
    return root;
}

//assign synonum pointer of all nodes in the BST
void assignSynonymPointerBST(struct TNode* LNode,struct TNode* toAssign)
{
    if (LNode == NULL)
        return;
    assignSynonymPointerBST(LNode->left,toAssign);

    LNode->synPointer=toAssign;//assign here

    assignSynonymPointerBST(LNode->right,toAssign);
}
