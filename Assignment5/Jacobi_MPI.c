/******************************************************************************
    Program:      Jacobi_MPI.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: March 27th, 2023
*******************************************************************************/
//mpicc Jacobi_MPItest.c -o J1 ,  mpirun -np 16 ./J1
//for N = 496 timer: 5.0650ms 
#include <stdio.h>
#include <mpi.h>
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
    // solve linar equation Ax = b
    // mpi in a distribution memory 
    double a[N][N];
    double local_a[N/size_Of_Process][N];
    double b[N];
    double x_old[N];
    double local_x_old[N/size_Of_Process];

    double local_sum=0;
    int p=0;
    int start = process_Rank*N/size_Of_Process;
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
		       if(i==j){
		              a[i][j]=10;; //rand()%10+1
		       }else{
			      a[i][j]=1;//rand()%5+1;; //rand()%10+1
		       }
			//printf("a: %lf ", a[i][j]);
		}
		//printf("\n");
		b[i]= 10+i;
                x_old[i]= 0;
    	}
    }
    /* Send data of a&x_old from root(0) to all.*/
    MPI_Bcast(&b, N, MPI_DOUBLE,root,MPI_COMM_WORLD);  
    MPI_Bcast(&x_old, N, MPI_DOUBLE,root,MPI_COMM_WORLD);

    // scatter a to the local_a that each processor has one part.
    MPI_Scatter(&a, N*N/size_Of_Process, MPI_DOUBLE,&local_a, N*N/size_Of_Process, MPI_DOUBLE,root,MPI_COMM_WORLD);  

    // Gauss-Jacobi method calculate
    for(int lop=0;lop<20;lop++){  
        // p this is a location of each processor use to get new position of local_a and b.
        p = start;
        //printf("%d:%d\n",process_Rank,p);
        for(int j=0; j<N/size_Of_Process; j++)//row
        {
             local_sum=0;
             for(int k=0; k<N; k++)//col  
             {   
                    if(p != k)
                    {
             	            local_sum += local_a[j][k]*x_old[k];
                    }
             }
             local_x_old[j] = (b[p]- local_sum)/local_a[j][p];
             //printf("{%lf=%lf-%lf/ %lf}\n", local_x_old[j] ,b[p], local_sum,local_a[j][p] );
             // each processor local_a has same rows, so same self increment.
             p++;
        }
       /* printf("Iteration: %d \n", lop+1);
        for(int i=0; i<N/size_Of_Process; i++){
            //x_old[i]=local_x_old[i];   
            printf("%lf ", local_x_old[i]);
        }
        printf("\n");*/
 
        MPI_Barrier(MPI_COMM_WORLD); 
        // get new value local_x_old collect and save in x_old, send to all processors. Next iteration use again.
        MPI_Allgather(&local_x_old, N/size_Of_Process, MPI_DOUBLE,&x_old, N/size_Of_Process, MPI_DOUBLE,MPI_COMM_WORLD);
    }
    after = MPI_Wtime();
    MPI_Reduce(&before, &before, 1, MPI_DOUBLE, MPI_MIN, root, MPI_COMM_WORLD);
    MPI_Reduce(&after, &after, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
    MPI_Finalize();
    if(process_Rank == 0)
    {
      delta = after - before;
      printf("for N = %d timer: %.4fms \n", N, delta*1000);
    } 
    return 0;
}
