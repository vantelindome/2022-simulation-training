#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cfloat>
#include "BM.h"

#define m 0.10
#define dt 0.01
#define ensemble 10000
#define window 52
#define dim 2
//using namespace std;

void ini(double *dr2){
  for(int i=0;i<window;i++){
    dr2[i]=0.0;
  }
}

void input(double (*x)[dim],double *t){
  char filename[128];
  std::ifstream file;
  sprintf(filename,"1-5/m%.1f.dat",m);
  file.open(filename);
  int asize=ensemble*window;
  for(int i=0;i<asize;i++){
    file >> t[i] >> x[i][0] >> x[i][1];
  }
  file.close();

}

void output(double *t,double *dr2){
  char filename[128];
  std::ofstream file;
  sprintf(filename,"1-5/r2_m%.1f.dat",m);
  file.open(filename);
  for(int i=1;i<window;i++)
    file<<t[i]-t[0]<<"\t"<<dr2[i]<<std::endl;
  file.close();

}

void analyze(double (*x)[dim],double *t,double *dr2){
  double dx[dim];
  for(int i=0;i<ensemble;i++){
    for(int j=0;j<window;j++){
      for(int k=0;k<dim;k++){
        dx[k]=(x[j+window*i][k]-x[window*i][k]);
        dr2[j]+=(dx[k]*dx[k])/ensemble;
      }
    }
  }
}

int main(){
  double t[ensemble*window],dr2[window],corr[window],integral=0.0;
  int i,j;
  double  (*x)[dim] = new double[ensemble*window][dim];
  double  (*v)[dim] = new double[ensemble*window][dim];

  ini(dr2);
  input(x,t);
  analyze(x,t,dr2);
  output(t,dr2);
  delete[] x;
  delete[] v;
  return 0;
}
