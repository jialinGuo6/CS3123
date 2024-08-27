/******************************************************************************
    Program:      Mult_matrix2.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: March 27th, 2023
*******************************************************************************/
// mpicc Mult_matrix2.c -o M2,mpirun -np 16 ./M2
//for N = 496 timer: 77.6551ms 

#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define N 496
int main(int argc, char** argv)
{
    // Prepare mpi parameters 
    int root =0;
    int process_Rank, size_Of_Process;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    // Divide subarray dynamic base on processor #.
    int MatrixA[N][N];
    int Local_MatrixA[N/size_Of_Process][N];

    int MatrixB[N][N];
    int Local_MatrixB[N/size_Of_Process][N];

    int MatrixC[N][N];
    int Local_matrixC[N/size_Of_Process][N];    
    int local_sum=0;
    
    double before, after, delta;
    before = MPI_Wtime();
    // This is MPI area.
    // initialize in the root;
    if(process_Rank == root)
    {      
	for(int i=0;i<N;i++)
	{
		for (int j = 0; j < N; ++j) 
		{
			MatrixA[i][j]= i+1;
			MatrixB[j][i]= i+1;
			MatrixC[i][j]= 0;
		}
    	} 

	for(int i=0;i<N/size_Of_Process;i++)
	{
		for (int j = 0; j < N; ++j) 
		{
			Local_matrixC[i][j]= 0;
		}
    	} 

    }

    // Bcast Local_matrixC initialize in all processors. 
    // Make Local_matrixC is 0, if not initialize some value will has a long incorrect int value.
    MPI_Bcast(&Local_matrixC, N*N/size_Of_Process, MPI_INT,root,MPI_COMM_WORLD);


    // split MatrixA and MatrixB, each processor has their own local part.
    MPI_Scatter(&MatrixA,N*N/size_Of_Process, MPI_INT, &Local_MatrixA,N*N/size_Of_Process, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Scatter(&MatrixB,N*N/size_Of_Process, MPI_INT, &Local_MatrixB,N*N/size_Of_Process, MPI_INT, root, MPI_COMM_WORLD);
/* 
	printf("\np=%d: MatrixA \n", process_Rank);
           for(int i=0;i<N/size_Of_Process;i++)
          {
           	  for (int j = 0; j < N; ++j) 
          	  {
            		printf("%d ", Local_MatrixA[i][j]);
           	  }
          	  printf("\n");
           }   
 

	printf("\np=%d: MatrixB \n", process_Rank);
           for(int i=0;i<N/size_Of_Process;i++)
          {
           	  for (int j = 0; j < N; ++j) 
          	  {
            		printf("%d ", Local_MatrixB[i][j]);
           	  }
          	  printf("\n");
           }   */

    MPI_Barrier(MPI_COMM_WORLD);
    // multiple Local_matrixC
    for(int i=0;i< N/size_Of_Process; i++) //row
    { 
	for (int j = 0; j < N; j++) //col_1
	{      
     		for (int k = 0; k < N; k++) //col_2
		{
               		Local_matrixC[i][j] +=  Local_MatrixA[i][k] * Local_MatrixB[i][k];
                }
	}
    }
	printf("\np=%d: MatrixC \n", process_Rank);
           for(int i=0;i<N/size_Of_Process;i++)
          {
           	  for (int j = 0; j < N; ++j) 
          	  {
            		printf("%d ", Local_matrixC[i][j]);
           	  }
          	  printf("\n");
           }   
    // collect the local result for MatrixC
    MPI_Gather(& Local_matrixC,N*N/size_Of_Process,MPI_INT,&MatrixC,N*N/size_Of_Process,MPI_INT,root,MPI_COMM_WORLD);
    after = MPI_Wtime();     
    MPI_Finalize();
    if(process_Rank == root)
    {   
	delta = after - before;
	printf("for N = %d timer: %.4fms \n", N, delta*1000);   
    /*	printf("\nMatrixA \n");
    	  for(int i=0;i<N;i++)
    	  {
    	 	 for (int j = 0; j < N; ++j) 
    	 	 {
    	 	 	printf("%d ",MatrixA[i][j]);
    	 	 }
    	         printf("\n");
    	  }  
    	  printf("\nMatrixB^T \n");
    	  for(int i=0;i<N;i++)
    	  {
    	 	 for (int j = 0; j < N; ++j) 
    	 	 {
    	 	 	printf("%d ",MatrixB[i][j]);
    	 	 }
    	         printf("\n");
    	  }  
    	  printf("\nMatrixC \n");
    	  for(int i=0;i<N;i++)
    	  {
    	 	 for (int j = 0; j < N; ++j) 
    	 	 {
    	 	 	printf("%3d ",MatrixC[j][i]);
    	 	 }
    	         printf("\n");
    	  }*/                               
    }

    return 0;
}
