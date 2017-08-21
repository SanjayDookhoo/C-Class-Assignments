/* Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/

#include <stdio.h>
#include <stdlib.h>

//queuedata struct and methods used by queue header
typedef struct {
    struct node* tnode;
}QueueData;

QueueData newQueueData(struct node* tnp){
    QueueData temp;
    temp.tnode=tnp;
    return temp;
}
//end queuedata struct and methods

//beginning of queue header
typedef struct QNode{
    QueueData data;
    struct QNode*next;
}QNode,*QNodePtr;

typedef struct queueType{
    QNodePtr head,tail;
}QueueType,*Queue;

Queue initQueue(){
    Queue qp=(Queue)malloc(sizeof(QueueType));
    qp->head=qp->tail=NULL;
    return qp;
}

int empty(Queue Q){
    return (Q->head==NULL);
}

void enqueue(Queue Q, QueueData d){
    QNodePtr np=(QNodePtr)malloc(sizeof(QNode));
    np->data=d;
    np->next=NULL;
    if(empty(Q)){
        Q->head=np;
        Q->tail=np;
    }else{
        Q->tail->next=np;
        Q->tail=np;
    }
}

QueueData dequeue(Queue Q){
    if(empty(Q)){
        printf("\nAttempt to remove from an empty queue");
        exit(1);
    }
    QueueData hold=Q->head->data;
    QNodePtr temp=Q->head;
    Q->head=Q->head->next;
    if(Q->head==NULL)Q->tail=NULL;
    free(temp);
    return hold;
}
//end of queue header
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}Node,*NodePtr;

NodePtr newNode(int x){
    NodePtr temp=(NodePtr)malloc(sizeof(Node));
    temp->data=x;
    temp->left=NULL;
    temp->right=NULL;
}

NodePtr insert( int key,NodePtr root){
    NodePtr node=newNode(key);
    if(root==NULL) return node;

    NodePtr curr=root;
    while(node->data!=curr->data){
        if(node->data<curr->data){
            if(curr->left==NULL) {
                curr->left=node;
                return root;
            }
            curr=curr->left;
        }else{
            if(curr->right==NULL) {
                curr->right=node;
                return root;
            }
            curr=curr->right;
        }
    }
}

void insertR( int key,NodePtr *root){
    NodePtr node=newNode(key);
    if(*root==NULL) *root=node;

    else if(key<(*root)->data){
        insertR(key,&(*root)->left);
    }else{
        insertR(key,&(*root)->right);
    }
}

void inOrder(NodePtr node){
    if(node!=NULL){
        inOrder(node->left);

        printf("%d ",node->data);

        inOrder(node->right);
    }
}

void preOrder(NodePtr node){
    if(node!=NULL){
        printf("%d ",node->data);

        preOrder(node->left);
        preOrder(node->right);
    }
}

void postOrder(NodePtr node){
    if(node!=NULL){
        postOrder(node->left);
        postOrder(node->right);

        printf("%d ",node->data);
    }
}

NodePtr search(NodePtr root, int x){
    NodePtr curr=root;
    while(curr!=NULL && curr->data!=x){
        if(x<curr->data) curr=curr->left;
        else curr=curr->right;
    }

    return curr;
}

NodePtr searchR(int key, NodePtr root){
    if (root == NULL)
        return NULL;
    else if (key < root->data)
        return searchR(key, root->left);
    else if (key > root->data)
        return searchR(key, root->right);
    else
        return root;
}

int countNodes(NodePtr root) {
    if(root == NULL) return 0;
    else return 1 + countNodes(root->left)+countNodes(root->right);
}

int countLeaves(NodePtr root) {
    if(root == NULL) return 0;
    if ( (root->left == NULL) && (root->right == NULL)) return 1;
    return countLeaves(root->left)+ countLeaves(root->right);
}

int myMax(int a, int b){
    if(a>b) return a;
    else return b;
}

int compHeight(NodePtr root) {
    //level(root) = 0
    if(root == NULL)return -1;
    else return 1 + myMax(compHeight(root->left),compHeight(root->right));
}

int numLevels(NodePtr root) {
    // #levels
    if(root == NULL)return 0;
    else return 1 + myMax(numLevels(root->left),numLevels(root->right));
}

NodePtr findMin(NodePtr root) {
    NodePtr min = NULL;
    NodePtr curr = root;
    while(curr != NULL) {
        min = curr;
        curr = curr->left;
    }
    return min;
}

NodePtr findMinR(NodePtr root) {
    // recursive findSmallest()
    if(root->left == NULL)return root;
    else return findMinR(root->left);
}

NodePtr findMax(NodePtr root) {
    NodePtr max = NULL;
    NodePtr curr = root;
    while(curr != NULL) {
        max = curr;
        curr = curr->right;
    }
    return max;
}

NodePtr findMaxR(NodePtr root) {
    // recursive findLargest()
    if(root->right == NULL)return root;
    else return findMaxR(root->right);
}

NodePtr inOrderSuccessor(NodePtr root, int key) {
    NodePtr succ = NULL, curr = root;
    // check for empty tree
    if ( root == NULL )
        return NULL;
        // Start from root and search for
        // successor down the tree
    while ( key != curr->data ) {
        if (key < curr->data) {
            succ = curr;
            curr = curr->left;
        }else // key > curr->data
            curr = curr->right;
    }
    // curr->data = key,
    // i.e., the node is found
    if ( (curr != NULL) && (curr->right != NULL) )
        succ = findMinR(curr->right);

    return succ;
}
/*
int Delete(int key, NodePtr *root) {
    // (assumes non-empty tree)
    NodePtr p = NULL; // parent
    NodePtr c = *root; // current
    int isLeftChild = 1;
    // c is left or right child of p
    while (c->data != key) {
        // search for node
        p = c; // move p to c
        if (key < c->data) { // go left
            // c is left child of p,
            // --> update p->left
            isLeftChild = 1;
            c = c->left;
        }else { // go right
            // c is right child of p,
            // --> update p->right
            isLeftChild = 0;
            c = c->right;
        }
        if (c == NULL)
        // end of the line,
        return 0; // did not find it
    } // end while
    // found node c to delete

    // Case 1: // if c has no children,simply delete it
    if ((c->left == NULL) &&(c->right == NULL)) {
        if (c == *root) // if root,
            *root = NULL; // tree is empty
        else if (isLeftChild)
            // left child of p
            p->left = NULL;
            // disconnect, update p->left
        else // from parent
            p->right = NULL;
            // update p->right
    } // end Case 1

    // Case 2: if c has no right child,
    // replace c with left subtree of c
    else if (c->right == NULL)
        if (c == *root)
            // i.e., c has no parent
            *root = c->left;
        else if (isLeftChild)
            // c is left child of p,
            // --> update p->left
            p->left = c->left;
        else
            // c is right child of p,
            // --> update p->right
            p->right = c->left;
            // if c has no left child, replace
            // c with right subtree of c
        else if (c->left == NULL)
            if (c == *root)
                // i.e., c has no parent
                *root = c->right;
            else if(isLeftChild)
                // c is left child of p,
                // --> update p->left
                p->left = c->right;
            else
                // c is right child of p,
                // --> update p->right
                p->right = c->right;

    // Case 3:
    else { // two children, so replace c
        // with its successor
        // successor is leftmost node
        // of right subtree
        // get successor of node to
        // delete (current)
        NodePtr s = inOrderSuccessor(root,c->data);
        // successor
        // getSuccessor() also performs
        // Steps 1 and 2
        // Step 1: sp->left = s->right;
        // Step 2: s->right = delNode->right;
        // connect parent of current to
        // successor instead
        if (c == *root)
            *root = s;
            // i.e., c has no parent
            // Step 3: p->left = s; or
        // p->right = s;
        else if(isLeftChild)
            // c is left child of p,
            // --> update p->left
            p->left = s;
        else
            // c is right child of p,
            // --> update p->right
            p->right = s;
        // end of Step 3 or Step 1 in
        // case successor is right child
        // of to-be-deleted node
        // Step 4: s->left = c->left;
        // connect successor to current's
        // left child
        s->left = c->left;
        // Step 4 or Step 2 in case
        // successor is right
        // child of to-be-deleted node
    } // end else two children
    // successor cannot have left child
    return 1; // success
} // end Delete()
*/

