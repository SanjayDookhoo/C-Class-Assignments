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
