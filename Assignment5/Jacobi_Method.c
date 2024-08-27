/******************************************************************************
 Gauss-Jacobi method use iteration
/******************************************************************************
    Program:      Jacobi_Method.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: XXXXX, 2023
*******************************************************************************/

#include <stdio.h>

int main()
{   int N=4;
    double a[4][4] = {{18,7,3,2}, {3,16,1,5}, {4,3,10,2}, {5,2,3,14}};
    double b[4] = {57,43,53,60};
    double x[4] = {0,0,0,0};
    double x2[4] = {0,0,0,0};

    for(int i=0; i<20; i++){
        
        for(int j=0; j<4; j++){//row
            for(int k=0; k<4; k++){ //col
              if(j!=k)
              {
                  x[j]+=(-1)*( a[j][k]/a[j][j] )* x2[k] ;
              }
            }
            x[j] += b[j]/a[j][j];
        }
       
        printf("Iteration: %d \n", i+1);
        for(int i=0; i<4; i++){
            x2[i]=x[i];
            x[i] =0;  
            printf("%lf ", x2[i]);
        }
        printf("\n");
       
    }
    printf("Hello World");

    return 0;
}
