import matplotlib
import matplotlib.pyplot as plt
%matplotlib inline
%config InlineBackend.figure_format = 'retina'
import matplotlib.cm as cm  # colormap
import numpy as np

plt.rcParams["text.usetex"] =True 
fig = plt.figure()

data = np.genfromtxt('buffon.txt')

ax1 = fig.add_subplot(2,1,1)
ax1.plot((data[:,0], data[:,1]))
ax1.set_title("Calculate pi using Buffon's pin")
ax1.xscale('log')
ax1.xlabel('number of dropping pins')
ax1.ylabel('measured Pi')

ax2 = fig.add_subplot(2,1,2)
ax2.plt.plot((data[:,0], data[:,2]))
ax1.set_title('Relation between absolute error of pi and ')
ax2.xscale('log')
ax2.yscale('log')
ax2.xlabel('number of dropping pins')
ax2.ylabel('absolute error')


plt.savefig('problem1.png')
plt.savefig('problem1.pdf')
plt.show()
