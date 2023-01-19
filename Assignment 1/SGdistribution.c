/******************************************************************************
    Program:      SGdistribution.c
    Course:       CS 3123 Winter 2023 UNB Saint John
    by:           Jialin Guo(3687827)
    Program Date: January 18th, 2023
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PAI 3.14159265358979
//The Standard Gaussian distribution Function
double f(double x) 
{
     double result= ( 1/(sqrt(2*PAI)) )*exp(-(x*x)/2);
     return result;
}
//using a Riemann sum to get area from -infinity to x(A)
double areaCalculate(double x,double area,int n)
{
    double h,a,b, endX;
    area = 0;
    endX = -10.00;
    if(x<0)
    {
       h = (10.00 + x)/n;
       printf("Divide as %d blocks, then distance(h)= %f",n,h);
    }else if(x>=0)
    {
       h = (10.00 + x)/n;  
       printf("Divide as %d blocks, then distance(h)= %f",n,h);
    }
    printf("\n");
    //Trapezoid Area Formula = (a+b)/2 x h
    for(int i = 0; i < n; ++i)
    {
        a = f(endX);
        endX = endX + h;
        b = f(endX);
        area = area + (((a+b)*h)/2);
    }
    printf("Area(P) = %0.10f\n",area);
}
int main()
{
    double result1,result2,result3,area;
    result1 = f(0.00);
    result2 = f(-1.00);
    result3 = f(3.00);
    int n = 100000000;
    // f(x) range is (-infinity to A), assume -infinity can be replaced by -10
    printf("A = 0.00,  f(A)=%0.10f,\nA = -1.00, f(A)=%0.10f,\nA = 3.00,  f(A)=%0.10f\n", result1,result2,result3);
    // Therefore calculate the are from x= -10 to x(0.00,-1.00,3.00)
    printf("\nWhen A = 0.00\n");
    areaCalculate(0.00,area,n); 
    printf("\nWhen A = -1.00\n");
    areaCalculate(-1.00,area,n); 
    printf("\nWhen A = -3.00\n");
    areaCalculate(-3.00,area,n); 
    return 0;
}