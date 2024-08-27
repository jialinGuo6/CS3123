/***********************************************************************
    Program:      Sum_Arr_usefor.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 20th, 2023
************************************************************************/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#define NUM_THREADS 4
int main(int argc, char** argv)
{
    clock_t start, difference;
    int N= 100000;
    double A[N];
    double SUM=0;
    double testsum=0;
    printf("Array size = %d\n", N);
    omp_set_num_threads(NUM_THREADS);  
    start = clock();

    // This is my parallel machine
    // SUM the value of array A
    #pragma omp parallel
    {
        // initialize the array A
        #pragma omp for
    	for(int i=0;i<N;i++)
    	{
    	    A[i]=rand()%10+1;
   	 }
        // try for in this file
        #pragma omp for firstprivate(sum)
    	for(int i=0;i<N;i++)
    	{ 
     		SUM= SUM+ ((A[i]/(A[i]+1))*pow(-1,i));
    	}   
    }
    // left the parallel machine
    // Print The SUM
    // printf("The sum of the array is %.4f\n", SUM);
    difference=clock()-start;
    printf("Timer: %.4ld\n", difference);
    
    // Use common code to test the parallel answer
     printf("-----------------TEST AREA--------------------\n");
    for(int i=0;i<N;i++)
    {
     	  testsum= testsum+ ((A[i]/(A[i]+1))*pow(-1,i));
    }
    printf("%.4f \n",testsum);
    
    return 0;
}
