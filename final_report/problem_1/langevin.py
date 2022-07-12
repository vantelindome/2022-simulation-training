from dataclasses import dataclass
import numpy as np
import math


t=0.0
dt=0.01
m=10.0 # m^*
x=0.00 ; x1=0.00
y=0.00 ; y1=0.00
vx=0.00 ; vx1=0.00
vy=0.00 ; vy1=0.00

t = t + dt

for n in range(10000):
    Rg1=np.random.randn()
    Rg2=np.random.randn()
    vx1 = (1-(dt/m))*vx + np.sqrt(2*dt)*Rg1/m
    vy1 = (1-(dt/m))*vy + np.sqrt(2*dt)*Rg2/m

    x1 = x + vx1*dt
    y1 = y + vy1*dt

    if n%10 == 0:
        print(t,x1,y1)
    vx = vx1
    vy = vy1
    x = x1
    y = y1
    t = t + dt




    
