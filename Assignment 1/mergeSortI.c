/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/
#include <stdlib.h>
#include <stdio.h>
#define MaxNum 8

void CopyArray(int B[],int A[],int n){
    int i;
    for(i=0;i< n;i ++)
        A[i]=B[i];
}

int min(int a,int b){
    if (a<b) return a;
    else return b;
}

void BottomUpMergeSort(int A[],int B[],int n){
    int width,i;

    for (width = 1; width < n; width = 2 * width){
        for (i = 0; i < n; i = i + 2 * width){
          BottomUpMerge(A, i, min(i+width, n), min(i+2*width, n), B);
        }
        CopyArray(B, A, n);
    }
}

BottomUpMerge(int A[],int iLeft,int iRight,int iEnd,int B[]){
    int i = iLeft, j = iRight,k;

    for (k = iLeft; k < iEnd; k++) {
        if (i < iRight && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}

int main(){
    int A[MaxNum]={8,3,2,9,7,1,5,4};
    int B[MaxNum];

    BottomUpMergeSort(A, B, MaxNum);

    int x;
    for(x=0;x<8;x++){
        printf("%d ",A[x]);
    }
    return 0;
}
