#include"header.h"
int main()
{
    char buffer[1024];
    char *record,*line;
    int c,d,i=0,j=0,l,k,m=0,x,y,a,r,b;
    char ***mat,**cp;
    int **parse,**parse1;
    //char p;
    double *error,sum=0.0,average;
    error=(double *)malloc(sizeof(double)*MAX);
    FILE *fstream = fopen("input_file.csv","r");
    mat=(char ***)malloc(sizeof(char**)*MAX);
    for(i = 0; i < MAX; i++){
	mat[i] = (char**)malloc(sizeof(char*)*MAX);		 
	for(j=0;j<MAX;j++){
	    mat[i][j] = (char*)malloc(sizeof(char)*MAX);
	}
    }
    cp=(char **)malloc(sizeof(char*)*MAX);
    for(i = 0; i < MAX; i++) 
	cp[i] = (char*)malloc(sizeof(char)*MAX);
    parse=(int **)malloc(sizeof(int*)*MAX);
    for(i = 0; i < MAX; i++) 
	parse[i] = (int*)malloc(sizeof(int)*MAX);
    parse1=(int **)malloc(sizeof(int*)*MAX);
    for(i = 0; i < MAX; i++) 
	parse1[i] = (int*)malloc(sizeof(int)*MAX);	
    if(fstream == NULL){
	printf("\n file opening failed ");
	return -1 ;
    }
    i=0;
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
	j=0;
	record = strtok(line,",");
	while(record != NULL){
	    strcpy(mat[i][j],record);
	    //sscanf(record,"%d",&p);
	    //mat[i][j]=record;
	    j++;
	    record = strtok(NULL,",");
	}
	i++;
    }
    for(k=0;k<i;k++){
	for(l=0;l<j;l++){
	    printf("%s\t",mat[k][l]);
	}
	printf("\n");
    }
    printf("\n");
    for(k=0;k<1;k++){
	for(l=0;l<j;l++){
	    strcpy(cp[m++],mat[k][l]);
	}
    }
    a=1;
    for(y=0;y<1;y++){
	for(x=0;x<m-1;x++){
	    parse[y][x]=a++;
	}
	parse[y][x]=-1;
    }
    x=0;
    for(k=0;k<j;k++){
	y=1;
	m=0;
        strcpy(cp[m++],mat[0][0]);
       	for(l=1;l<i;l++){
	    for(b=0;b<m;b++){
		r=strcmp(cp[b],mat[l][k]);
		if(r==0){
		    parse[y][x]=parse[b][k];
		    strcpy(cp[m++],mat[l][k]);
		    y++;
		    break;
		}
	    }
	    if(r!=0){
		parse[y][x]=max(parse,y,x);
       		strcpy(cp[m++],mat[l][k]);
		y++;
	    }
	}
	x++;	
    }
    for(c=0;c<(i-1);c++) {
	for(d=0;d<j;d++){
	    parse1[c][d]=parse[c+1][d];
	}
    }					
    for(c=0;c<(i-1);c++){
       	for(d=0;d<j;d++){
             printf("%d\t",parse1[c][d]);
        }
	printf("\n");
    }
    for(c=0;c<iteration;c++){
	error[c]=func_main(parse1,i-1,j,c);
    }
    for(i=0;i<iteration;i++){
	sum=sum+error[i];
    }
    average=(sum/iteration);
    
    printf("Average error is:%f\n",average);
    return 0;
}
int max(int **parse,int y,int x)
{
    int p;
    int maxi=-1;
    for(p=0;p<y;p++){
	if(maxi<parse[p][x])
	maxi=parse[p][x];
    }
    return ++maxi;
}
