/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define H 8
#define W 8
#define N 8//max size


typedef struct node{
    int r;
    int c;
    struct node *next;
    struct node *prev;
}Node;
/*
Node *extendHillCur(Node* start,int n, int limit){

    extendHillCur(start,n+1,limit);
}
*/
Node *copy(Node* start){
    Node *start2;
    while(start!=NULL){

        start=start->next;
    }
}

Node* constructHillCur(int n,int limit){//n is current level which starts at 1
    Node* start=NULL;
    Node curve[N][N];
    int size=(int)pow(2,1),i,j;

    //initialize struct
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            curve[i][j].r=i;
            curve[i][j].c=j;
        }
    }

    //construction of initial level=1
    start=&curve[0][0];
    curve[0][0].prev=NULL;
    curve[0][0].next=&curve[1][0];

    curve[1][0].prev=&curve[0][0];
    curve[1][0].next=&curve[1][1];

    curve[1][1].prev=&curve[1][0];
    curve[1][1].next=&curve[0][1];

    curve[0][1].prev=&curve[1][1];
    curve[0][1].next=NULL;

    //extendHillCur(start,n+1,limit);

    return start;
}

void printHillCur(int width,Node* start,int a[][width]){
    Node *curr=start;
    while(curr!=NULL){
        printf("%d ",a[curr->r][curr->c]);
        curr=curr->next;
    }
    //printf("%d ",curr->c);
}

void leftRotate(int n,int a[][n]){
    int tmp,i,j;
    for (i=0; i<n/2; i++){
            for (j=i; j<n-i-1; j++){
                    tmp=a[i][j];
                    a[i][j]=a[j][n-i-1];
                    a[j][n-i-1]=a[n-i-1][n-j-1];
                    a[n-i-1][n-j-1]=a[n-j-1][i];
                    a[n-j-1][i]=tmp;
            }
    }
}

void horFlip(int n,int a[][n]){
    int i,j,tmp;
    for(i=0;i<n/2;i++){
        for(j=0;j<n;j++){
            tmp=a[i][j];
            a[i][j]=a[n-1-i][j];
            a[n-1-i][j]=tmp;
        }
    }
}

int main(){
    int A[N][N]={0,1,5,6,14,9,14,2,
                 2,4,7,13,15,7,56,4,
                 3,8,12,16,21,8,1,3,
                 9,11,17,20,22,4,51,3,
                 10,18,19,23,24,20,14,36,
                 7,11,17,20,22,4,51,3,
                 6,11,17,20,22,4,51,3,
                 5,11,17,20,22,4,51,3};
    Node* start=constructHillCur(1,8);
    printHillCur(N,start,A);
    return 0;
}
