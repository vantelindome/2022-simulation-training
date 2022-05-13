from dataclasses import dataclass
import math
import numpy as np

dt = 0.010
dt_num = 50000
T=3
v_n = 0.01
x_n = 0.0
x_n1 = 0.0
v_n1 = 0.0
dt_total = 0.0
while dt_total < dt*(dt_num):
    dt_total=dt_total + dt
    v_n1 = (1-T*dt)*v_n - x_n*dt
    x_n1 = (1-dt)*x_n + (1-T*dt)*v_n*dt
    
    
    print(dt_total,x_n1)
    x_n = x_n1
    v_n = v_n1