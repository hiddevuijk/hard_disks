import numpy as np
import matplotlib.pyplot as plt

Np = 100
L = 50.
L /= 2
pcdat = np.loadtxt("pc.dat")

bins = pcdat[:,0]
g = pcdat[:,1]

plt.axvline(1,c='black')
plt.axhline(1,c='black')

from scipy.integrate import simps
bs = bins[1] - bins[0]
g2 =g* 2*np.pi*bins*(Np/(L*L))
I = simps(g2,bins)
print(I)
print(I/(Np-1))


N = g2.shape[0]
print(simps(g2[:N/2],bins[:N/2]))


plt.ylim([0,max(g)*1.1])
plt.xlim([0,L])
plt.plot(bins,g)
plt.show()


