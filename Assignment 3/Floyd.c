/*
Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: Comp2000
*/

#include <stdio.h>
#define V 3
#define Infinity 9999

void floyd(int D[V][V],int Path[V][V],int W[V][V]){
    int i,j,k,num;

    //initialize path to all be -1,meaning there is no intermediate path for any
    for (i=0; i<V; i++) {
        for (j=0; j<V; j++) {
            Path[i][j]=-1;
        }
    }
    //initialize D to W, because the original weight would be lost otherwise, so D is used to store the cost
    for (i=0; i<V; i++) {
        for (j=0; j<V; j++) {
            D[i][j]=W[i][j];
        }
    }

    for (k=0; k<V; k++) {//intermediate node
        for (i=0; i<V; i++) {//fixed vertex row
            for (j=0; j<V; j++) {//fixed vertex col
                num=D[i][k]+D[k][j];
                if (num<D[i][j]) {
                    D[i][j]=num;
                    Path[i][j]=k;
                }
            }
        }

        //print cost matrix for every intermediate node
        printf("D(%d) is:\n",k+1);
        for (i=0; i<V; i++) {
            for (j=0; j<V; j++) {
                if(D[i][j]!=Infinity)
                    printf("%d \t",D[i][j]);
                else
                    printf("%c \t",'I');

            }
            printf("\n");
        }
        printf("\n");
    }


}

int main(){
    int i,j;
    int graph[V][V] = {
        {0, 4, 11},
        {6, 0, 2},
        {3, Infinity, 0}
    };
    int D[V][V];
    int Path[V][V];

    //print weight matrix
    printf("The weight matrix W is:\n");
    for (i=0; i<V; i++) {
        for (j=0; j<V; j++) {
            if(graph[i][j]!=Infinity)
                printf("%d \t",graph[i][j]);
            else
                printf("%c \t",'I');
        }
        printf("\n");
    }
    printf("\n");

    floyd(D,Path,graph);
    //print distance matrix
    printf("The distance matrix D is:\n");
    for (i=0; i<V; i++) {
        for (j=0; j<V; j++) {
            if(D[i][j]!=Infinity)
                printf("%d \t",D[i][j]);
            else
                printf("%c \t",'I');

        }
        printf("\n");
    }
    printf("\n");

    //print path matrix
    printf("The Path matrix is:\n");
    for (i=0; i<V; i++) {
        for (j=0; j<V; j++) {
            printf("%d \t",Path[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}
