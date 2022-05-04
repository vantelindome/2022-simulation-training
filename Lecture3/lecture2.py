import matplotlib
import matplotlib.pyplot as plt
%matplotlib inline
%config InlineBackend.figure_format = 'retina'
import matplotlib.cm as cm  # colormap
import numpy as np
plt.rcParams["text.usetex"] =True 
fig = plt.figure(figsize=(18,8))

data = np.loadtxt('lecture2_python.dat')


x = data[:, 0]
y = data[:, 1]

plt.plot(x, y,'r--')
plt.xscale("log")
plt.xlabel("Time")
plt.ylabel("10*t*exp(-t)")
plt.show()