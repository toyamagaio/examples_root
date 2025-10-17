import numpy as np
import matplotlib.pyplot as plt
 
plt.rcParams['xtick.direction'] = 'in'
plt.rcParams['ytick.direction'] = 'in'
 
x = np.arange(-5, 5, 0.1)
y = np.sin(x)
 
plt.plot(x, y)
 
plt.show()
