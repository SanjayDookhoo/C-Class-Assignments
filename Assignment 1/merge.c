/*
Becayse an array must be returned, c is a pointer of int type
*/

/*
Student Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: COMP 2000
*/

#include <stdlib.h>
#include <stdio.h>


int * merge(int a[],int m,int b[],int n){
    int i=0,j=0,k=0;
    //static int temp[m+n];
    int * temp= (int*)malloc(sizeof(int) * (m+n));

    while(i<m && j<n){
        if(a[i]<b[j])temp[k++]=a[i++];
        else temp[k++]=b[j++];
    }
    if(i<m){
        for(;i<m;i++){
            temp[k++]=a[i];
        }
    }else if(j<n){
        for(;j<n;j++){
            temp[k++]=b[j];
        }
    }

    return temp;

}

int main(){
    int m=5,n=4;
    int a[5]={1,7,19,22,23};
    int b[4]={0,15,19,20};
    int *c;
    c=merge(a,5,b,4);

    int x;
    for(x=0;x<m+n;x++){
        printf("%d ",c[x]);
    }

    return 0;
}
