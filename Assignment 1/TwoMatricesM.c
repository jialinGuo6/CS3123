/******************************************************************************
    Program:      TwoMatricesM.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: January 20th, 2023
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
// function to get matrix elements randomly generated 0-99
void CreateMatrixE(int matrix[100][100], int row, int column) 
{
   printf("\nRandom elements \n");
   for (int i = 0; i < row; ++i) 
   {
      for (int j = 0; j < column; ++j) 
      {
         matrix[i][j]= rand()%100;
         printf("%d  ", matrix[i][j]);
      }
      printf("\n");
   }
}
// function to multiply two matrices
void multiplyMatrices(int first[100][100],int second[100][100],int result[100][100],int n) 
{  // Initializing elements of matrix mult to 0.
   for (int i = 0; i < n; ++i) 
   {
      for (int j = 0; j < n; ++j) 
      {
         result[i][j] = 0;
      }
   }
   // Create file pointer
   FILE *fpointer;
   fpointer = fopen("result.txt", "a");
   printf("\nResult Matrix:\n");
   fprintf(fpointer,"\n\n");
   // Multiplying first and second matrices and storing it in result.txt
   for (int i = 0; i < n; ++i) 
   {
      for (int j = 0; j < n; ++j) 
      {
         for (int k = 0; k < n; ++k) 
         {
            result[i][j] += first[i][k] * second[k][j];
         }
            printf("%7d  ", result[i][j]);
            fprintf(fpointer,"%7d ",result[i][j]); 
      }
      printf("\n");
      fprintf(fpointer,"\n");
   }
   fclose(fpointer);
}

int main() 
{
    int n;
    int first[100][100], second[100][100],result[100][100];
    printf("Enter the row dimension of the matrix: ");
    scanf("%d", &n);
    CreateMatrixE(first, n, n);
    CreateMatrixE(second, n, n);
    multiplyMatrices(first,second,result,n);
    return 0;
}
