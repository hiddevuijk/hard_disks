import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("config.dat")
x = data[:,0]
y = data[:,1]

L = 10.
r = .5
fig, ax = plt.subplots()

aax=r/1.5
aay=r/2.5
for i in range(len(data)):
	for xi in [-1,0,1]:
		for yi in [-1,0,1]:
			ax.add_artist(plt.Circle( (x[i]+xi*L,y[i]+yi*L),r, fill=False ))
			ax.annotate(str(i),(x[i]+xi*L-aax,y[i]+yi*L-aay),size=7.)

plt.vlines(0,-L,2*L)
plt.vlines(L,-L,2*L)
plt.hlines(0,-L,2*L)
plt.hlines(L,-L,2*L)


#plt.xlim([-L,L+L])
#plt.ylim([-L,L+L])

plt.xlim([0,L])
plt.ylim([0,L])

ax.set_aspect('equal')
plt.show()

