/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/
#include <stdlib.h>
#include <stdio.h>
#define MaxNum 8

//Partition: Hoare’s Algorithm
/*
TO HELP UNDERSTAND:
the first element is treated as the pivot
the first half of the array is less than p
the second half of the array is greater than p
the var i is an element that isnt less than p from the left
the var j is an element that isnt greater than p from the right
if i<j swap i and j elements thereby allowing the partition to exist

from index 1 to s is all elements less than the pivot
if an element is found to be less than the pivot, s is incremented by 1, and it swaps to that position, this is if its current position isnt already s++, then swapping is unnessary
all index greater than s is greater than the pivot
the element at index s will swap with the element at index 1 to become the pivot, which is returned
*/
int partition(int a[],int l,int r){
    int p=a[l];//partition element
    int i=l;//partition location/source
    int j=r+1;//set to r+1 because of the do while minusing 1
    int temp;

    while(i<j){
        do{
            i++;
        }while(i<j && a[i]<p);//the i<j check is necessary because all elements coming after the first can be less than the pivot, causing i to exceed the index boundary

        do{
            j--;
        }while(a[j]>p);// an extra check isnt needed here because the pivot cannot be greater than itself

        if(i<j){
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }
    //can swap with i or j at this point
    temp=a[l];
    a[l]=a[j];
    a[j]=temp;

    return j;
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
