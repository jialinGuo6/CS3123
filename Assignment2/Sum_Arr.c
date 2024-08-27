/******************************************************************************
    Program:      Sum_Array.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 6th, 2023
*******************************************************************************/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv){
{
    int thread_id;
    clock_t start, difference;
    int N= 500;
    double A[N];
    double SUM;
    double Total=0;
    double testsum=0;
    printf("Array size = %d\n", N);
    start = clock();

    // This is my parallel machine
    // SUM the value of array A in each processors = 4;
    // Then get Total value from every processors.
    // * private: each processors has own private(thread_id,SUM)*
    #pragma omp parallel private(thread_id,SUM)
    {
              thread_id = omp_get_thread_num();
              int m =omp_get_num_threads();  

    //make each processors's own sum.           
              
              int start = thread_id*N/m;
              int end = (thread_id+1)*N/m;
              SUM =0;
              for(int i=start;i<end;i++)
              {
       	           A[i]=rand()%10+1;
              }
              for(int i=start;i<end;i++)
              { 
                   double x= A[i];
     	           SUM= SUM+ ((x/(x+1))*pow(-1,i));
     	         //  printf("A[%d],%0.1f idside sum %.4f\n",i,A[i], SUM);
              }   
   	     // printf("The sum of the array is %.4f\n", SUM);
   	     
   	     //Add all Sum together
   	      Total= SUM+Total;
   	      
    }
    // left the parallel machine
    // Print The Total (add each SUMs)
    printf("Total =%.4f\n", Total);
    difference=clock()-start;
    printf("Timer: %.4ld\n", difference);
    
    // Use common code to test the parallel answer
     printf("-----------------TEST AREA--------------------\n");
    for(int i=0;i<N;i++)
    {
        double testx= A[i];
     	testsum= testsum+ ((testx/(testx+1))*pow(-1,i));
    }
    printf("%.4f \n",testsum);
    
    return 0;
}
