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

int main()
{
    int thread_id;
    clock_t start, difference,insideStart,insideDifference;
    int N= 8;    //max size? of N is 835
    int matrixA[N][N];
    int matrixB[N][N];
    int SUM[N][N];
//  int testSUM[N][N];
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
	     //initialize matrix
	    for (int i = start;i< end; ++i) 
	    {
	    	for (int j = 0; j < N; ++j) 
	    	{
		        matrixA[i][j]= rand()%10+1;
		        matrixB[i][j]= rand()%10+1;
		        SUM[i][j]=0;
		 //     testSUM[i][j]=0;
	    	}
	    }   
 	   
 	      
           for (int i = start;i< end; ++i)
           {     
	    	for (int j = 0; j < N; ++j) 
	    	{
	    		SUM[i][j] = matrixA[i][j] + matrixB[i][j];
	    	}
	    	
           }
      // the output of each part of processors;
      //     printf("partily SUM lines by lines:==> processor #%d\n", thread_id);
      //     for (int i = start;i< end; ++i) 
      //     {
      //     	for (int j = 0; j < N; ++j) 
      //     	{
      //     		printf("%2d ", SUM[i][j]);
      //     	}
      //        printf("\n");
      //     }
    }    
    // left the parallel machine
    difference= clock()-start;
    printf("Timer: %.4ld\n", difference);
    
     //Show all the SUM that add from parallel
    for (int i = 0;i< N; ++i) 
    {
    	for (int j = 0; j < N; ++j) 
    	{
    		printf("%2d ", SUM[i][j]);
    	}
    	printf("\n");
    }
  
  // Test area and comment it. 
  // When finish test becuase it has some part in parallel(spend time).
  // printf(""\n-----------------TEST AREA--------------------\n");
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
