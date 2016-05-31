#include"header.h"
double func_main(int **parse,int row,int col,int index)
{
    srand(index);
    int i,j,r,row_train=0,row_test=0,class_size,*count_of_class,*class,***matrix;
    double err=0.0;
    int tr_row;
    int *array;
    array=(int*)malloc(sizeof(int)*MAX);
    int **train_set,**test_set;
    train_set=(int **)malloc(sizeof(int*)*MAX);
    for(i = 0; i < MAX; i++) 
       train_set[i] = (int*)malloc(sizeof(int)*MAX);
    test_set=(int **)malloc(sizeof(int*)*MAX);
    for(i = 0; i < MAX; i++) 
        test_set[i] = (int*)malloc(sizeof(int)*MAX);	
    tr_row=(int)(0.7*(double)row);
    int ran;
    //srand(index);
    array[1]=rand()%row;
    for(i=2;i<=row;i++) {
        ran=rand()%row;
        for(j=1;j<i;j++) {
            if(ran==array[j]) {
                i--;
                break;
            }
        }
        if(j>=i)
        array[i]=ran;
    }
    for(i=0;i<row;i++) {
	r=array[i+1];
        for(j=0;j<col;j++) {
		train_set[row_train][j]=parse[r][j];
	}
	row_train++;
    }
    for(i=tr_row;i<row;i++) {
	for(j=0;j<col;j++) {
		test_set[row_test][j]=train_set[i][j];
	}
	row_test++;
    }
    /*printf("training set\n");
    for(i=0;i<tr_row;i++) {
        for(j=0;j<col;j++) {
	    printf("%d  ",train_set[i][j]);
	}
        printf("\n");
    }
    printf("test set\n");
    for(i=0;i<row_test;i++) {
        for(j=0;j<col;j++) {
	    printf("%d  ",test_set[i][j]);
	}
        printf("\n");
    }*/
    class_size=count_of_unique(train_set,tr_row,col-1);
    class=unique_elements(train_set,tr_row,col-1,class_size);
    count_of_class=class_count(train_set,class,tr_row,col,class_size);
    matrix=statistics(class,class_size,train_set,tr_row,col);
    err=bayes_test(matrix,count_of_class,tr_row,col,class_size,train_set,test_set,row_test);
    return err;
}
int count_of_unique(int **parse,int row,int col)
{
    int i,k,unique=0,*ele,flag,e=0;
    ele=(int *)malloc(sizeof(int)*row);	
    for(i=0;i<row;i++) {
        flag=0;
	for(k=0;k<e;k++) {	
	    if(parse[i][col]==ele[k]) {
		flag=1;
  	 	break;
	    }
 	}
	if(flag!=1) {
	    ele[e++]=parse[i][col];
	    unique++;	
	}
    }
    return unique;
}
int *unique_elements(int **parse,int row,int col,int unique)
{
    int *ele,i,k,e=0,flag;
    ele=(int *)malloc(sizeof(int)*unique);
    for(i=0;i<row;i++) {
	flag=0;
        for(k=0;k<e;k++) {
	    if(parse[i][col]==ele[k]) {
		flag=1;
		break;
	    }
	}
	if(flag!=1)
	    ele[e++]=parse[i][col];
    }
    return ele;
}
int *class_count(int **parse,int *class,int row,int col,int class_size)
{
    int *count_of_class,count,coc=0,i,inst;
    count_of_class=(int *)malloc(sizeof(int)*class_size);
    for(i=0;i<class_size;i++) {
	inst=class[i];
	count=count_unique(parse,row, col,inst);
	count_of_class[coc++]=count;
    }
    return count_of_class;
}
int count_unique(int **parse,int row,int col,int j)
{	
    int i,count=0;
    for(i=0;i<row;i++) {
	if(parse[i][col-1]==j)		
	    count++;
    }
    return count;
}
int ***statistics(int *class,int class_size,int **parse, int row,int col)
{
    int ***matrix,*ele,x,i,j,k,unique,count;
    matrix=(int ***)malloc(sizeof(int**)*col);
    for(i = 0; i < MAX; i++) {
	matrix[i] = (int**)malloc(sizeof(int*)*MAX);		 
	for(j = 0; j < MAX; j++) {
	    matrix[i][j] = (int*)malloc(sizeof(int)*MAX);
  	}
    }
    for(x = 0; x < col-1; x++) {	
	unique=count_of_unique(parse,row,x);
	ele= unique_elements(parse,row,x,unique);
	for(i = 0; i < unique; i++) {
	    for(j = 0; j < class_size; j++) {
	        count=0;
		for(k = 0; k < row; k++) {
		    if((class[j] == parse[k][col-1]) && (ele[i] == parse[k][x]))
			count++;
		}
		matrix[x][i][j] = count;
	    }       
	}
    }
    return matrix;
}
double bayes_test(int ***prob_train,int *prob,int row_train,int col,int classes,int **parse,int **test,int row_test)
{
    int i,j,k,max,correct=0,error=0,instance;
    int *ele,unique,index;
    int *prob_test;
    prob_test=(int *)malloc(sizeof(int)*col);
    double probability,*array_max;
    array_max=(double *)malloc(sizeof(int)*classes);
    double percent;
    for(i=0;i<row_test;i++){
        for(j=0;j<classes;j++){
	    probability=((double)prob[j]/(double)row_train);
	    for(k=0;k<col-1;k++){
                instance=test[i][k];
		unique=count_of_unique(parse,row_train,k);
		ele=unique_elements(parse,row_train,k,unique);
		index=compare(ele,instance,unique);
		prob_test[k]=prob_train[k][index][j];
	    }
            for(k=0;k<col-1;k++){
                probability=probability*((double)prob_test[k]/(double)prob[j]);
            }
            array_max[j]=probability;
        }
        max=max_class(array_max,classes);
	if(test[i][col-1]==max){
	    correct++;
	}
	else{
	    error++;
	}
    }
    percent=(((double)error/(double)row_test)*100);
    printf("Error is : %f percent",percent);
    printf("\n");
    return percent;
}
int compare(int *ele,int instance,int unique)
{
    int i;
    for(i=0;i<unique;i++){
	if(ele[i]==instance)
	    break;
    }
    return i;
}
int max_class(double *array_max,int classes)
{
    double max=0.0;
    int class_max,i;
    for(i=0;i<classes;i++){
        if(max<=array_max[i]){
	    max=array_max[i];
	    class_max=i;
	}
    }
    return class_max;
}
