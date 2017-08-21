/*
Name: Sanjay Thistle Kashmir Dookhoo
ID: 814000842
Course Code: COMP 3000
Assignment: 2
Summer: 3

Statement of Problem:
    Write a program to fill a 5 x 5 grid such that each row (from left to right),
	each column (from top to bottom) and each diagonal (from left to right) form a
	5-digit prime number. The sum of the digits of each prime is the same. For example:

		1	1	3	5	1

		3	3	2	0	3

		3	0	3	2	3

		1	4	0	3	3

		3	3	3	1	1

	Here, the digits of each prime add up to 11. The diagonal primes are 13331 and 34301.

	Data consists of two numbers, m and n. The digits of each prime must
	add up to m and n must be placed in the top-left position.
	In the example, m = 11 and n = 1.

	You may use the same prime more than once in the grid.
	You must output all possible solutions.

	In addition to the above, there are two other
	solutions for m = 11 and n = 1. They are:

		1 1 3 5 1		1 3 3 1 3
		1 4 0 3 3		1 3 0 4 3
		3 0 3 2 3 	and	3 2 3 0 3
		5 3 2 0 1		5 0 2 3 1
		1 3 3 1 3 		1 3 3 3 1

Method of Solution / Problem Analysis

    Since each of the 5x5 squares of digits, fulfilling certain prerequisites, must be created (rather than only one), a methodical approach is important to
    deplete all potential outcomes. One vital subtask is to perceive five-digit primes with a given digit entirety.

    Give us a chance to research a few numbers, for example, the quantity of 5x5 digit squares. There are 25 digits in the square; the digit in the upper
    left-hand corner is given. Accordingly, there are at most 10^24 squares to be considered. This number can be decreased significantly. For example,
    the top line and the left segment can't contain any zeroes. Additionally the digit wholes of five lines, five segments, and two diagonals are given,
    twelve digit totals out and out. That generally implies that twelve digits are dictated by the others. Likewise watch that the nine digits in the
    base line and the furthest right segment are odd. Disregarding the points of interest of primes, this implies the quantity of applicant 5x5 squares
    is on the request of 9^6*10^6/2^9, or roughly 10^9. This is more than you can hope to explore in 90 seconds on a 33 MHz machine (90 seconds at
    that point give you 3*10^9 clock cycles).

    Obviously, numerous blends can be precluded at an early stage, as a result of the primality condition. We can either check primality of 5-digit
    numbers on-the-fly (while filling in the square), or make a table of them toward the start (before filling in the square). What does it cost to
    check primality on-the-fly? Consider for example the strategy that works by trial division. There are 65 primes <=sqrt(99,999). (The 65th and 66th
    prime are 313 and 317, moreover 313*313=97,969 and 317*317=100,489. I deceived here: I asked Mathematica. You can likewise make a harsh gauge
    by utilizing the Prime Number Hypothesis.) This implies primality testing should be possible by at most 65 isolate operations. For primes it in
    reality takes in any event that numerous divisions. This technique appears to be excessively time-exorbitant, making it impossible to do on-the-fly.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ND 5
#define DIGIT 9

struct number
{
    int d[ND+1]; /* d[i] is i-th digit of v */
    long v;   /* 5-digit prime prime[i] digit sum ds */
}     /* number */;

/*global variables*/
FILE* in, *out;
int ds;   /* given digit sum */
int tld;   /* given digit in top left-hand corner */
int s[ND+1][ND+1]; /* the square */
int n;   /* # primes */
struct number prime[800];        /* prime[0..n-1] filled in */
int first[DIGIT+1], last[DIGIT+1]; /* prime[i].d[1] = f for first[f] <= i <= last[f] */

/* Problem Specific Section */

// Here is a function IsPrime that works by trial division with all integers less than the square root (for n=99,999, this involves no more than 316 divisions):
int isPrimeGen(long n)  //pre: n >= 4
{
    int i, j, h;

    h = sqrt(n) + 1 ;
    i = 2 ;
    j = h ; //bounded linear search for smallest divisor
    while (i != j)
    {
        if (n % i == 0)
            j = i; //i divides n, n is not prime
        else
            i++ ;
    }
    return (i == h) ;
}

//Our square-generating program then starts off to read the primes with the appropriate digit sum from this file.
void storeprimes(long p, int s)
{
    int i;
    if (s == ds)
    {
        prime[n].v = p;
        for( i = 5; i >= 1; i --)
        {
            prime[n].d[i] = p % 10;
            p = p / 10;
        }
        if (first[prime[n].d[1]] == -1)  first[prime[n].d[1]] = n;
        last[prime[n].d[1]] = n;
        n += 1;
    } /* if prime[i] */
}

