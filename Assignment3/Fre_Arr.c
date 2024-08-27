/******************************************************************************
    Program:      Frequence_Arr.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 20th, 2023
*******************************************************************************/
#include <stdio.h>
#include <omp.h>
#include <time.h>
#define NUM_THREADS 2
// use four threads ==> export OMP_NUM_THREADS=4
int main(int argc, char** argv){
    clock_t start, difference,insideStart,insideDifference;
    int thread_id;
    int N = 10000;
    int A[N];
    int NumRange[]={1,2,3,4,5,6,7,8,9,10};
    int freq[10];
    int count=0,testcount=0;
    omp_set_num_threads(NUM_THREADS);  
    start = clock();
    // this next line activtes the parallel machine
    // and all processes run all the code in this machine
    // and each shared all cariables unless private variables
    #pragma omp parallel
    {
        //initialize the array freq & A
        #pragma omp for
        for(int j=0;j<10;j++)
        {
            freq[j]=0;
        } 
        #pragma omp for
        for(int i=0;i< N ;i++)
 	{
 	    A[i]=rand()%10+1;
 	}
    // make space to keep to each processors counts on, and save the count values.
        // each processor counts it section of the array
        #pragma omp for firstprivate(count)
    	for(int index = 0; index< 10;index++).  //0-9 numbers
 	{ 
 	      	 count =0;
		 for (int j = 0; j < N; j++)
		 {
		      if(A[j] == NumRange[index])
		      {    
		           count++;
		      } 
                      freq[index]=count;
		 }  
	    // printf(" %ds is %d == %d ?\n",index+1 ,count, freq[index]);
 	 } 
    }
    // left the parallel machine
    difference=clock()-start;
    printf("\nTimer: %.4ld\n", difference);
    // print the frequence_table.
    printf("The Frequence Table with N = %d\n",N);
    printf("\n");
    for (int i=0;i<10;i++)
    {     printf("--------------------------------------\n");
	   	printf(" %5d  ",freq[i]);
	   	testcount = testcount+freq[i];
	   printf("| %2d occurs| %5d times     |\n", i+1, freq[i]);
    }
    printf("--------------------------------------\n");
    printf("count how many items in the frequency table = %d\n" , testcount);

    return 0;
}
