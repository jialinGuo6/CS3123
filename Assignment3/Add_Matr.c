/******************************************************************************
    Program:      Add_Matrix.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 20th, 2023
*******************************************************************************/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define NUM_THREADS 2
int main()
{
    clock_t start, difference;
    int N= 500;    //(int)max size 835 , double
    double matrixA[N][N];
    double matrixB[N][N];
    double SUM[N][N];
//    double testSUM[N][N];
    omp_set_num_threads(NUM_THREADS);  
    printf("\nMatrix Size = %d\n",N);
    start = clock();
    // This is my parallel machine                                        
    // SUM the value of array A and set processors = 4;
    // SUM lines divide as N/m parts;(eg:(8/4) P1:1,2 lines, P2:3,4 l,P3:5,6 l,P4:7,8 l).  
    #pragma omp parallel
    {
            //initialize all matrix
            #pragma omp for
	    for (int i = 0;i< N; ++i) 
	    {
	    	for (int j = 0; j < N; ++j) 
	    	{
		        matrixA[i][j]= (10*(double)rand())/RAND_MAX;
		        matrixB[i][j]= (10*(double)rand())/RAND_MAX;
		        SUM[i][j]=0;
//		        testSUM[i][j]=0;
	    	}
	    }   
 	   
 	   // add matrixA + matrixB in the matrix SUM
           #pragma omp for reduction(+:SUM)
           for (int i = 0;i< N; ++i)
           {     
	    	for (int j = 0; j < N; ++j) 
	    	{
	    		SUM[i][j] = matrixA[i][j] + matrixB[i][j];
	    	}
	    	
           }
    }
    // left the parallel machine
    difference= clock()-start;
    printf("Timer: %.4ld\n", difference);
    
  // Test and comment it. 
  // When finish test becuase it has some part in parallel(spend time).
  // Or give to much print
  //     //Show all the SUM that add from parallel
  //printf("SUM =======\n");
  //  for (int i = 0;i< N; ++i) 
  //  {
  //  	for (int j = 0; j < N; ++j) 
  //  	{
  //  		printf("%0.4f ", SUM[i][j]);
  //  	}
  // 	printf("\n");
  //  }
    
  // printf("\n-----------------TEST AREA--------------------\n");
  // printf(" A :==>\n");
  // for (int i = 0; i < N; ++i) 
  //  {
  //	for (int j = 0; j < N; ++j) 
  //  	{
  //	        printf("%0.4f ",matrixA[i][j]);
  // }
  //  	 printf("\n");
  //  }
  //  printf(" B :==>\n");
  //  for (int i = 0; i < N; ++i) 
  //  {
  //  	for (int j = 0; j < N; ++j) 
  // 	{
  //	        printf("%0.4f ",matrixB[i][j]);
  // 	}
  //  	 printf("\n");
  //  }	
  //   printf(" SUM :==>\n");
  //  for (int i = 0; i < N; ++i) 
  //  {
  //  	for (int j = 0; j < N; ++j) 
  // 	{
  //	        testSUM[i][j] = matrixA[i][j] + matrixB[i][j];
  //	        printf("%0.4f ",testSUM[i][j]);
  // 	}
  // 	 printf("\n");
  //  }	
    return 0;
}
