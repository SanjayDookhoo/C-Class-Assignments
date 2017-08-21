/*
Name: Sanjay Thistle Kashmir Dookhoo
ID: 814000842
*/

/*
Overview:
    -A set of Balanced BST is created for the set of synonyms.
    -Each BST is traversed inOrder, to identify a word, which is searched for in all other BST.
        If found: the Two BST are merged into another BST. And that tree begins the inOrder traversal to identify a word again
        If not found in the entirety of another BST: Move to the next tree and keep searching, until all trees are traversed

Reasoning:
    -A balanced BST allows for traversing in alphabetical order as well finding a word in O(log(n)).
    -Allows for finding a word in the most efficient time while accounting for an unlimited amount of words

Method:
    STORING
    -A sorted linked list of all related synonyms is created for each line of the input file
    -Each of those sorted linked list is used to created a Balanced BST
    -Each BST is traversed inOrder, to identify a word, which is searched for in all other BST.
        If found: the Two BST are merged into another BST. And that tree begins the inOrder traversal to identify a word again
        If not found in the entirety of another BST: Move to the next tree and keep searching, until all trees are traversed
    -Once all synonyms occurrences in different line has been removed, each node in all BST, then points to the root of its own BST. Allowing each node to access all its synonyms
    -All the remaining BST is then merged into one final BST

    OUTPUT REPEAT ALLOWED
    -perform inOrder traversal of the final tree
    -print the data in the node, and then perform an inOrder traversal of the BST root the node points to (to print its synonyms)
    -for the synonyms, do not print if it was already printed from the original BST that initiated the synonym traversal

    OUTPUT REPEAT NOT ALLOWED
    -initiate all nodes of the final BST printed state to 0
    -perform inOrder traversal of the final tree
    -if printed ==0
        -print the data in the node
        -and then perform an inOrder traversal of the BST root the node points to
        -for the data found in the second tree traversal, search the first tree (and get the state printed). if printed==0
            -for the synonyms, do not print if it was already printed from the original BST that initiated the synonym traversal
            -print
            -printed=1
    -printed=1

limitation:
    -words in the same line may be seperated by ' ' or '\t'
    -the end of a line is signaled by one or more new line chars
    -Due to the high storage capacity of computers
        -the original nodes of the BST (before it merges to one final BST) have extra unnecessary data to reduce code written (int and a Node ptr)
        -when a merge has been performed. the two trees that were used for the merge are not freed. (unnecesary time taken if it is not needed for the sake of this code)

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXWORDSIZE 32
#define LINESIZE 260
#define nextCol 20

/* ====creating and manipulating linked list of synonyms. Where a linked list is created for each line of the input data==== */

/* Link list LNode */
struct LNode
{
    char data[MAXWORDSIZE+1];
    struct LNode* next;
};

/* Link list all head container */
struct LHead
{
    struct LNode* head;
};

/* function to insert a new_node in a list. Note that this
  function expects a pointer to head_ref as this can modify the
  head of the input linked list */
