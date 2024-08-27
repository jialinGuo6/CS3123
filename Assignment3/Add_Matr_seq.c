/******************************************************************************
    Program:      Add_Matr_seq.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 20th, 2023
*******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
int main()
{
    clock_t start, difference;
    int N= 500;    
    double matrixA[N][N];
    double matrixB[N][N];
    double testSUM[N][N];
    printf("\nMatrix Size = %d\n",N);

    start = clock();
    //initialize all matrix
	for (int i = 0;i< N; ++i) 
	{
    		for (int j = 0; j < N; ++j) 
    		{
	   	     matrixA[i][j]= (10*(double)rand())/RAND_MAX;
	    	     matrixB[i][j]= (10*(double)rand())/RAND_MAX;
	    	     testSUM[i][j]=0;
    		}
	}   
	// Add two matix together    
	for (int i = 0; i < N; ++i) 
        {
     		for (int j = 0; j < N; ++j) 
    		{
   	        testSUM[i][j] = matrixA[i][j] + matrixB[i][j];
   	      
    		}
        }	
    difference= clock()-start;
    printf("Timer: %.4ld\n", difference);
//    printf("\n-----------------TEST AREA--------------------\n");
//    printf("A :==>\n");
//    for (int i = 0; i < N; ++i) 
//    {
//    	for (int j = 0; j < N; ++j) 
//        {
//   	        printf("%0.4f ",matrixA[i][j]);
//    	}
//    	printf("\n");
//    }
//    printf("B :==>\n");
//    for (int i = 0; i < N; ++i) 
//    {
//    	for (int j = 0; j < N; ++j) 
//    	{
//   	        printf("%0.4f ",matrixB[i][j]);
//    	}
//    	 printf("\n");
//    }	
//    printf("SUM :==>\n");
//    for (int i = 0; i < N; ++i) 
//    {
//     	for (int j = 0; j < N; ++j) 
//    	{
//   	        printf("%8.4f ",testSUM[i][j]);
//    	}
//    	 printf("\n");
//    }	  
    return 0;
}
