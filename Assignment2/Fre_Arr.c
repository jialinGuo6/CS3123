/******************************************************************************
    Program:      Frequence_Arr.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 6th, 2023
*******************************************************************************/
#include <stdio.h>
#include <omp.h>
#include <time.h>
// use four threads ==> export OMP_NUM_THREADS=4
int main(int argc, char** argv){
    clock_t start, difference,insideStart,insideDifference;
    int thread_id;
    int N = 500;
    int A[N];
    int NumRange[]={1,2,3,4,5,6,7,8,9,10};
    int a[4][10];
    int count;
    int sum;
   // int** thread;
    start = clock();
    for(int j=0;j<10;j++)
    {
        for(int i=0;i<4;i++)
        {
            a[i][j]=0;
        }
    }
    // this next line activtes the parallel machine
    // and all processes run all the code in this machine
    // and each shared all cariables unless private variables
    #pragma omp parallel private(thread_id,count)
    { 
              int m =omp_get_num_threads();
 	      thread_id = omp_get_thread_num();
 	      int start = thread_id*N/m;
 	      int end =   (thread_id+1)*N/m;
           //initialize the array A
           for(int i=start;i< end ;i++)
 	   {
 	              A[i]=rand()%10+1;
 	   }
    // make space to keep to each processors counts on, and save the count values.
 	    //thread = (int) malloc(sizeof(int)*m);
 	      int thread[m][10];

           for(int j=0;j<10;j++)
           {
                 for(int i=0;i<m;i++)
                 {
                    thread[i][j]=0;
                 }
           }
           // each processor counts it section of the array
           for(int index = 0; index<10;index++)
 	   { //0-9
 	      	 count =0;
		 for (int j = start; j < end; j++)
		 {
		      if(A[j] == NumRange[index])
		     {    
		       count++;
		       a[thread_id][index]=count;
		       thread[thread_id][index] = count;
		     } 
		 }  
	     // printf(" %ds is %d == %d ?\n",index+1 ,count,thread[thread_id][index]);
 	   } 
     }
    // left the parallel machine
    printf("The Frequence Table with N = %d\n",N);
    printf("--------------------------------------------------------\n");
    for (int i=0;i<10;i++)
    {      sum=0;
	   for(int j=0;j<4;j++){
	   	printf(" %3d  ",a[j][i]);
	   	sum=sum+a[j][i];
	   }
	   printf("| %3d occurs| %6d times     |\n", i+1, sum);
	   printf("--------------------------------------------------------\n");
    }
    difference=clock()-start;
    printf("Timer: %.4ld\n", difference);
    return 0;
}