NodePtr subDel(NodePtr T){
    if(T==NULL) return NULL;
    if(T->right==NULL) return T->left;
    NodePtr R=T->right;
    NodePtr P;
    if(T->left==NULL) return R;
    if(R->left==NULL){
        R->left=T->left;
        return R;
    }
    while(R->left!=NULL){
        P=R;
        R=R->left;
    }

    R->left=T->left;
    P->left=R->right;
    R->right=T->right;

    return R;
}

int Delete(int key, NodePtr *root){
    NodePtr curr=*root,prev=NULL;
    char state='n';
    while(curr!=NULL && curr->data!=key){
        if(key<curr->data) {
            prev=curr;
            curr=curr->left;
            state='l';
        }
        else {
            prev=curr;
            curr=curr->right;
            state='r';
        }
    }

    NodePtr  toDel=curr,parent=prev;


    if(toDel!=NULL){

        if(prev==NULL){
            *root=subDel(toDel);
        }else if(state=='l'){
            parent->left=subDel(toDel);
        }else if(state=='r'){
            parent->right=subDel(toDel);
        }

        return 1;
    }else{
        return 0;
    }
}

NodePtr DeleteRR(int key, NodePtr root){
    NodePtr tmp, s; // s = successor
    if (root == NULL) {
        printf("%d is not found\n", key);
        //return root;
        getchar();
    }else if (key < root->data) //go left
        root->left = DeleteRR(key, root->left);
    else if (key > root->data)//go right
        root->right = DeleteRR(key, root->right);
    else // found element to be deleted
        if ( (root->left != NULL) &&(root->right != NULL) ){ // deleted node has two children, replace with smallest in
            // right subtree
            s = findMinR(root->right);
            root->data = s->data;
            root->right=DeleteRR(root->data, root->right);
        }else { // deleted node has zero or one child
            tmp = root;
            if (root->left == NULL)
                root = root->right;//ROOT changes here, reason why root is returned
            else if (root->right == NULL)
                root = root->left;//ROOT changes here, reason why root is returned
            free(tmp);
        }

    return root;
}

