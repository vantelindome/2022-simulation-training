from dataclasses import dataclass
import numpy as np


t=0.0
dt=0.010
m=0.1
x=0.0 ; x1=0.0
y=0.0 ; y1=0.0
vx=0.0 ; vx1=0.0
vy=0.0 ; vy1=0.0

print(t,x,y)
t = t + dt

for t in range(10001):
    Rg=np.random.rand()
    vx1 = (1-(dt/m))*vx + np.sqrt(2*dt)*Rg/m
    vy1 = (1-(dt/m))*vy + np.sqrt(2*dt)*Rg/m

    x1 = x + vx1*dt
    y1 = y + vy1*dt

    if t%10 == 0:
        print(t,x1,y1)
    
    vx = vx1
    vy = vy1
    t = t + dt





    
