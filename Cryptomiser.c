/*Cryptomiser Encryption Library in C Language with optimised RSA Copyright (C) 2016 Avi Sharma, Mukul Kashiv and Shivam Srivastava

GNU GENERAL PUBLIC LICENSE V3 This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "rsa.h"
#define MAX_DIGITS 1024
// Numbers will be stored as an array arr of integers.
// arr[0] is a one's digit, arr[1] the 10's digit, etc.


#define KARAT_CUTOFF 4
// When karatsuba() gets to numbers with at most KARAT_CUTOFF
// digits, it reverts to straight grade-school multiplication.
// (This helps because karatsuba() is slower than grade-school
// multiplication for tiny values of n.)

// Within karatsuba() and gradeSchool(), we do not worry about whether
// the `digits' are actually between 0 and 9; this is fixed after we
// return from the call with doCarry().
//
// WARNING! This is potentially problematic if the `digits' get so
// large that we have overflow. With 32-bit ints and KARAT_CUTOFF==4,
// we are safe up to 1024 digits; more than this is potentially
// problematic. One easy way to avoid this is to call doCarry()
// for larger values, but the below code does not do this.

void            karatsuba(int *a, int *b, int *ret, int d);
void            gradeSchool(int *a, int *b, int *ret, int d);
void            doCarry(int *a, int d);
void            getNum(int *a, int *d_a);
void            printNum(int *a, int d);
long long int   arrayToInt(int *A ,int len);
void            primality(int *a, int *b);


  long long int            a[MAX_DIGITS]; // first multiplicand
  long long int             b[MAX_DIGITS]; // second multiplicand

	// result goes here
    int             d_a; // length of a
    int             d_b; // length of b


int main() {
int y;
  printf("Choose operation: \n");
  printf("1: Show CPU info\n");
  printf("2: Run optimised text encryption\n");

  scanf(" %d", &y);
  switch(y)
  {
  case 1 : cpuinfofunc(); break;
  case 2 : cryptomiser(); break;

  default : printf("Invalid input.");
  }
    return 0;
}


int cpuinfofunc(int argc, char **argv){
  char z;

  FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
  char *arg22 = 0;
  size_t size = 0;
  while(getdelim(&arg22, &size, 0, cpuinfo) != -1)
  {
     puts(arg22);
  }
  free(arg22);
  fclose(cpuinfo);

printf("\nDo you want to clear the screen and return to menu? [Y/N]");
scanf(" %c", &z);
switch(z)
{
  case 'Y': system("clear"); main(); break;
  case 'y': system("clear"); main(); break;
  case 'N': break;
  case 'n': break;
}

}

void cryptomiser()
{
  int             d; // maximum length
  int             i; // counter
  int             j; // counter 2
  int             r[6 * MAX_DIGITS];
  int             y; //for switch
clock_t         start; // for timing
clock_t         stop; // for timing
printf("Enter first unique prime number, p: \n");
getNum( a, &d_a); // Error, does not prompt for user input
getNum( a, &d_a); // makeshift solution for error by overwriting
printf("Enter second unique prime number, q: \n");
getNum( b, &d_b);
rsa();
if(d_a < 0 || d_b < 0) {
    printf("0\n");
    exit(0);
    return 0;
}
//printf("1\n");
// let d be the smallest power of 2 greater than d_a and d_b,
// and zero out the rest of a and b.
i = (d_a > d_b) ? d_a : d_b;
for(d = 1; d < i; d *= 2);
for(i = d_a; i < d; i++) a[i] = 0;
for(i = d_b; i < d; i++) b[i] = 0;

// do the trials, first for Karatsuba, then for grade-school.
// For each trial, we print the result, followed by the time
// taken per multiplication, followed by the number of
// multiplications done. We do as many multiplications as we
// can until we pass away an entire second.
   start = clock();
   stop = start + CLOCKS_PER_SEC;
  // printf("2\n");
   primality(a,b);

for(j = 0; clock() < stop; j++) {

    karatsuba(a, b, r, d); // compute product w/o regard to carry
    doCarry(r, 2 * d); // now do any carrying
}
start = clock() - start;

ce(ta);

start = clock();
stop = start + CLOCKS_PER_SEC;
for(i = 0; clock() < stop; i++) {
    gradeSchool(a, b, r, d); // compute product in old way
    doCarry(r, 2 * d); // now do any carrying
}
start = clock() - start;
    printf("\n\n");
printNum(r, 2 * d);
printf("\n==========================================");
encrypt();
decrypt();
printf("\nRSA:\n");
<<<<<<< HEAD
float x = 1000 * (double) start / CLOCKS_PER_SEC / j - 1000 * (double) start / CLOCKS_PER_SEC / i; // i for RSA
printf("%f ms (%d trials)\n", 1000 * (double) start / CLOCKS_PER_SEC / i, i);

printf("\nOptimised RSA:\n");
printf("%f ms (%d trials)\n", 1000 * (double) start / CLOCKS_PER_SEC / j, j); // j for optimised RSA
printf("\nTime difference: %f ms\n\n", x);
=======
float x = 1000 * (double) start / CLOCKS_PER_SEC / j - 1000 * (double) start / CLOCKS_PER_SEC / i;
printf("%f ms (%d trials)\n", 1000 * (double) start / CLOCKS_PER_SEC / i, i);

printf("\nOptimised RSA:\n");
printf("%f ms (%d trials)\n", 1000 * (double) start / CLOCKS_PER_SEC / j, j);
printf("\nPerformance boost: %f ms\n\n", x);
>>>>>>> ed3bda343e8977a59cec30412676ba959f9e1ea4
 //printf("Value of ta is %lld",ta);



}
void primality(int *a, int *b ){
	int len=        d_a;
	int len2=       d_b;
    long long int   k,j,r,m,p,q;
    int             i;
	int             A[len];
    int             B[len];

	for(i=len-1;i>=0;i--){
	A[i]=a[i];
	}

	for(i=(len2)-1;i>=0;i--){
	B[i]=b[i];
	}

  p=arrayToInt(A,len);

  //printf("\nA done without exit");
  printf("P is %lld\n",p);
  q=arrayToInt(B,len2);
  printf("Q is %lld\n",q);
  //printf("\nB done without exit");
   n=p*q;
   ta=(p-1)*(q-1);
   p1=p;
   q1=q;
//	ce(ta);

}

// ret must have space for 6d digits.
// the result will be in only the first 2d digits
// my use of the space in ret is pretty creative.
// | ar*br  | al*bl  | asum*bsum | lower-recursion space | asum | bsum |
//  d digits d digits  d digits     3d digits              d/2    d/2
void karatsuba(int *a, int *b, int *ret, int d) {
    int             i;
    int             *ar = &a[0]; // low-order half of a
    int             *al = &a[d/2]; // high-order half of a
    int             *br = &b[0]; // low-order half of b
    int             *bl = &b[d/2]; // high-order half of b
    int             *asum = &ret[d * 5]; // sum of a's halves
    int             *bsum = &ret[d * 5 + d/2]; // sum of b's halves
    int             *x1 = &ret[d * 0]; // ar*br's location
    int             *x2 = &ret[d * 1]; // al*bl's location
    int             *x3 = &ret[d * 2]; // asum*bsum's location

    // when d is small, we're better off just reverting to
    // grade-school multiplication, since it's faster at this point.
    if(d <= KARAT_CUTOFF) {
        gradeSchool(a, b, ret, d);
        return;
    }

    // compute asum and bsum
    for(i = 0; i < d / 2; i++) {
        asum[i] = al[i] + ar[i];
        bsum[i] = bl[i] + br[i];
    }

    // do recursive calls (I have to be careful about the order,
    // since the scratch space for the recursion on x1 includes
    // the space used for x2 and x3)
    karatsuba(ar, br, x1, d/2);
    karatsuba(al, bl, x2, d/2);
    karatsuba(asum, bsum, x3, d/2);

    // combine recursive steps
    for(i = 0; i < d; i++) x3[i] = x3[i] - x1[i] - x2[i];
    for(i = 0; i < d; i++) ret[i + d/2] += x3[i];
}

void
gradeSchool(int *a, int *b, int *ret, int d) {
    int             i, j;

    for(i = 0; i < 2 * d; i++) ret[i] = 0;
    for(i = 0; i < d; i++) {
        for(j = 0; j < d; j++) ret[i + j] += a[i] * b[j];
    }
}

void
doCarry(int *a, int d) {
    int             c;
    int             i;

    c = 0;
    for(i = 0; i < d; i++) {
        a[i] += c;
        if(a[i] < 0) {
            c = -(-(a[i] + 1) / 10 + 1);
        } else {
            c = a[i] / 10;
        }
        a[i] -= c * 10;
    }
    if(c != 0) fprintf(stderr, "Overflow %d\n", c);
}

void
getNum(int *a, int *d_a) {
    int             c;
    int             i;

    *d_a = 0;
    while(1) {
        c = getchar();
        if(c == '\n' || c == EOF) break;
        if(*d_a >= MAX_DIGITS) {
            fprintf(stderr, "using only first %d digits\n", MAX_DIGITS);
            while(c != '\n' && c != EOF) c = getchar();
        }
        a[*d_a] = c - '0';
        ++(*d_a);
    }
    // reverse the number so that the 1's digit is first
    for(i = 0; i * 2 < *d_a - 1; i++) {
        c = a[i], a[i] = a[*d_a - i - 1], a[*d_a - i - 1] = c;
    }
}

void
printNum(int *a, int d) {
    int i;
    for(i = d - 1; i > 0; i--) if(a[i] != 0) break;
    for(; i >= 0; i--) printf("%lld", a[i]);
}


 long long int  arrayToInt(int *A,int len)
{

    long long int length = len,m,i,r;
    char a_as_num[length][40];
    char string[30] = "\0";



    for (i = length-1; i >=0 ; i--) {
        sprintf(a_as_num[i], "%lld", A[i]);
        strcat(string, a_as_num[i]);
    }
    r = atoll(string);
    printf("\nValue of number is :%lld\n", r);

    	m=sqrt(r); // we can also use here pr/2 ,Based on compilation time we'll choose one.
	if(r==1)
	{
		printf("Wrong input");
		exit(1);
	}
	if(r==2 || r==3)
	{
	return r;
	}
	else{

	for(i=2;i<=m;i++)
	{
	 if(i>=100000){//  precision is upto 10^12 because sqrt of(10^12) or less will be six digits only
	   	break;
	   }
		if(r%i==0)
			{

				printf("\nWRONG INPUT\n");
			exit(1);}
}
	return r;
	}



}