NodePtr DeleteR(NodePtr root){
    int toDelete;
    printf("Enter the node integer to delete: ");
    scanf("%d",&toDelete);
    getchar();
    return DeleteRR(toDelete,root);
}

void levelOrder(NodePtr root){
    /*QueueData newQueueData(TreeNodePtr);*/
    Queue Q=initQueue();
    enqueue(Q,newQueueData(root));

    printf("The level order is: ");

    while(!empty(Q)){
        QueueData temp=dequeue(Q);

        printf("%d ",temp.tnode->data);

        if(temp.tnode->left!=NULL) enqueue(Q,newQueueData(temp.tnode->left));
        if(temp.tnode->right!=NULL) enqueue(Q,newQueueData(temp.tnode->right));
    }
    printf("\n");
}

int main(){
    NodePtr root=NULL,retNode;
    int menuOpt,toInsert,toSearch,numOfNodes,numOfLeaves,height,levels,key,min,max,toDelete,deleted;

    //menu
    while(1){
        printf("1. Insert a new node(iteration)\n");
        printf("2. Insert a new node(recursion)\n");
        printf("3. Tree traversal\n");
        printf("4. Search a node(iteration)\n");
        printf("5. Search a node(recursion)\n");
        printf("6. Count number of nodes in tree\n");
        printf("7. Count number of leaves in tree\n");
        printf("8. Height of tree (root level=0)\n");
        printf("9. Height of tree (root level=1)\n");
        printf("10. Find the node with the minimum key(iteraation)\n");
        printf("11. Find the node with the minimum key(recursion)\n");
        printf("12. Find the node with the maximum key(iteration)\n");
        printf("13. Find the node with the maximum key(recursion)\n");
        printf("14. Delete a node from BST(iteration)\n");
        printf("15. Delete a node from BST(recursion)\n");
        printf("16. Find the inorder successor (without using parent link)\n");
        printf("17. Breadth-first traversal(BFT)\n");
        printf("18. Exit\n");
        scanf("%d",&menuOpt);
        getchar();

        switch(menuOpt){
            case 1:
                printf("Enter a number to insert: ");
                scanf("%d",&toInsert);
                getchar();
                root=insert(toInsert,root);
                break;
            case 2:
                printf("Enter a number to insert: ");
                scanf("%d",&toInsert);
                getchar();
                insertR(toInsert,&root);
                break;
            case 3:
                printf("1. InOrder Traversal\n");
                printf("2. PreOrder Traversal\n");
                printf("3. PostOrder Traversal\n");
                scanf("%d",&menuOpt);
                getchar();

                switch(menuOpt){
                    case 1:
                        printf("INORDER TRAVERSAL: ");
                        inOrder(root);
                        printf("\n");
                        break;
                    case 2:
                        printf("PREORDER TRAVERSAL: ");
                        preOrder(root);
                        printf("\n");
                        break;
                    case 3:
                        printf("POSTORDER TRAVERSAL: ");
                        postOrder(root);
                        printf("\n");
                        break;
                    default:
                        printf("Number must be between 1-3");
                        break;
                }
                break;
            case 4:
                printf("Enter a node to search for by its data: ");
                scanf("%d",&toSearch);
                getchar();
                retNode=search(root,toSearch);

                //testing
                if(retNode!=NULL) printf("Node found: %d\n",retNode->data);
                else printf("Node not found\n");

                break;
            case 5:
                printf("Enter a node to search for by its data: ");
                scanf("%d",&toSearch);
                getchar();
                retNode=searchR(toSearch,root);

                //testing
                if(retNode!=NULL) printf("Node found: %d\n",retNode->data);
                else printf("Node not found\n");

                break;
            case 6:
                numOfNodes=countNodes(root);
                printf("Number of Nodes: %d\n",numOfNodes);
                break;
            case 7:
                numOfLeaves=countLeaves(root);
                printf("Number of Leaves: %d\n",numOfLeaves);
                break;
            case 8:
                height=compHeight(root);
                printf("Height: %d\n",height);
                break;
            case 9:
                levels=numLevels(root);
                printf("Levels: %d\n",levels);
                break;
            case 10:
                min=findMin(root)->data;
                printf("The min is: %d\n",min);
                break;
            case 11:
                min=findMinR(root)->data;
                printf("The min is: %d\n",min);
                break;
            case 12:
                max=findMax(root)->data;
                printf("The max is: %d\n",max);
                break;
            case 13:
                max=findMaxR(root)->data;
                printf("The max is: %d\n",max);
                break;
            case 14:
                printf("Enter the node integer to delete: ");
                scanf("%d",&toDelete);
                getchar();
                deleted=Delete(toDelete,&root);
                if(deleted==1) printf("Deletion successful\n");
                else printf("Could not find element to delete\n");
                break;
            case 15:
                root=DeleteR(root);
                break;
            case 16:
                printf("Enter key to find inorder successor of: ");
                scanf("%d",&key);
                retNode=inOrderSuccessor(root, key);

                //testing
                printf("The inOrderSuccessor is: %d\n",retNode->data);

                break;
            case 17:
                levelOrder(root);
                break;
            case 18:
                exit(0);
                break;

            default:
                printf("Number must be between 1-18");
                break;
        }
    }
    return 0;
}
