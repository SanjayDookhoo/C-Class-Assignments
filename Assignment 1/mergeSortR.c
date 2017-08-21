/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/
#include <stdlib.h>
#include <stdio.h>
#define MaxNum 8

void merge(int A[],int lo,int mid,int hi){
    static int T[MaxNum];
    int i=lo;
    int j=mid+1;
    int k=lo;
    while(i<=mid ||j<=hi){
        if(i>mid) T[k++] = A[j++];//first half of sorted array already allocated, so allocate seccond half
        else if(j>hi) T[k++] =A[i++];//second half of sorted array already allocated, so allocate first half
        else if(A[i]<A[j]) T[k++] = A[i++];
        else T[k++] = A[j++];
    }

    for(j=lo;j<=hi;j++) A[j] = T[j];//since it was stored in a temporary array, copy from temporary array into relevant array
}

void mergeSort(int A[],int lo,int hi){
    void merge(int [],int,int,int);
    if(lo<hi){
        int mid=(lo+hi)/2;
        mergeSort(A,lo,mid);
        mergeSort(A,mid+1,hi);
        merge(A,lo,mid,hi);
    }
}

int main(){
    int A[MaxNum]={8,3,2,9,7,1,5,4};

    mergeSort(A,0,MaxNum-1);

    int x;
    for(x=0;x<8;x++){
        printf("%d ",A[x]);
    }
    return 0;
}
