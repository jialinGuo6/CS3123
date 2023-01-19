/******************************************************************************
    Program:      sumOfS.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: January 20th, 2023
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matrix[100][100];
    double total = 0, cSumS=0, uncSumS=0;
    double average; 
    int row;
    int column;
    FILE *fpointer;
    fpointer = fopen("data3.txt", "r");
    fscanf(fpointer, "%d", &row);
    printf("row = column = %d \n", row);
    column = row;
    double num;
    num= row * column;
    for (int i = 0; i < row; ++i) 
    {
      for (int j = 0; j < column; ++j) 
      {
         fscanf(fpointer, "%d", &matrix[i][j]);
         total = total + matrix[i][j];
      }
      average= total/num;
    }
    printf("\nsum of all elements: %f \naverage of all elements: %f \n", total,average);
    for (int i = 0; i < row; ++i) 
    {
      for (int j = 0; j < column; ++j) 
      {
         cSumS = cSumS + (matrix[i][j]-average)*(matrix[i][j]-average);
         uncSumS= uncSumS + (matrix[i][j])*(matrix[i][j]);
      }
    }
    printf("corrected sum of squares: %f  \nuncorrected of squares: %f \n ", cSumS,uncSumS);
    return 0;
}
