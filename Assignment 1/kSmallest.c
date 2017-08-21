
/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/
#include <stdlib.h>
#include <stdio.h>
#define MaxNum 8

int partition(int a[],int l,int r){
    int p=a[l];
    int i=l,j=r+1,temp;
    while(i<j){
        do{
            i++;
        }while(a[i]<p);

        do{
            j--;
        }while(a[j]>p);

        if(i<j){
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }
    temp=a[l];
    a[l]=a[j];
    a[j]=temp;

    return j;
}

int kSmallest(int A[],int k,int lo,int hi){
    int kShift =lo+k-1;
    if(kShift<lo || kShift>hi) return -9999;
    int dp =partition(A,lo,hi);
    while(dp!=kShift){
        if(kShift<dp)hi=dp-1;
        else lo=dp+1;
        dp=partition(A,lo,hi);
    }
    return A[dp];
}

int main(){
    int A[MaxNum]={8,3,2,9,7,1,5,4};

    printf("%d",kSmallest(A,3,0,MaxNum-1));

    return 0;
}
