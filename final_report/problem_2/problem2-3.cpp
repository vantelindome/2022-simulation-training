#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cfloat>
#include "BM.h"

#define Np 1000
#define L 50.0
#define tmax 1500
#define dt 0.01
#define temp 0.2
#define dim 2
#define cut 2.0
#define polydispersity 0.0

void input(double (*x)[dim], double (*v)[dim], double (*a)){
  char filename[128];
  std::ifstream file;
  sprintf(filename,"2-2/coord_T5.000_1_problem2-2.dat");
  file.open(filename);
  for(int k=0;k<Np;k++)
    file >> x[k][0] >> x[k][1] >> v[k][0] >> v[k][1] >> a[k];
  file.close();
  
}

void set_diameter(double *a){
  for(int i=0;i<Np;i++)
    a[i]=1.0+polydispersity*gaussian_rand();
}

void p_boundary(double (*x)[dim]){ // 境界条件
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++)
      x[i][j]-=L*floor(x[i][j]/L);
}

void ini_array(double (*x)[dim]){
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++)
      x[i][j]=0.0;
}

void calc_force(double (*x)[dim],double (*f)[dim],double *a){
  double dx,dy,dr,dr2,dUr,w2,w6,w12,cut2,wc2,wc6,wc12,aij;
  ini_array(f);

  for(int i=0;i<Np;i++)
    for(int j=0;j<Np;j++){
      if(i<j){
        	dx=x[i][0]-x[j][0];
          dy=x[i][1]-x[j][1];
          dx-=L*floor((dx+0.5*L)/L);
          dy-=L*floor((dy+0.5*L)/L);
          dr2=dx*dx+dy*dy;
          dr=sqrt(dr2);
          	if(dr2<cut*cut){
              aij=0.5*(a[i]+a[j]);
              w2=aij*aij/dr2;
              w6=w2*w2*w2;
              w12=w6*w6;
              cut2=cut*cut;
              wc2=aij*aij/cut2;
              wc6=wc2*wc2*wc2;
              wc12=wc6*wc6;
              dUr=-48.*w12/dr2 + 24.*w6/dr2 + 48.*wc12/(cut*dr) - 24.*w6/(cut*dr); // F_ij
              f[i][0]-=dUr*dx;
              f[j][0]+=dUr*dx;
              f[i][1]-=dUr*dy;
              f[j][1]+=dUr*dy;
            }
          }
        }
}

void eom(double (*v)[dim],double (*x)[dim],double (*f)[dim],double temp0){
  double zeta=1.0;
  double fluc=sqrt(2.*zeta*temp0*dt);
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++){
      v[i][j]+=-zeta*v[i][j]*dt+f[i][j]*dt+fluc*gaussian_rand();
      x[i][j]+=v[i][j]*dt;
    }
}


void output(double (*x)[dim],double (*v)[dim],double *a){
  char filename[128];
  std::ofstream file;
  static int j=0;
  sprintf(filename,"./2-3/coord_T%.3f_%d_problem2-3.dat",temp,j);
  file.open(filename);
  for(int i=0;i<Np;i++)
    file <<x[i][0]<<"\t"<<x[i][1]<<"\t"<<v[i][0]<<"\t"<<v[i][1]<<"\t"<<a[i]<<std::endl;
  file.close();
  j++;
}

int main(){
  double x[Np][dim],v[Np][dim],f[Np][dim],a[Np];
  double tout=0.0;
  int j=0;
  // set_diameter(a);
  input(x,v,a);

  while(j*dt < 100.0){
    j++;
    calc_force(x,f,a);
    eom(v,x,f,5.0);
  }
  j=0;
  while(j*dt < tmax){
    j++;
    calc_force(x,f,a);
    eom(v,x,f,temp);
    p_boundary(x);
    if(j*dt >= tout){
      output(x,v,a);
      tout+=100.;
    }
  }
  return 0;
}
