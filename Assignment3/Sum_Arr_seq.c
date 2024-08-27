/*********************************************************
    Program:      Sum_Arr_seq.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 20th, 2023
*********************************************************/
#include <stdio.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv)
{
    clock_t start, difference;
    int N= 100000;
    double A[N];
    double testsum=0;
    printf("Array size = %d\n", N);
    start = clock();

// initialize the array A
    for(int i=0;i<N;i++)
    {
       A[i]=rand()%10+1;
    }
// SUM the value of array A
    for(int i=0;i<N;i++)
    {
        double testx= A[i];
     	testsum= testsum+ ((testx/(testx+1))*pow(-1,i));
    }
    difference=clock()-start;
    printf("Timer: %.4ld\n", difference);
    
    printf("%.4f \n",testsum);
    
    return 0;
}
