/******************************************************************************
    Program:      SumOfMatrix.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 6th, 2023
*******************************************************************************/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
int main()
{   
// // max[][] size 835, then try otherway 
    int thread_id;
    clock_t start, difference,insideStart,insideDifference;
    int N= 8;    
    double **matrixA;  
    double **matrixB;
    double **SUM;
 //   double  **testSUM;
    printf("\nMatrix Size = %d\n",N);
    start = clock();
    // This is my parallel machine                                        
    // SUM the value of array A in each processors = 4;
    // SUM lines divide as N/m parts;(eg:(8/4) P1:1,2 lines, P2:3,4 l,P3:5,6 l,P4:7,8 l).       
    #pragma omp parallel private(thread_id)
    {
              int m =omp_get_num_threads();
 	      thread_id = omp_get_thread_num();

 	      int start = thread_id*N/m;
 	      int end =   (thread_id+1)*N/m;
 	      // get a matrix to each proceesor
 	      matrixA = (double**) malloc(sizeof(double*)*(N/m));  // line
 	      matrixB = (double**) malloc(sizeof(double*)*(N/m));  // line
 	      SUM = (double**) malloc(sizeof(double*)*(N/m));      // line
 	    //  testSUM = (double**) malloc(sizeof(double*)*(N/m));      // line
 	      
 	      for (int i = start;i< end; ++i) 
 	       {  matrixA[i] = (double*) malloc(sizeof(double)*N);   // col
 	          matrixB[i] = (double*) malloc(sizeof(double)*N);   // col
 	          SUM[i] = (double*) malloc(sizeof(double)*N);       // col
 	        //  testSUM[i] = (int*) malloc(sizeof(int)*N);   // col
 	       }  
 	       
	     //initialize all matrix
	    for (int i = start;i< end; ++i) 
	    {
	    	for (int j = 0; j < N; ++j) 
	    	{
		        matrixA[i][j]= (10*(double)rand())/RAND_MAX;
		        matrixB[i][j]= (10*(double)rand())/RAND_MAX;
		        SUM[i][j]=0;
		 //     testSUM[i][j]=0;
	    	}
	    }   
 	   
 	    // add matrixA + matrixB in the matrix SUM
           for (int i = start;i< end; ++i)
           {     
	    	for (int j = 0; j < N; ++j) 
	    	{
	    		SUM[i][j] = matrixA[i][j] + matrixB[i][j];
	    	}
	    	
           }
       //the output of each part of processors;
           printf("partily SUM lines by lines:==> processor #%d\n", thread_id);
           for (int i = start;i< end; ++i) 
          {
           	for (int j = 0; j < N; ++j) 
          	{
           		printf("%0.4lf ", SUM[i][j]);
           	}
              printf("\n");
           }
    }    
    // left the parallel machine
    
    difference= clock()-start;
    printf("Timer: %.4ld\n", difference);
    
  
  // Test and comment it. 
  // When finish test becuase it has some part in parallel(spend time).
  // Or give to much print
  //     //Show all the SUM that add from parallel
  //  for (int i = 0;i< N; ++i) 
  //  {
  //  	for (int j = 0; j < N; ++j) 
  //  	{
  //  		printf("%2d ", SUM[i][j]);
  //  	}
  //  	printf("\n");
  //  }
    
  // printf("\n-----------------TEST AREA--------------------\n");
  //  printf(" A :==>\n");
  //  for (int i = 0; i < N; ++i) 
  //  {
  //  	for (int j = 0; j < N; ++j) 
  //  	{
  //	        printf("%2d ",matrixA[i][j]);
  //  	}
  //  	 printf("\n");
  //  }
  //   printf(" B :==>\n");
  //  for (int i = 0; i < N; ++i) 
  //  {
  //  	for (int j = 0; j < N; ++j) 
  // 	{
  //	        printf("%2d ",matrixB[i][j]);
  //  	}
  //  	 printf("\n");
  //  }	
  //   printf(" SUM :==>\n");
  //  for (int i = 0; i < N; ++i) 
  //  {
  //  	for (int j = 0; j < N; ++j) 
  // 	{
  //	        testSUM[i][j] = matrixA[i][j] + matrixB[i][j];
  //	        printf("%2d ",testSUM[i][j]);
  //  	}
  //  	 printf("\n");
  //  }	
    return 0;
}
