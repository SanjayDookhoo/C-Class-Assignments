/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/
#include <stdlib.h>
#include <stdio.h>
#define MaxNum 8

//Partition: Lomuto’s Algorithm
/*
TO HELP UNDERSTAND:
the first element is treated as the pivot
from index 1 to s is all elements less than the pivot
if an element is found to be less than the pivot, s is incremented by 1, and it swaps to that position, this is if its current position isnt already s++, then swapping is unnessary
all index greater than s is greater than the pivot
the element at index s will swap with the element at index 1 to become the pivot, which is returned
*/
int partition(int a[],int l,int r){
    int p=a[l];//partition element
    int s=l;//partition location/source
    int i,temp;
    for(i=l+1;i<=r;i++){
        if(a[i]<p){
            s=s+1;
            if(s!=i){
                temp=a[i];
                a[i]=a[s];
                a[s]=temp;
            }
        }
    }
    temp=a[l];
    a[l]=a[s];
    a[s]=temp;

    return s;
}

void quickSort(int a[],int l,int r){
    if (l<r){
        int s=partition(a,l,r);
        quickSort(a,l,s-1);
        quickSort(a,s+1,r);
    }
}

int main(){
    int A[MaxNum]={8,3,2,9,7,1,5,4};

    quickSort(A,0,MaxNum-1);

    int x;
    for(x=0;x<8;x++){
        printf("%d ",A[x]);
    }
    return 0;
}
