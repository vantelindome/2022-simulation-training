#include <stdio.h> // for printf, etc
#include <stdlib.h> // for rand(), etc
#include <math.h> // for sin(),cos(), etc
#include <iostream>// for cout, etc
#include <iomanip>// for setprecision()
#include <fstream> // for ifstream/ofstream
#include <time.h>// for time(NULL), etc
#include "MT.h"// for MT, 同じdirectoryのファイルを読み込む

using namespace std;
int main(void){
  int i, count = 0, max = 1e+9;
  double x,y,z,pi, out=1.e+2; //corrected 4/17
  char fname[128];
  ofstream file; // fileを呼ぶための関数
  srand(time(NULL));
  sprintf(fname,"pi-error.dat");
  file.open(fname);
  for(i=0;i<max;i++){
    x = (double)rand()/RAND_MAX;
    y = (double)rand()/RAND_MAX;
    z = x*x + y*y;
    if(z<1)
      count++;
    if(i>=(int)out){
      pi=(double)count /i*4;
      file<<setprecision(16)<<i<<" "<<pi<<" "<<abs(pi-M_PI)<<endl;;// abs:絶対値
      // cout<<setprecision(16)<<i<<" "<<pi<<" "<<abs(pi-M_PI)<<endl;// M_PI: math.hにあるπの理論値
      out*=1.2;//前の変数を1.2倍
    }
  }
  file.close();
  out=1e+2;
  count=0;

  sprintf(fname,"pi-error-MT.dat");
  file.open(fname);
  init_genrand(time(NULL));
  for(i=0;i<max;i++){
    x = genrand_res53();
    y = genrand_res53();
    z = x*x + y*y;
    if(z<1)
      count++;
    if(i>=(int)out){
      pi=(double)count /i*4;
      file<<setprecision(16)<<i<<" "<<pi<<" "<<abs(pi-M_PI)<<endl;;
      cout<<setprecision(16)<<i<<" "<<pi<<" "<<abs(pi-M_PI)<<endl;
      out*=1.2;
    }
  }
  file.close();
  return 0;
}

