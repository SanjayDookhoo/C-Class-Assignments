/*
Name: Sanjay Dookhoo
ID: 814000842
*/

/*
Method:
    because the synonyms of a word must be found quickly.
        binary search must be implemented
    *because the amount of words expected is unknown, can be stored as
        a linked list O(n) < array version
            sorted linked list to balanced bst  O(n) (compensates for the array version) (creating a completely different LNodeAll for bst and remove/free the LNodeAll of the linked list)
        or an array of max size O(n)
            (performing binary search, O(log(N)))

    this addresses storing and finding each word.

    question 1
    to find all synonyms of a word (with repition)
        point to top of list of synonyms
            print all

    question 2
    to find all synonyms of a word (without repition)
        point to top of list of synonyms
            check if each word was not printed yet (each word carries a printed state)
                if not printed, print

    should the binary tree share the same memory data as the top of the synonym list? or is it different?
        the linked list of synonyms holds
            ptr to the next in list
            and ptr to the bst LNodeAll
*/

#include<stdio.h>
#include<stdlib.h>

/* Link list LNodeAll */
struct LNodeAll
{
    int data;
    struct LNodeAll* next;
};

/* function to insert a new_node in a list. Note that this
  function expects a pointer to head_ref as this can modify the
  head of the input linked list (similar to push())*/
void sortedInsert(struct LNodeAll** head_ref, struct LNodeAll* new_node)
{
    struct LNodeAll* current;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the LNodeAll before the point of insertion */
        current = *head_ref;
        while (current->next!=NULL &&
               current->next->data < new_node->data)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

/* BELOW FUNCTIONS ARE JUST UTILITY TO TEST sortedInsert */

/* A utility function to create a new LNodeAll */
struct LNodeAll *newNode(int new_data)
{
    /* allocate LNodeAll */
    struct LNodeAll* new_node =
        (struct LNodeAll*) malloc(sizeof(struct LNodeAll));

    /* put in the data  */
    new_node->data  = new_data;
    new_node->next =  NULL;

    return new_node;
}

/* Function to print linked list */
void printList(struct LNodeAll *head)
{
    struct LNodeAll *temp = head;
    while(temp != NULL)
    {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
}

/* A Binary Tree LNodeAll */
struct TNode
{
    int data;
    struct TNode* left;
    struct TNode* right;
};

struct TNode* newNodeBST(int data);
int countLNodes(struct LNodeAll *head);
struct TNode* sortedListToBSTRecur(struct LNodeAll **head_ref, int n);


/* This function counts the number of nodes in Linked List and then calls
   sortedListToBSTRecur() to construct BST */
struct TNode* sortedListToBST(struct LNodeAll *head)
{
    /*Count the number of nodes in Linked List */
    int n = countLNodes(head);

    /* Construct BST */
    return sortedListToBSTRecur(&head, n);
}

/* The main function that constructs balanced BST and returns root of it.
       head_ref -->  Pointer to pointer to head LNodeAll of linked list
       n  --> No. of nodes in Linked List */
struct TNode* sortedListToBSTRecur(struct LNodeAll **head_ref, int n)
{
    /* Base Case */
    if (n <= 0)
        return NULL;

    /* Recursively construct the left subtree */
    struct TNode *left = sortedListToBSTRecur(head_ref, n/2);

    /* Allocate memory for root, and link the above constructed left
       subtree with root */
    struct TNode *root = newNodeBST((*head_ref)->data);
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
int countLNodes(struct LNodeAll *head)
{
    int count = 0;
    struct LNodeAll *temp = head;
    while(temp)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

/* Helper function that allocates a new LNodeAll with the
   given data and NULL left and right pointers. */
struct TNode* newNodeBST(int data)
{
    struct TNode* LNodeAll = (struct TNode*)
                         malloc(sizeof(struct TNode));
    LNodeAll->data = data;
    LNodeAll->left = NULL;
    LNodeAll->right = NULL;

    return LNodeAll;
}

/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* LNodeAll)
{
    if (LNodeAll == NULL)
        return;
    printf("%d ", LNodeAll->data);
    preOrder(LNodeAll->left);
    preOrder(LNodeAll->right);
}

/* Drier program to test above functions*/
int main()
{
    /* Start with the empty list */
    struct LNodeAll* head = NULL;
    struct LNodeAll *new_node = newNode(5);
    sortedInsert(&head, new_node);
    new_node = newNode(10);
    sortedInsert(&head, new_node);
    new_node = newNode(7);
    sortedInsert(&head, new_node);
    new_node = newNode(3);
    sortedInsert(&head, new_node);
    new_node = newNode(1);
    sortedInsert(&head, new_node);
    new_node = newNode(9);
    sortedInsert(&head, new_node);
    printf("\n Created Linked List\n");
    printList(head);

    /* Convert List to BST */
    struct TNode *root = sortedListToBST(head);
    printf("\n PreOrder Traversal of constructed BST ");
    preOrder(root);

    return 0;
}
