from dataclasses import dataclass
import math
import numpy as np

pie=math.pi
l=5
d=6
n_true=0
n=1

# for n in range (10**2):
#     theta=np.random.uniform(0,pie)
#     y_s=np.random.uniform(0,d/2)
    
#     A=(l/2)*math.sin(theta)
#     if A <= y_s:
#         n_true=n_true+1

for n in range(1,10**8+1):
    theta=np.random.uniform(0,pie/2)
    y_s=np.random.uniform(0,d/2)
    
    A=(l/2)*math.sin(theta)
    if A >= y_s:
        n_true=n_true+1

    if n%100 == 0:
        p=2*l*n/(d*n_true)
        p_false=math.fabs(p-pie)
        print(n,p,p_false)







    
