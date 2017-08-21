/* Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/

//in hash table
//-1 : empty
#include <stdio.h>
#include <stdlib.h>

#define M 10


typedef struct node{
    int k;
    struct node * next;
}Node,*NodePtr;

int hash(int key){
    return key%M;
}

int rehash(int key, int t){
    return (key+t)%M;
}

NodePtr newNode(int key){
    NodePtr temp=(NodePtr)malloc(sizeof(Node));
    temp->k=key;
    temp->next=NULL;
}

void Insert(NodePtr table[],int key){
    int h1=hash(key);
    NodePtr temp;
    NodePtr prev=NULL;
    NodePtr curr;

    if(table[h1]==NULL){
        table[h1]=newNode(key);
    }else{
        curr=table[h1];
        while(curr!=NULL && curr->k<key){
            prev=curr;
            curr=curr->next;
        }
        //insert at top
        if(prev==NULL) {
            temp=newNode(key);
            temp->next=table[h1];
            table[h1]=temp;
        }else{
            temp=newNode(key);
            prev->next=temp;
            temp->next=curr;
        }
    }
}

NodePtr Search(NodePtr table[],int key){//returns the index i if found otherwise returns M.
    int h=hash(key);
    NodePtr curr=table[h];

    if(table[h]==NULL){
        return NULL;
    }else{
        while(curr!=NULL && curr->k!=key){
            curr=curr->next;
        }
        if(curr->k==key) return curr;
        else return NULL;
    }
}

void Delete(NodePtr table[], int key){
    int h=hash(key);
    NodePtr prev=NULL,curr,temp;

    if(table[h]==NULL){
        printf("key does not exist to delete\n");
    }else{
        curr=table[h];
        while(curr!=NULL && curr->k!=key){
            prev=curr;
            curr=curr->next;
        }
        if(prev==NULL){
            temp=table[h];
            table[h]=table[h]->next;
            free(temp);
        }else if(curr!=NULL){
            temp=curr;
            prev->next=curr->next;
            free(temp);
        }else {
            printf("key does not exist to delete\n");
        }
    }
}

void Display(NodePtr table[]){
    NodePtr curr;
    int x;
    for(x=0;x<M;x++){
        printf("Bucket %d:\n",x);
        curr=table[x];
        while(curr!=NULL){
            printf("%d\n",curr->k);
            curr=curr->next;
        }
    }
}

void initTable(NodePtr table[]){
    int x;
    for(x=0;x<M;x++){
        table[x]=NULL;
    }
}

int main(){
    NodePtr table[M];
    int menuOpt,key;
    NodePtr foundAt;

    initTable(table);

    //menu
    while(1){
        printf("1. Insert a new key\n");
        printf("2. Search a given key\n");
        printf("3. Delete a given key\n");
        printf("4. Display hash table\n");
        printf("5. Quit\n");
        scanf("%d",&menuOpt);
        getchar();

        switch(menuOpt){
            case 1:
                printf("Enter key to insert: ");
                scanf("%d",&key);
                getchar();
                Insert(table,key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d",&key);
                getchar();
                foundAt=Search(table,key);
                printf("Found At: %d\n",foundAt);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d",&key);
                getchar();
                Delete(table,key);
                break;
            case 4:
                Display(table);
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Error, input should be between 1-5\n");
                break;
        }
    }

    return 0;
}