//generate all primes with a given number ND of digits.
void genprimes()
{
    long start=1, i, f;
    int s;

    for(i=1; i<=ND-1; i++)
        start = 10*start ;
    for(i=start; i<=(10*start)-1; i++)
        if (isPrimeGen(i))
        {
            f = i ;
            s = i % 10 ;
            while (f >= 10)
            {
                f = f / 10 ;
                s = s + f % 10 ;
            }
            storeprimes(i,s);
        }
}

void readprimes()
/* read primes prime[i] digit sum ds from file */
/* pre: primes are sorted in increasing order */
{
    int s,i,f;
    long p;

    for( n = 1; n <= 9; n ++)   /* empty ranges */
    {
        first[n] = -1;
        last[n] = -2;
    }
    n = 0;

    genprimes();
}   /* ReadPrimes */
// ===end of change ===

int isprimeNarrowed(long w)
{
    //return: w is a 5-digit prime with digit sum ds
    int i, j, h;
    i = 0 ;
    j = n ;
    // w in prime[0..n-1].v == w in prime[i..j-1].v
    while (i != j-1)
    {
        h = (i+j) / 2 ;
        if (prime[h].v <= w)
            i = h;
        else
            j = h;
    }
    return (prime[i].v == w);
}

void writesquare(FILE *out)
{
    int r, c;

    for( r = 1; r <= 5; r ++)
    {
        for( c = 1; c <= 5; c ++)
            fprintf(out,"%d",s[r][c]);
        fprintf(out,"\n");
    }   /* for r */
    fprintf(out,"\n");
}   /* WriteSquare */

int solutions;

void writesolution()
{
    writesquare(out);
    solutions += 1;
}   /* WriteSolution */

/*
To decrease the quantity of potential outcomes however much as could reasonably be expected, we should attempt to fill openings for which whatever number digits as could reasonably be expected are now known, in light of the fact that this limits the quantity of primes that will fit there. Many requests are conceivable. Give me a chance to present names for the spaces as takes after: H1 to H5 for the even openings (lines 1 to 5), V1 to V5 for the vertical openings (segments 1 to 5), and D1 and D2 for the corner to corner openings (D1 from upper left to base right and D2 from base left to upper right). We pick the request:

H1, V1, D2, H2, V2, H3, V3, H4, V4, H5, V5, D1

The digits are then created in the accompanying request:

1 2 3 4 5

6 13 14 12 15

7 16 11 18 19

8 10 20 22 23

9 17 21 24 25

A decent property of this request is that the main digit is as of now known for each opening that is being filled: The upper left digit is given and it is the primary digit of H1 and V1. The principal digits of every (other) space are secured by H1 and V1. Since the main digit of each opening is known, we can limit thoughtfulness regarding primes from the table that begin with that digit.
*/
void h1() ;
void h2() ;
void h3() ;
void h4() ;
void h5() ;
void v1() ;
void v2() ;
void v3() ;
void v4() ;
void v5() ;
void d1() ;
void d2() ;

void computeanswer()
{
    s[1][1] = tld;
    solutions = 0;
    h1();
    fprintf(out, "Number of solutions = %d\n",solutions);
}   /* ComputeAnswer */

int odd(long x)
{
    if(x%2!=0) return 1;
    return 0;
}

//Just the primary digit is known. All primes with this first digit are crossed by the for-circle. Just the primes without zeroes are filled in, after which V1 proceeds.
void h1()
{
    const int r = 1;
    int i,c;

    for( i = first[tld]; i <= last[tld]; i ++)
    {
        if (prime[i].d[2] != 0)
            if (prime[i].d[3] != 0)
                if (prime[i].d[4] != 0)
                {
                    for( c = 2; c <= 5; c ++) s[r][c] = prime[i].d[c];
                    v1();
                }
    }  /* if */
}   /* H1 */

//The methodology for V1 is nearly the same. as above
void v1()
{
    const int c = 1;
    int i,r;

    for( i = first[tld]; i <= last[tld]; i ++)
    {
        if (prime[i].d[2] != 0)
            if (prime[i].d[3] != 0)
                if (prime[i].d[4] != 0)
                {
                    for( r = 2; r <= 5; r ++) s[r][c] = prime[i].d[r];
                    d2();
                }
    }  /* if */
}   /* V1 */

//The primary digit of opening D2 is in position S[5, 1]. For each prime with this first digit, we check whether its last digit d[5] matches the digit effectively introduce in position S[1, 5] (filled in by H1). On the off chance that that is the situation, the other three digits of the prime are duplicated into the square and H2 proceeds.
void d2()
{
    int i;

    for( i = first[s[5][1]]; i <= last[s[5][1]]; i ++)
    {
        if (prime[i].d[5] == s[1][5])
        {
            s[4][2] = prime[i].d[2];
            s[3][3] = prime[i].d[3];
            s[2][4] = prime[i].d[4];
            h2();
        }
    }  /* if */
}   /* D2 */

