/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/
#include <stdlib.h>
#include <stdio.h>
#define MaxNum 8

//for heapsort to be in ascending order, the heap must be a maxHeap
//for heapsort to be in descending order, the heap must be a minHeap

//sift down for a maxHeap
void siftDown(int key,int num[],int root, int last){
    int bigger=2*root+1;
    while(bigger<=last){
        if (bigger<last)
            if (num[bigger+1]>num[bigger]) bigger++;
        if(key>=num[bigger]) break;
        num[root] =num[bigger];
        root=bigger;
        bigger=2*root;
    }
    num[root]=key;
}

//shell sort
//where n represents the last index
void heapSort(int num[],int n){
    int k;
    for(k=n/2;k>=0;k--) siftDown(num[k],num,k,n);
    for (k=n;k>0;k--){
        int item=num[k];
        num[k]=num[0];//TO NOTE: if it was just MaxNum then k can be 8 in this case, which was not set, if it was a low number then it would be included in the final array when it is sorted(since it is sorting in ascended) which is incorrect
        siftDown(item,num,0,k-1);
    }
}

int main(){
    int A[MaxNum]={8,3,2,9,7,1,5,4};

    heapSort(A,MaxNum-1);//MaxNum-1 is necessary here, look at TO NOTE

    int x;
    for(x=0;x<MaxNum;x++){
        printf("%d ",A[x]);
    }
    return 0;
}
