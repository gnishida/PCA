import sys
import numpy as np
import matplotlib
import matplotlib.pyplot as plt



# データの読み込み
X = []
for l in open('residue.txt').readlines():
	list = l.split(',')
	rec = [float(d) for d in list]
	X.append(rec)

X = np.array(X)

plt.xlabel('#data')
plt.ylabel('RMSE')
plt.plot(X[:,0], X[:,2], 'b.-', label='RMSE');
plt.legend(loc='lower right')
#plt.plot(X[:,0], X[:,2], 'g.', label='#condition');
#plt.legend(loc='upper right')
plt.show()

