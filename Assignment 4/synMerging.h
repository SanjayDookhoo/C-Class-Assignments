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