void sortedInsert(struct LNode** head_ref, struct LNode* new_node)
{
    struct LNode* current;
    /* Special case for the head end */
    if (*head_ref == NULL || strcmp((*head_ref)->data, new_node->data) >=0) /*comparison*/
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the LNode before the point of insertion */
        current = *head_ref;
        while (current->next!=NULL &&
               strcmp(current->next->data, new_node->data)<0)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

/* A utility function to create a new LNode */
struct LNode *newNode(char new_data[MAXWORDSIZE +1])
{
    /* allocate LNode */
    struct LNode* new_node =
        (struct LNode*) malloc(sizeof(struct LNode));

    /* put in the data  */
    strcpy(new_node->data, new_data);
    new_node->next =  NULL;

    return new_node;
}

void deleteEntireLinkedList(struct LNode *head){
    struct LNode *curr;
    while ((curr = head) != NULL) {
        head = head->next;
        free (curr);
    }
}

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

/* ====holds the references to the root of each Balanced BST that exist for the synonyms ====*/

/* Link list LBSTNode */
struct LBSTNode
{
  struct TNode* root;
  struct LBSTNode *next;
};

/* Link list all head container */
struct LBSTHead
{
    struct LBSTNode* head;
};

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void appendBST(struct LBSTNode** head_ref, struct TNode* new_data)
{
    /* 1. allocate node */
    struct LBSTNode* new_node = (struct LBSTNode*) malloc(sizeof(struct LBSTNode));

    struct LBSTNode *last = *head_ref;  /* used in step 5*/

    /* 2. put in the root  */
    new_node->root  = new_data;

    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

void deleteNodeLBST(struct LBSTNode *head, struct LBSTNode *n)
{
    // When node to be deleted is head node
    if(head == n)
    {
        if(head->next == NULL)
        {
            printf("There is only one node. The list can't be made empty ");
            return;
        }

        /* Copy the root of next node to head */
        head->root= head->next->root;

        // store address of next node
        n = head->next;

        // Remove the link of next node
        head->next = head->next->next;

        // free memory
        free(n);

        return;
    }


    // When not first node, follow the normal deletion process

    // find the previous node
    struct LBSTNode *prev = head;
    while(prev->next != NULL && prev->next != n)
        prev = prev->next;

    // Check if node really exists in Linked List
    if(prev->next == NULL)
    {
        printf("\n Given node is not present in Linked List");
        return;
    }

    // Remove node from Linked List
    prev->next = prev->next->next;

    // Free memory
    free(n);

    return;
}

//assign synonum pointer of all nodes in the BST in the linked list to point to the root of each BST
void assignSynonymPointerLBST(struct LBSTNode *head){
    struct LBSTNode *curr=head;

    while(curr!=NULL){

        assignSynonymPointerBST(curr->root,curr->root);

        curr = curr->next;
    }
}

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

/* ====Functions that initiate the merging of synonyms BST for the purpoes of
   creating one BST with all related words. And for merging the final
   synonyms BST into one big BST. Allowing for all words to be traversed.====
*/

/* Structure of a stack node. Linked List implementation is used for
   stack. A stack node contains a pointer to tree node and a pointer to
   next stack node */
struct sNode
{
  struct TNode *t;
  struct sNode *next;
};

/* Stack related functions */
void push(struct sNode** top_ref, struct TNode *t);
struct TNode *pop(struct sNode** top_ref);
int isEmpty(struct sNode *top);

/* BEGINNING OF SPECIFIC FUNCTIONS FOR SYNONYM */

struct TNode* finalTreeMerge(struct LBSTNode* head_BST){
    struct LBSTNode* curr= head_BST;
    struct TNode* newTree=head_BST->root;//initiated in case the list only has one node. In which case no merging will be done

    while(curr->next!=NULL){
        newTree=mergeTrees(curr->root,(curr->next)->root,countTreeNodes(curr->root),countTreeNodes((curr->next)->root));

        deleteNodeLBST(head_BST,(curr->next));

        curr->root=newTree;
    }
    return newTree;
}

//return 1 if found, return 0 if not
int getSecondWord(struct TNode **rootLoc, char *firstWord)
{
  /* set current to root of binary tree */
  struct TNode *root=*rootLoc;
  struct TNode *current = root;
  struct sNode *s = NULL;  /* Initialize stack s */
  int done = 0;

  while (!done)
  {
    /* Reach the left most TNode of the current TNode */
    if(current !=  NULL)
    {
      /* place pointer to a tree node on the stack before traversing
        the node's left subtree */
      push(&s, current);
      current = current->left;
    }

    /* backtrack from the empty subtree and visit the TNode
       at the top of the stack; however, if the stack is empty,
      you are done */
    else
    {
      if (!isEmpty(s))
      {
        current = pop(&s);

        /* within the block of code the second word will be retrieved inOrder  */

        if(strcmp(current->data,firstWord)==0){
            //delete the word found, since when it merges there will be another occurence of the word
            *rootLoc=deleteNodeBST(root,current->data);

            return 1;
        }

        /* we have visited the node and its left subtree.
          Now, it's right subtree's turn */
        current = current->right;
      }
      else
        done = 1;
    }
  } /* end of while */

  return 0;
}

//root of BST where commonality was found if it was, therefore restart seaarch from right there, if NULL then move on the next in list
struct LBSTNode* getFirstWord(struct LBSTNode *head_BST)
{
  /* set current to root of binary tree */
  struct TNode *current = head_BST->root;
  struct sNode *s = NULL;  /* Initialize stack s */
  int done = 0;

  struct LBSTNode *currInList;
  int found=0;

  while (!done)
  {
    /* Reach the left most TNode of the current TNode */
    if(current !=  NULL)
    {
      /* place pointer to a tree node on the stack before traversing
        the node's left subtree */
      push(&s, current);
      current = current->left;
    }

    /* backtrack from the empty subtree and visit the TNode
       at the top of the stack; however, if the stack is empty,
      you are done */
    else
    {
      if (!isEmpty(s))
      {
        current = pop(&s);

        /* within the block of code the first word will be retrieved inOrder  */

        currInList=head_BST->next;

        while(currInList!=NULL){
            found=getSecondWord(&(currInList->root),current->data);
            if(found==1){
                //end this search, and begin again
                return currInList;
            }

            currInList=currInList->next;
        }

        /* we have visited the node and its left subtree.
          Now, it's right subtree's turn */
        current = current->right;
      }
      else
        done = 1;
    }
  } /* end of while */

  return NULL;
}

void synonymMerging(struct LBSTNode* head_BST){
    struct LBSTNode* found;
    struct LBSTNode* curr=head_BST;

    struct TNode* newTree;

    while(curr!=NULL){
        found=getFirstWord(curr);

        if(found==NULL){//not found therefore safe to move on to the next synonym list, otherwise keep processing this list till all its merges are completed
            curr=curr->next;
        }else{
            //merge the two bst from their root and return a root to the new merged BST
            newTree=mergeTrees(curr->root,found->root,countTreeNodes(curr->root),countTreeNodes(found->root));

            //original two trees should be deleted here
            //not done because it takes procesisng time

            //delete one from the linked list (found)
            deleteNodeLBST(head_BST,found);

            //replace the other with the new bst (curr)
            curr->root=newTree;
        }
    }
}

/* END OF SPECIFIC FUNCTIONS FOR SYNONYM */


/* Iterative function for inorder tree traversal */
void inOrderNonRecursive(struct TNode *root)
{
  /* set current to root of binary tree */
  struct TNode *current = root;
  struct sNode *s = NULL;  /* Initialize stack s */
  int done = 0;

  while (!done)
  {
    /* Reach the left most TNode of the current TNode */
    if(current !=  NULL)
    {
      /* place pointer to a tree node on the stack before traversing
        the node's left subtree */
      push(&s, current);
      current = current->left;
    }

    /* backtrack from the empty subtree and visit the TNode
       at the top of the stack; however, if the stack is empty,
      you are done */
    else
    {
      if (!isEmpty(s))
      {
        current = pop(&s);
        printf("%s ", current->data);

        /* we have visited the node and its left subtree.
          Now, it's right subtree's turn */
        current = current->right;
      }
      else
        done = 1;
    }
  } /* end of while */
}

/* UTILITY FUNCTIONS */
/* Function to push an item to sNode*/
void push(struct sNode** top_ref, struct TNode *t)
{
  /* allocate TNode */
  struct sNode* new_tNode =
            (struct sNode*) malloc(sizeof(struct sNode));

  if(new_tNode == NULL)
  {
     printf("Stack Overflow \n");
     getchar();
     exit(0);
  }

  /* put in the data  */
  new_tNode->t  = t;

  /* link the old list off the new TNode */
  new_tNode->next = (*top_ref);

  /* move the head to point to the new TNode */
  (*top_ref)    = new_tNode;
}

/* The function returns true if stack is empty, otherwise false */
int isEmpty(struct sNode *top)
{
   return (top == NULL)? 1 : 0;
}

/* Function to pop an item from stack*/
struct TNode *pop(struct sNode** top_ref)
{
  struct TNode *res;
  struct sNode *top;

  /*If sNode is empty then error */
  if(isEmpty(*top_ref))
  {
     printf("Stack Underflow \n");
     getchar();
     exit(0);
  }
  else
  {
     top = *top_ref;
     res = top->t;
     *top_ref = top->next;
     free(top);
     return res;
  }
}

/* ====Functions to print to the output file in the format specified using recursive inOrder traversal of the BSTs==== */

//print the first word as well as the necessary space for seperation
void fprintFirstWord(char *word,FILE *out){
    int i;
    fprintf(out,"%s",word);
    for(i=strlen(word);i<nextCol;i++) fprintf(out," ");
}

//traversal of synonyms
void inOrderRepeat(struct TNode* LNode,char *ignore,FILE *out)
{
    if (LNode == NULL)
        return;
    inOrderRepeat(LNode->left,ignore,out);

    if(strcmp (LNode->data,ignore)!=0)
        fprintf(out,"%s ", LNode->data);

    inOrderRepeat(LNode->right,ignore,out);
}

//printing all words
void printRepeat(struct TNode* LNode,FILE *out)
{
    if (LNode == NULL)
        return;
    printRepeat(LNode->left,out);

    //fprintf(out,"%s\t\t",LNode->data);
    fprintFirstWord(LNode->data,out);
    inOrderRepeat(LNode->synPointer,LNode->data,out);
    fprintf(out,"\n");

    printRepeat(LNode->right,out);
}

//traversal of synonyms
void inOrderNoRepeat(struct TNode* LNode,char *ignore,struct TNode* allWords,FILE *out)
{
    if (LNode == NULL)
        return;
    inOrderNoRepeat(LNode->left,ignore,allWords,out);

    if(strcmp(ignore,LNode->data)!=0){
        struct TNode* temp=searchBST(allWords,LNode->data);
        if(temp->printed==0){
            fprintf(out,"%s ", LNode->data);
            temp->printed=1;
        }
    }

    inOrderNoRepeat(LNode->right,ignore,allWords,out);
}

//printing all words
void printNoRepeat(struct TNode *LNode,struct TNode *allWords,FILE *out){
    if (LNode == NULL)
        return;
    printNoRepeat(LNode->left,allWords,out);

    if(LNode->printed==0){
        //fprintf(out,"%s\t\t",LNode->data);
        fprintFirstWord(LNode->data,out);
        inOrderNoRepeat(LNode->synPointer,LNode->data,allWords,out);
        fprintf(out,"\n");

        LNode->printed=1;
    }

    printNoRepeat(LNode->right,allWords,out);
}

/* Drier program to test above functions*/
int main()
{
    FILE *in = fopen("input.txt","r");
	FILE *out = fopen("output.txt","w");
	if(in == NULL)printf("Error reading input...\n");
    char buf[LINESIZE];
    char *token;

    /* Start with the empty list */
    struct LNode* head = NULL;
    struct LNode *new_node;

    /* Start with the empty list BST */
    struct LBSTNode* head_BST = NULL;

    struct TNode *root;

    //store synonym data
    while(fgets(buf, sizeof(buf), in)) //where sizeof(buf) is the length of line you anticipate reading in.
    {
        if(buf[strlen(buf)-1]=='\n')//if new line is at the end of the line
            buf[strlen(buf)-1]='\0';//remove new line character from the end

        token = strtok(buf, " \t");
        head = NULL;
        while (token && strcmp(token,"")!=0) {
            //insert into a linked list
            new_node = newNode(token);
            sortedInsert(&head, new_node);

            token = strtok(NULL, " \t");
        }
        //create balanced BST from that linked list
        root = sortedListToBST(head);

        //store root of balanced BST in a linked list
        appendBST(&head_BST, root);

        //free memory used to create original linked list
        //not done since its not necessary to increase performance
        //deleteEntireLinkedList(head);
    }

    synonymMerging(head_BST);

    assignSynonymPointerLBST(head_BST);

    root=finalTreeMerge(head_BST);

    fprintFirstWord("Words",out);
    fprintf(out,"Synonyms\n\n");
    printRepeat(root,out);

    fprintf(out,"\n\n");
    fprintFirstWord("Words",out);
    fprintf(out,"Synonyms\n\n");
    initPrinted(root);
    printNoRepeat(root,root,out);

    fclose(in);
	fclose(out);

    return 0;
}
