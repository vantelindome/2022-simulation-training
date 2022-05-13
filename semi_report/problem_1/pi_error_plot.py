import matplotlib
import matplotlib.pyplot as plt
%matplotlib inline
%config InlineBackend.figure_format = 'retina'
import matplotlib.cm as cm  # colormap
import numpy as np

plt.rcParams["text.usetex"] =True 
fig = plt.figure()

data = np.genfromtxt('buffon.txt')

plt.plot((data[:,0], data[:,2]))
plt.set_title('Relation between absolute error of pi and ')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('number of dropping pins')
plt.ylabel('absolute error')

plt.savefig('problem1-3.png')
plt.savefig('problem1-3.pdf')
plt.show()
