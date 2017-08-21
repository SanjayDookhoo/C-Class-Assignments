/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/
#include <stdlib.h>
#include <stdio.h>
#define H 5
#define W 5

void zigzag(int A[][W]){
    int x,y,z;
    for(x=0;x<H;x++){
        for(y=0;y<=x && y<H;y++){
            printf("%d ",A[y][x-y]);
        }
    }

    for(x=1;x<W;x++){
        for(y=0;y<H-x ;y++){
            printf("%d ",A[x+y][W-1-y]);
        }
    }
}

int main(){
    int A[H][W]={0,1,5,6,14,
                 2,4,7,13,15,
                 3,8,12,16,21,
                 9,11,17,20,22,
                 10,18,19,23,24};
    //printf("%d",A[1][4]);
    zigzag(A);
    return 0;
}
