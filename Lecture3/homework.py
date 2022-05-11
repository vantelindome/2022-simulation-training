from dataclasses import dataclass
import math

for i in range(10001):
    v=10*i*math.pow(math.e, -i)
    print(i,v)

