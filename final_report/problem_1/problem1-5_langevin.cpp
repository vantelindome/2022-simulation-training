#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cfloat>
#include "BM.h"

#define tmax 100
#define dt 0.01
#define m 0.10
#define ensemble 10000
#define dim 2
//using namespace std;

void ini_phase(double *x,double *v){
  int i;
  for(i=0;i<dim;i++){
    x[i]=0.;
    v[i]=0.;
  }
}

void ini_clock(int *j,double *tout){
  *j=0;
  *tout=1.e-2;
}

void eom(double *v,double *x){
  int i;
  for(i=0;i<dim;i++){
    v[i] = (1-(dt/m))*v[i]+sqrt(2.*dt)*gaussian_rand()/m;
    x[i]+= v[i]*dt;
  }
}

void output(double *x,int j){
  char filename[128];
  std::ofstream file;

  sprintf(filename,"1-5/m%.1f.dat",m);
  file.open(filename,std::ios::app); //append
  file <<j*dt<<"\t"<<x[0]<<"\t"<<x[1]<<std::endl;
  //  std::cout<<j*dt<<"\t"<<x[0]<<"\t"<<x[1]<<"\t"<<x[2]<<std::endl;
  file.close();  
}

int main(){
  double x[dim],v[dim],t,tout;
  int i,j;
  ini_phase(x,v);
  for(i=0;i<ensemble;i++){
    ini_clock(&j,&tout);
    output(x,j);
    while(j*dt < tmax){
      j++;
      eom(v,x);
      if(j*dt >= tout){
        output(x,j);
        tout*=1.2;
      }
    }
  }

  return 0;
}
