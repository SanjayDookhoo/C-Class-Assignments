/*

Solution Creator:
    Name: Sanjay Dookhoo
    ID: 814000842
    Email: sanjaydookhoo@msn.com
    Course: COMP3000

Problem:
    Lorries
Description:
    Several items are loaded on a conveyor belt. As items come off the belt, they are loaded onto delivery lorries.
    All lorries are the same and they can carry items up to a specific maximum weight (called the capacity of the lorry).
    Items are numbered from 1 and are of various weights. The items must be loaded sequentially onto the lorries,
    i.e., items 1 to N (for some N) go on the first lorry, items N+1, …, M (for some M) go on the second lorry, and so on.
    Not all lorries will be loaded to their full capacity, of course, but it is guaranteed that no single item is too
    heavy for a lorry.

Input:
    The first line of data gives the value of c and the number of items, n (<= 1000). Subsequent lines contain n values,
    the weights of the items, in order. Some sample data are:

Output:
    on the first line, print the number of lorries required. On the second line, print the number of items on each lorry,
    starting with the number of items on the first lorry, followed by the number of items on the second lorry, and so on.
    On the last line print the spare capacity of the fleet. For the above data, you should output:

Solution:
    fillLorry(i) the best way to fill lorry from items i to n, where i starts a new lorry
        where
            Wi = weight of item
            c = capacity of lorry
        if fillLorry(k) > n, fillLorry(k) = 0
        fillLorry(i) = min [(c - [Wi+...+Wk])^2 + fillLorry(k+1)] for k = 1 to n, where (Wi + ... Wk) < c

        e.g. capacity = 6, no of items 5 {1, 2, 3, 1, 1}
        fillLorry(3) = min{
                (c - W3)^2 + fillLorry(4)
                (c - W3 + W4)^2 + fillLorry(5)
                (c - W3 + W4 + W5)^2 + fillLorry(6) }

    This is a version of knapsack implementation
    As shown, this can be done recursively. To reduce the time taken due to repeated unnecesary
    calculations, memoization is used to store what was already calculated. Similarly, since we
    know this function will be run for each item, therefore n times, the function calls can start
    from n to 1. This ensures that all sub calls to the function, will already have a value calculated,
    preventing the need for recursive function calls.

Reliability:
    -File exist and stream created, otherwise notify then exit(1)
    -Allocation of memory during runtime from the "amount of items" read from the file, otherwise notify then exit(1)
    -Recursion not used, no stack overflow
    -Memoization/dynamic programming used, increases processing speed

*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>// limits library used to gain access to INT_MAX, will explain later when encountered

typedef struct lorry{// will be used to create an array of length n called lorries. Where each lorry at item x represents the min sqCap to the nth item, where the end of the items associated with this lorry is itemEnd
    int sqCap;// min sqCap to the nth item
    int itemEnd;// end of the items associated with this lorry
}Lorry;

// Methods used
void fillLorry(int*, Lorry*, int, int);// Allocates the items to Lorries in such a way to minimize spare capacity
int countLorries(Lorry*, int, int);// Prints the amount of lorries utilized
void printLorries(FILE *, Lorry*, int, int);// Prints the amount of items for each lorry, in the order of 1 to n, where n is the last lorry

int main(){
    // Variables
    int n;// Amount of items that were loaded on the conveyor belt
    int c;// Capacity of each lorry
    int i;// General Counter
    int *items;// Each item's weight from 1 to N is stored in this pointer (assigned during runtime)
    Lorry *lorries; // Each Lorry's, spare capacity and end of items stored in that lorry (index of above array), from 1 to N is stored in this pointer (assigned during runtime)
	FILE *in = fopen("input.txt","r");// Input Stream
	FILE *out = fopen("output.txt","w");// Output Stream

    //if input and output streams were not successfully created, force end program
	if(in == NULL || out == NULL){
		printf("error reading files\n");
		exit(1);
	}

	fscanf(in,"%d %d",&c, &n);// Scan capacity and number of items from input file

	items = (int*) malloc((n+1)*sizeof(int));// (assigned during runtime) array is of size n+1 because the first item will be stored in index 1
    lorries=(Lorry*) malloc((n+1)*sizeof(Lorry));// (assigned during runtime) array is of size n+1 because the first item will be stored in index 1

    if(items==NULL || lorries==NULL){
        printf("memory could not be allocated\n");
		exit(1);
    }

    // For each item that is expected, store the values from the file for each item into an array called items. Note the array starts at 1.
	for(i = 1; i <= n; i++){
		fscanf(in,"%d",&items[i]);
	}

	fillLorry(items, lorries, c,n);// Stores lorries (Main Processing)

	fprintf(out,"%d\n",countLorries(lorries,n,1));// Prints the amount of Lorries needed to minimize spare capacity
	printLorries(out,lorries,n,1);// Prints the amount of items for each lorry, in the order of 1 to n, where n is the last lorry
	fprintf(out, "\n");//seperator
	fprintf(out, "%d\n", lorries[1].sqCap);// Prints the spare capacity that was minimized

    //close file streams before ending program
	fclose(in);
	fclose(out);

	return 0;
}

// Prints the amount of lorries utilized
int countLorries(Lorry *lorries, int n, int i){
	if(lorries[i].itemEnd != n){// if lorries[i].itemEnd != n then there exist another lorry
		return 1 + countLorries(lorries,n,lorries[i].itemEnd+1);// for each itemEnd that isnt n, it must mean that the lorry extends from its index i from the array to position itemEnd, therefore another lorry begins at itemEnd+1
	}

	return 1;
}

// Prints the amount of items for each lorry, in the order of 1 to n, where n is the last lorry
void printLorries(FILE *out, Lorry *lorries, int n, int i){
	fprintf(out, "%d ", lorries[i].itemEnd - i + 1);// i is the beginning of the lorry's items and itemEnd is the end of the lorry's items, therefore the difference is the amount of items in the lorry. 1 is added to include the first item also
	if(lorries[i].itemEnd != n){// if lorries[i].itemEnd != n then there exist another lorry
		printLorries(out, lorries,n,lorries[i].itemEnd+1);// for each itemEnd that isnt n, it must mean that the lorry extends from its index i from the array to position itemEnd, therefore another lorry begins at itemEnd+1
	}
}

// Allocates the items to Lorries in such a way to minimize spare capacity
void fillLorry(int *items, Lorry *lorries, int capacity, int n){
    // Variables
	int i, j, k, sqcap, min, position, sum;

	for(i = n; i >= 1; i--){ // As described in the solution, starts solving lorries from the last item, where the data is stored to then calculate the lorries for the second to last item to n, and so on
		min = INT_MAX;// this provides the highest possible number that can be represented. This ensures that whatever is the first sqcap of the lorry, it will always be less than what was already in the variable
		for(k=i; k<=n; k++){ // from the position i, each item to k is then added as the next lorry begins at k+1. with the sum added together with the next lorry's spare capacity, the min is found and noted
			sum = 0;

			for(j = i; j<=k; j++){
				sum += items[j];// from the position i, each item to k is then added as the next lorry begins at k+1
			}// end for j

			sqcap = capacity - sum;// the capacity of the lorry that was not used
			if(sqcap<0) break;// if it is less than 0, then the sum of the items exceeds how much the lorry can carry, break since everything after guarantees to cause the same problem

			sqcap = sqcap * sqcap;// The first square to calculate the sum of squares of the spare capacity of the lorries
			if(k+1 <= n){// if k+1 <= n that means that at least one more lorry will be used to store the items
				sqcap = sqcap + lorries[k+1].sqCap;// since the best spare capacity (already squared) was found for that lorry already, add from the memoization array/table
			}
			if(sqcap <= min){// if the sum of the squares of the capacity found is less than any that was previously found, save the square as well as the position of the next lorry
				min = sqcap;
				position = k;
			}

		}
		// After all sub item/lorry sets from k to n was found and the min was found, save it
		lorries[i].sqCap = min;
		lorries[i].itemEnd = position;
	}
}
