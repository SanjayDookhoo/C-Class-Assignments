/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/

#include <stdlib.h>
#include <stdio.h>
#define m 5
#define n 4
int b[m*n];
int a[m][n];

void tran2Dto1DSM(){
    int i=0,j=0;
    for(i=0;i<=m;i++){
        for(j=0;j<=n;j++){
            b[(i+1)*(i)/2+j+1]=a[i][j];

        }
    }
}

void tran1Dto2DSM(){
    int i=0,j=0;
    for(i=0;i<=m;i++){
        for(j=0;j<=n;j++){
            if(i>=j)
                a[i][j]=b[(i+1)*(i)/2+j+1];
            else
                a[i][j]=b[(j+1)*(j)/2+i+1];
        }
    }
}

int main(){

    return 0;
}