//Techniques H2, V2, H3, V3, and H4 are all fundamentally the same as, just more digits are known and should be checked, while less digits are duplicated.
void h2()
{
    const int r = 2;
    int i;

    for( i = first[s[r][1]]; i <= last[s[r][1]]; i ++)
    {
        if (prime[i].d[4] == s[r][4])
        {
            s[r][2] = prime[i].d[2];
            s[r][3] = prime[i].d[3];
            s[r][5] = prime[i].d[5];
            v2();
        }
    }  /* if */
}   /* H2 */

//Techniques H2, V2, H3, V3, and H4 are all fundamentally the same as, just more digits are known and should be checked, while less digits are duplicated.
void v2()
{
    const int c = 2;
    int i;

    for( i = first[s[1][c]]; i <= last[s[1][c]]; i ++)
    {
        if (prime[i].d[2] == s[2][c])
            if (prime[i].d[4] == s[4][c])
            {
                s[3][c] = prime[i].d[3];
                s[5][c] = prime[i].d[5];
                h3();
            }
    }  /* if */
}   /* V2 */

//Techniques H2, V2, H3, V3, and H4 are all fundamentally the same as, just more digits are known and should be checked, while less digits are duplicated.
void h3()
{
    const int r = 3;
    int i;

    for( i = first[s[r][1]]; i <= last[s[r][1]]; i ++)
    {
        if (prime[i].d[2] == s[r][2])
            if (prime[i].d[3] == s[r][3])
            {
                s[r][4] = prime[i].d[4];
                s[r][5] = prime[i].d[5];
                v3();
            }
    }  /* if */
}   /* H3 */

//Techniques H2, V2, H3, V3, and H4 are all fundamentally the same as, just more digits are known and should be checked, while less digits are duplicated.
void v3()
{
    const int c = 3;
    int i;

    for( i = first[s[1][c]]; i <= last[s[1][c]]; i ++)
    {
        if (prime[i].d[2] == s[2][c])
            if (prime[i].d[3] == s[3][c])
            {
                s[4][c] = prime[i].d[4];
                s[5][c] = prime[i].d[5];
                h4();
            }
    }  /* if */
}   /* V3 */

//Techniques H2, V2, H3, V3, and H4 are all fundamentally the same as, just more digits are known and should be checked, while less digits are duplicated.
void h4()
{
    const int r = 4;
    int i;

    for( i = first[s[r][1]]; i <= last[s[r][1]]; i ++)
    {
        if (prime[i].d[2] == s[r][2])
            if (prime[i].d[3] == s[r][3])
            {
                s[r][4] = prime[i].d[4];
                s[r][5] = prime[i].d[5];
                v4();
            }
    }  /* if */
}   /* H4 */


//Strategy V4 is marginally unique, in that everything except the last digit are as of now known. We can basically figure the rest of the digit on the grounds that the digit whole is given. At the point when this digit is figured, all that remaining parts is to check whether the subsequent number is prime. For that reason we have acquainted a capacity with look into a number in the table of primes. Since the table of primes is sorted on extent we can do a double hunt (this is the motivation behind why not just the digits of the primes are required additionally their `whole esteems').
void v4()
{
    const int c = 4;
    int d,r;
    long w;

    d = ds;
    w = 0;
    for( r = 1; r <= 4; r ++)
    {
        d = d - s[r][c];
        w = 10*w + s[r][c];
    }   /* for */
    if (odd(d) && (0 <= d) && (d <= 9))
        if (isprimeNarrowed(10*w+d))
        {
            s[5][c] = d;
            h5();
        }   /* if */
}   /* V4 */

//Procedure H5 is similar to V4.
void h5()
{
    const int r = 5;
    int d,c;
    long w;

    d = ds;
    w = 0;
    for( c = 1; c <= 4; c ++)
    {
        d = d - s[r][c];
        w = 10*w + s[r][c];
    }   /* for */
    if (odd(d) && (0 <= d) && (d <= 9))
        if (isprimeNarrowed(10*w+d))
        {
            s[r][5] = d;
            v5();
        }   /* if */
}   /* H5 */

//For slots V5 and D1 all digits are known and the only remaining task is to check primality.
void v5()
{
    const int c = 5;
    int r;
    long w;

    w = 0;
    for( r = 1; r <= 5; r ++) w = 10*w + s[r][c];
    if (isprimeNarrowed(w))  d1();
}   /* V5 */

//For slots V5 and D1 all digits are known and the only remaining task is to check primality.
void d1()
{
    int rc;
    long w;

    w = 0;
    for( rc = 1; rc <= 5; rc ++) w = 10*w + s[rc][rc];
    if (isprimeNarrowed(w))  writesolution();
}   /* D1 */

int main()
{
    //get file streams
    in=fopen("input.txt","r");
    out=fopen("output.txt","w");

    //get data from file
    fscanf(in,"%d", &ds);
    fscanf(in,"%d", &tld);

    readprimes();
    computeanswer();

    fclose(in);
    fclose(out);

    return 0;
}
