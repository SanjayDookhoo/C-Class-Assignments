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
