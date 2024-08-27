/******************************************************************************
    Program:      pie.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: March 27th, 2023
*******************************************************************************/
//mpicc pie.c -o P1,  mpirun -np 16 ./P1
//for N = 1000000000 timer: 38148.9211ms  
//AVG_pie = 3.141579

#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char** argv)
{ 
    double before, after, delta;
    // Prepare mpi parameters 
    int root =0;
    int process_Rank, size_Of_Process;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);
    int N= 1000000000;
    double X=0,Y=0,local_count=0, count=0, Pie,Total_pie; 
    before = MPI_Wtime();

    // 16 processors with 1 billion numbers per processor
    // a unit x=|1|=1, y=|-1|=1
    // x^2+y^2 <= 1, count++ as in circle count points.
    srand(process_Rank+1);
   for(int i;i<N;i++)
    {
  	  X = 2.0*(double)rand() / RAND_MAX -1.0;
   	  Y = 2.0*(double)rand() / RAND_MAX -1.0;
   	  //printf("Random number: %f,%f\n", X,Y);
          if( (X*X)+(Y*Y) <= 1)
              local_count++;
    }
    // calulate local pie, (in circle points / total generation points)*4  
    Pie = local_count/N *4;
    //printf("pie=%f\n", Pie);
    // Get sum total pie
    MPI_Reduce(&Pie,&Total_pie,1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);
    after = MPI_Wtime();
    MPI_Reduce(&before, &before, 1, MPI_DOUBLE, MPI_MIN, root, MPI_COMM_WORLD);
    MPI_Reduce(&after, &after, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
    
    MPI_Finalize();
    if(process_Rank == root)
    {
          delta = after - before;
          printf("for N = %d timer: %.4fms \n", N, delta*1000);
          // total_pie/16 for average of each processor.
          Total_pie = Total_pie/size_Of_Process;
          printf("AVG_pie = %f\n", Total_pie);
    }
    return 0;
}
