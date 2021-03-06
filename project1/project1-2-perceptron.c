/*************************************************************/
/* C-program for learning of single layer neural network     */
/* based on the delta learning rule                          */
/*                                                           */
/*  1) Number of Inputs : N                                  */
/*  2) Number of Output : R                                  */
/* The last input for all neurons is always -1               */
/*                                                           */
/* This program is produced by Qiangfu Zhao.                 */
/* You are free to use it for educational purpose            */
/*************************************************************/


// perceptron rule 適用version (delta rule は使っていない)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define N             3
#define R             3
#define n_sample      3
#define eta           0.5
#define lambda        1.0
#define desired_error 0.0003
#define sigmoid(x)    (2.0/(1.0+exp(-lambda*x))-1.0)
#define frand()       (rand()%10000/10001.0)
#define randomize()   srand((unsigned int)time(NULL))

double x[n_sample][N]={
  {10,2,-1},
  {2,-5,-1},
  {-5,5,-1},
};
double d[n_sample][R]={
  {1,-1,-1},
  {-1,1,-1},
  {-1,-1,1},
};
double w[R][N];
double o[R];

void Initialization(void);
void FindOutput(int);
void PrintResult(void);
double DiscreteFunction(double);

main(){
  int    i,j,p,q=0;
  double Error=DBL_MAX;
  double delta;
  double learning;

  Initialization();
  while(Error>desired_error){
    q++;
    Error=0;
    for(p=0; p<n_sample; p++){
      FindOutput(p);
      for(i=0;i<R;i++){
        // printf("%f ", o[i]);
	Error+=0.5*pow(d[p][i]-o[i],2.0);
      }
      // printf("\n");
      for(i=0;i<R;i++){
	// delta=(d[p][i]-o[i])*(1-o[i]*o[i])/2;
        learning = eta*(d[p][i]-o[i]);
	for(j=0;j<N;j++){
	  w[i][j]+=learning*x[p][j];
	}
      }
    }
    printf("Error in the %d-th learning cycle=%f\n",q,Error);

    // 重み出力用
    // PrintResult();
  }
  PrintResult();
}
  
/*************************************************************/
/* Initialization of the connection weights                  */
/*************************************************************/
void Initialization(void){
  int i,j;

  randomize();
  for(i=0;i<R;i++)
    for(j=0;j<N;j++)
      w[i][j]=frand()-0.5;
}

/*************************************************************/
/* Find the actual outputs of the network                    */
/*************************************************************/
void FindOutput(int p){
  int    i,j;
  double temp;

  for(i=0;i<R;i++){
    temp=0;
    for(j=0;j<N;j++){
      temp+=w[i][j]*x[p][j];
    }
    // o[i]=sigmoid(temp);
    o[i]=DiscreteFunction(temp);
  }
}


/*************************************************************/
/* discrete model of activation function                     */
/*************************************************************/
double DiscreteFunction(double x){
    if(x <= 0){
        return(-1.0);
    } else {
        return(1.0);
    }
}

/*************************************************************/
/* Print out the final result                                */
/*************************************************************/
void PrintResult(void){
  int i,j;

  printf("\n\n");
  printf("The connection weights are:\n");
  for(i=0;i<R;i++){
    for(j=0;j<N;j++)
      printf("%5f ",w[i][j]);
    printf("\n");
  }
  printf("\n\n");
}
