/******************************************************************************
    Program:      Mult_matrix1.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: March 27th, 2023
*******************************************************************************/
// mpicc Mult_matrix1.c -o M1 , mpirun -np 16 ./M1
// for N = 496 timer: 102.1628ms 

#include <stdio.h>
#include <mpi.h>
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
    // MatrixA Scatter ==> Local_MatrixA, MatrixB Bcast, Local_matrixC_MatrixC MatrixC
    // Prepare sub Local_MatrixA to save the split parts 
    // Prepare sub Local_matrixC save the sub result from each processor and gather to the total result matrixC 

    int MatrixA[N][N];
    int Local_MatrixA[N/size_Of_Process][N];

    int MatrixB[N][N];

    int Local_matrixC[N/size_Of_Process][N];
    int MatrixC[N][N];

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
			MatrixA[i][j]= rand()%10; //0-9 ; 1-10 rand()%10+1
			MatrixB[i][j]= rand()%10;
			MatrixC[i][j]= 0;
		}
    	} 
    }
    // Bcast MatrixB send to all processors
    MPI_Bcast(&MatrixB, N*N, MPI_INT,root,MPI_COMM_WORLD);

    // split MatrixA, each processor has their own local part.
    MPI_Scatter(&MatrixA,(N*(N/size_Of_Process)), MPI_INT, &Local_MatrixA,(N*(N/size_Of_Process)), MPI_INT, root, MPI_COMM_WORLD);

    /*	printf("\np=%d: Local_MatrixA \n", process_Rank);
	for(int i=0;i<N/size_Of_Process;i++)
	{
	  for (int j = 0; j < N; ++j) 
	  {
		printf("%d ", Local_MatrixA[i][j]);
	  }
	  printf("\n");
	}*/               
    
    // multiple Local_matrixC
    for(int i=0;i< N/size_Of_Process; i++) //row
    { 
	for (int j = 0; j < N; j++) //col_1
	{      
		Local_matrixC[i][j]=0; 
     		for (int k = 0; k < N; k++) //col_2
	       {
                      Local_matrixC[i][j] +=  Local_MatrixA[i][k] * MatrixB[k][j];     
               }
	}
    }

   /*	printf("\np=%d: Local_matrixC \n", process_Rank);
	for(int i=0;i<N/size_Of_Process;i++)
	{
		for (int j = 0; j < N; ++j) 
		{
		printf("%d ", Local_matrixC[i][j]);
		}
		printf("\n");
	}*/    

    //collect the local result for MatrixC
    MPI_Gather(&Local_matrixC,N*(N/size_Of_Process), MPI_INT, &MatrixC,N*(N/size_Of_Process), MPI_INT, root, MPI_COMM_WORLD);
    after = MPI_Wtime();     
    MPI_Finalize();
     if(process_Rank == root)
     {     
           delta = after - before;
           printf("for N = %d timer: %.4fms \n", N, delta*1000);
    	/*  printf("\nMatrixA \n");
    	  for(int i=0;i<N;i++)
    	  {
    	 	 for (int j = 0; j < N; ++j) 
    	 	 {
    	 	 	printf("%d ",MatrixA[i][j]);
    	 	 }
    	         printf("\n");
    	  }  
    	  printf("\nMatrixB \n");
    	  for(int i=0;i<N;i++)
    	  {
    	 	 for (int j = 0; j < N; ++j) 
    	 	 {
    	 	 	printf("%d ",MatrixB[i][j]);
    	 	 }
    	         printf("\n");
    	  }  
    	  printf("\nTranspose print MatrixC \n");
    	  for(int i=0;i<N;i++)
    	  {
    	 	 for (int j = 0; j < N; ++j) 
    	 	 {
    	 	 	printf("%3d ",MatrixC[i][j]);
    	 	 }
    	         printf("\n");
    	  }   */                            
     }

    return 0;
}
