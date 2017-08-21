/* Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/

//in hash table
//-1 : empty
//-2 : deleted
//this method assumes there will always be 1 hash location available
#include <stdio.h>
#include <stdlib.h>

#define M 10


typedef struct node{
    int k;
}Node;

int rehash(int key, int t){
    return (key+(t*t))%M;
}

int hash(int key){
    return key%M;
}

void Insert(Node table[],int key){
    int t=1;
    int h1=hash(key);
    int loc=h1;
    int deletedLoc=0;
    while(table[loc].k!=-1 && table[loc].k!=key){
        if(deletedLoc==0 && table[loc].k==-2) deletedLoc=loc;
        loc=rehash(h1,t++);//resolsvign collision
    }
    if(table[loc].k==-1){//key not found
        if(deletedLoc!=0) loc=deletedLoc;
        table[loc].k=key;
    }else{//no need for else since only distinct values are entered
    }
}

int Search(Node table[],int key){//returns the index i if found otherwise returns M.
    int t=1;
    int h1=hash(key);
    int loc=h1;
    while(table[loc].k!=-1 && table[loc].k!=key){
        loc=rehash(h1,t++);//resolvign collision
    }
    if(table[loc].k==-1) return M; //key not found
    else return loc;//key found
}

void Delete(Node table[], int key){
    int toDeleteLoc=Search(table,key);
    if(toDeleteLoc!=M){
        table[toDeleteLoc].k=-2;
    }else{
        printf("Key not found\n");
    }
}

void Display(Node table[]){
    int x;
    printf("Index\tData\n");
    for(x=0;x<M;x++){
        if(table[x].k==-1) printf("%d\tEMPTY\n",x);
        else if (table[x].k==-2) printf("%d\tDELETED\n",x);
        else printf("%d\t%d\n",x,table[x].k);
    }
}

void initTable(Node table[]){
    int x;
    for(x=0;x<M;x++){
        table[x].k=-1;
    }
}

int main(){
    Node table[M];
    int menuOpt,key,foundAt;

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
