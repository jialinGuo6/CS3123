/******************************************************************************
    Program:      Frequence_Arr.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: February 20th, 2023
*******************************************************************************/
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv){
    clock_t start, difference;
    int N = 500;
    int A[N];
    int NumRange[]={1,2,3,4,5,6,7,8,9,10};
    int freq[10];
    int count=0;
    start = clock();
    for(int j=0;j<10;j++)
    {
        freq[j]=0;
    }
    for(int i=0;i< N ;i++)
    {
 	 A[i]=rand()%10+1;
    }

    for(int index = 0; index< 10;index++)
    { //0-9
        count =0;
        for (int j = 0; j < N; j++)
	{
	    if(A[j] == NumRange[index])
            {    
		count++;
		freq[index]=count;
            } 
		 
 	} 
     }
    count =0;
    printf("The Frequence Table with N = %d\n",N);
    printf("-----------------------------------\n");
    for (int i=0;i<10;i++)
    {  count = count+ freq[i];    
	   printf("| %3d occurs| %6d times        |\n", i+1, freq[i]);
	   printf("-----------------------------------\n");
    }
    difference=clock()-start;
    printf("Timer: %.4ld\n", difference);
    printf("Total = %d\n",count);
    return 0;
}
