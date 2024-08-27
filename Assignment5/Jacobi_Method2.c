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
    double a[4][4] = {{10,1,1,1}, {1,10,1,1}, {1,1,10,1}, {1,1,1,10}};
    double b[4] = {13,13,13,13};
    double x[4] = {0.4,0.5,0.6,0.7};
    double x2[4] = {0,0,0,0};
    double sum=0;
    for(int i=0; i<3; i++){
  
        for(int j=0; j<4; j++){//row
            sum=0;
            for(int k=0; k<4; k++){ //col
               if(j!=k)
               {
             	 sum += a[j][k]*x[k];
              	//  x[j]+=(-1)*( a[j][k]/a[j][j] )* x2[k] ;
              	}
            }
             x2[j] = (b[j]- sum)/a[j][j];
        }
       
        printf("Iteration: %d \n", i+1);
        for(int i=0; i<4; i++){
             printf("%lf ", x2[i]);
             x[i]=0;
        }
        printf("\n");
    }
    printf("Hello World");

    return 0;
}
