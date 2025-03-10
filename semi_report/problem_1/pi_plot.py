import matplotlib
import matplotlib.pyplot as plt
%matplotlib inline
%config InlineBackend.figure_format = 'retina'
import matplotlib.cm as cm  # colormap
import numpy as np

plt.rcParams["text.usetex"] =True 
fig = plt.figure()

data = np.genfromtxt('buffon.txt')

plt.plot((data[:,0], data[:,1]))
plt.set_title("Calculate pi using Buffon's pin")
plt.xscale('log')
plt.xlabel('number of dropping pins')
plt.ylabel('measured Pi')

plt.savefig('problem1-2.png')
plt.savefig('problem1-2.pdf')
plt.show()
