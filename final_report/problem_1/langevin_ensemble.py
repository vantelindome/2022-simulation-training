from dataclasses import dataclass
from distutils.util import run_2to3
import numpy as np
import math


t=0.0
dt=0.01
m=0.10 # m^*
ensemble=1
x=0.00 ; x1=0.00
y=0.00 ; y1=0.00
vx=0.00 ; vx1=0.00
vy=0.00 ; vy1=0.00
totalx=0.00
totaly=0.00
listx=[0.00]*ensemble
listy=[0.00]*ensemble
listx1=[]
listy1=[]

t = t + dt


for n in range(10000):
    for i in range(ensemble):
        Rg1=np.random.randn()
        Rg2=np.random.randn()
        vx1 = (1-(dt/m))*vx + np.sqrt(2*dt)*Rg1/m
        vy1 = (1-(dt/m))*vy + np.sqrt(2*dt)*Rg2/m

        x = listx[i]
        y = listy[i]

        x1 = x + vx1*dt
        y1 = y + vy1*dt
        listx1.append(x1)
        listy1.append(y1)
        i=i+1

    if n%10 == 0:
        r2 = (totalx*totalx + totaly*totaly)/10000
        print(t,r2)
    vx = vx1
    vy = vy1
    x = x1
    y = y1
    t = t + dt
    listx=listx1
    listy=listy1
    listx1.clear()
    listy1.clear()
