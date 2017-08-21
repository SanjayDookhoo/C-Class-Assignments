/* Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/

//in hash table
//-1 : empty
//this method assumes there will always be 1 hash location available
#include <stdio.h>
#include <stdlib.h>

#define M 10


typedef struct node{
    int k;
    int next;
}Node;

int lastLink(Node table[],int loc){
    int prevLoc=loc;
    while(loc!=-1){//another link exist
        prevLoc=loc;
        loc=table[loc].next;
    }
    return prevLoc;
}

int hash(int key){
    return key%M;
}

int rehash(int key, int t){
    return (key-t)%M;
}

void Insert(Node table[],int key){
    int t=1;
    int h1=hash(key);
    int loc=h1;
    int loc2;
    int base=10;
    if(table[loc].k==-1 ){
        table[loc].k=key;

    }else{
        loc=lastLink(table,h1);
        //find an empty space to hash via some collision resolution from first hash (used linear hashing)
        loc2=rehash(base,t++);
        while(table[loc2].k!=-1 ){
            loc2=rehash(base,t++);
        }
        //assign data to empty space found
        table[loc2].k=key;
        //assign lastLink to point to the new space
        table[loc].next=loc2;

    }
}

int Search(Node table[],int key){//returns the index i if found otherwise returns M.
    int t=1;
    int h1=hash(key);
    int loc=h1;
    int loc2;


    if(table[loc].k==key){//only one at loc
        return loc;
    }else{//chained
        while(table[loc].k!=key && table[loc].next!=-1){
            loc=table[loc].next;
        }

        if(table[loc].k==key) return loc;
        else return M;
    }
}

int prevFoundAt(Node table[],int key){//returns the index i of what points to the key
    int t=1;
    int h1=hash(key);
    int loc=h1;
    int prevLoc;


    if(table[loc].k==key){
        return -1;
    }else{
        while(table[loc].k!=key && table[loc].next!=-1){
            prevLoc=loc;
            loc=table[loc].next;
        }

        if(table[loc].k==key) return prevLoc;
        else return M;
    }
}

void Delete(Node table[], int key){
    int h1=hash(key);
    int foundAt=Search(table,key);
    int loc=foundAt;
    int prevLoc=prevFoundAt(table,key);
    int nextLoc=table[loc].next;

    if(foundAt!=M){
        //if(foundAt==h1){//key is at its original hash location

        //}else{
            if(table[loc].next==-1){//last link
                table[loc].k=-1;
                table[prevLoc].next=-1;
            }else{//first or middle link


                while(table[loc].next!=-1){
                    table[loc].k=table[nextLoc].k;
                    table[loc].next=table[nextLoc].next;

                    table[nextLoc].k=-1;
                    table[nextLoc].next=-1;

                    loc=nextLoc;
                    nextLoc=table[nextLoc].next;
                }
            //}
        }
    }else{
        printf("key does not exist to delete\n");
    }
}

void Display(Node table[]){
    int x;
    printf("Index\tK\tnext\n");
    for(x=0;x<M;x++){
        printf("%d\t%d\t%d\n",x,table[x].k,table[x].next);
    }
}

void initTable(Node table[]){
    int x;
    for(x=0;x<M;x++){
        table[x].k=-1;
        table[x].next=-1;
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
