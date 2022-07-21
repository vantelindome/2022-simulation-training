#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cfloat>
#include "BM.h"

#define Np 1000
#define L 50.0
#define tmax 100
#define dtmd 0.001
#define dim 2
#define cut 2.0
#define polydispersity 0.0

void input(double (*x)[dim],double (*v)[dim], double (*a)){
  char filename[128];
  std::ifstream file;
  sprintf(filename,"2-3/coord_T0.200_150_problem2-3.dat");
  file.open(filename);
  for(int k=0;k<Np;k++)
    file >> x[k][0] >> x[k][1] >> v[k][0] >> v[k][1] >> a[k];
  file.close();
  
}

void set_diameter(double *a){
  for(int i=0;i<Np;i++)
    a[i]=1.0+polydispersity*gaussian_rand();
}

void p_boundary(double (*x)[dim]){
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++)
      x[i][j]-=L*floor(x[i][j]/L);
}

void ini_array(double (*x)[dim]){
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++)
      x[i][j]=0.0;
}

void calc_force(double (*x)[dim],double (*f)[dim],double *a,double *U){
  *U=0.0;
  double dx,dy,dr,dr2,dUr,w2,w6,w12,cut2,wc2,wc6,wc12,wc12c,wc6c,aij;

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
              wc12c = wc12/cut;
              wc6c = wc6/cut;
              *U += 4.*(w12-w6)-4.*(wc12-wc6)-(-48.*wc12/cut+24.*wc6/cut)*(dr-cut);
            }
          }
        }
}


void eom_md(double (*v)[dim],double (*x)[dim],double (*f)[dim],double *a,double *U,double dt){
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++){
      x[i][j]+=v[i][j]*dt+0.5*f[i][j]*dt*dt;
      v[i][j]+=0.5*f[i][j]*dt;
    }
  calc_force(x,f,a,&(*U));
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++){
      v[i][j]+=0.5*f[i][j]*dt;
    }
  p_boundary(x);
}

void output(int k,double (*v)[dim],double U){
  char filename[128];
  double K=0.0;

  std::ofstream file;
  sprintf(filename,"2-4/energy.dat");
  file.open(filename,std::ios::app); //append
  for(int i=0;i<Np;i++)
    for(int j=0;j<dim;j++)
      K+=0.5*v[i][j]*v[i][j];
  
  // std::cout<< std::setprecision(6)<<k*dtmd<<"\t"<<K/Np<<"\t"<<U/Np<<"\t"<<(K+U)/Np<<std::endl;  
  file<< std::setprecision(6)<<k*dtmd<<"\t"<<K/Np<<"\t"<<U/Np<<"\t"<<(K+U)/Np<<std::endl;
  file.close();
}

int main(){
  double x[Np][dim],v[Np][dim],f[Np][dim],a[Np];
  double tout=0.0,U;
  int j=0;
  set_diameter(a);
  input(x,v,a);
  ini_array(f);
  
  while(j*dtmd < tmax){
    j++;
    eom_md(v,x,f,a,&U,dtmd);
    if(j*dtmd >= tout){
      output(j,v,U);
      tout+=1.;
    }
  }
  
  return 0;
}
