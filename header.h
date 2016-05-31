#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define MAX 100
#define iteration 100
int max(int **,int,int);
double func_main(int **,int,int,int);
int count_of_unique(int **,int ,int);
int *unique_elements(int **,int,int,int);
int *class_count(int **,int *,int,int ,int);
int count_unique(int **,int,int,int);
int ***statistics(int *,int,int **,int,int);
double bayes_test(int ***,int *,int,int,int,int **,int **,int);
int compare(int *,int,int);
int max_class(double *,int);

