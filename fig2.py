import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import simps

Np2 = 100
L2 = 20.
rho2 = Np2/(L2*L2)

Np = 25
L = 10.
rho = Np/(L*L)
pcdat = np.loadtxt("pc.dat")
pc2dat = np.loadtxt("pc1.dat")


bins = pcdat[:,0]
bins2 = pc2dat[:,0]
g = pcdat[:,1]
g2 = pc2dat[:,1]

plt.axvline(1,c='black')
plt.axhline(1,c='black')

print(simps(g*2*np.pi*bins,bins)*rho/(Np-1))
print(simps(g2*2*np.pi*bins2,bins2)*rho2/(Np2-1))

N = g.shape[0]
IL = simps(g[:N/2]*2*np.pi*bins[:N/2],bins[:N/2])
IR = simps(g[N/2:]*2*np.pi*bins[N/2:],bins[N/2:])



plt.plot(bins,g,color="blue")
plt.plot(bins2,g2,color="red")
plt.show()


