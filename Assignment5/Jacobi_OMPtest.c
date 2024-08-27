/******************************************************************************
    Program:      Jacobi_OMP.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: March 27th, 2023
*******************************************************************************/
// gcc -fopenmp Jacobi_OMPtest.c -o J2   , ./J2 
// for N = 496 Timer: 
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#define N 496
#define NUM_THREADS 16

int main(int argc, char** argv)
{ 
    clock_t before, difference;
    omp_set_num_threads(NUM_THREADS);
    int thread_id;
    double a[N][N];
    double b[N];
    double x_old[N];
    double x_new[N];
    double local_sum=0;
    before = clock();

    // This is my omp parallel
    // solve linar equation Ax = b
    // omp work on a shared memory, so processors share a, b, x_old, x_new.
    #pragma omp parallel
    {     
      //initialize matrix and array.
      #pragma omp for
      for (int i = 0;i< N; ++i) 
      {
            for (int j = 0; j < N; ++j) 
            {
                 if(i==j){
             	        a[i][j]=10;
                 }else{
             	        a[i][j]=1;
                 }
            }
            b[i]= 10+i;
            x_old[i]= 0;
      }  
      // Gauss-Jacobi method calculate
      for(int lop=0;lop<10;lop++)
      { 
        #pragma omp for reduction(+:local_sum)
        for(int j= 0; j< N; j++)//row
        {
            local_sum=0;
            for(int k=0; k<N; k++)//col  
            {   
                 if(j != k)
                 {
             	        local_sum += a[j][k]*x_old[k];
              	        // printf("==>%lf=%lf:%lf\n",local_sum,a[j][k],x_old[k]);
                  }
            }
              x_new[j] = (b[j]- local_sum)/a[j][j];
              //printf("x_old[%d] ==> %lf = %lf - %lf/ %lf\n", j,x_new[j],b[j],local_sum,a[j][j]);
        }
        #pragma omp barrier
        // calculate x_new value send to x_old use next iteration again.
        #pragma omp for
         for(int i=0; i<N; i++)
         {    
              x_old[i] = x_new[i];
             // printf("%lf ", x_new[i]);
         }
        /* printf("\n");  */
      }   
       
    }
    // left the parallel machine
    difference= clock()-before;
    printf("for N = %d Timer: %ld\n",N, difference);
    return 0;
}
