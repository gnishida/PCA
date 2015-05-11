import sys
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from PCA import PCA



def test_pca(filename):
	# データセットの読み込み
	X = []
	for l in open(filename).readlines():
		data = l.split(' ')
		rec = [float(d) for d in data]
		X.append(rec)

	X = np.array(X)

	# 主成分分析
	# （Trueを指定すると、分散で割ってnormalizeする）
	pca = PCA(X, False)
	
	print pca.eigenvalues / np.sum(pca.eigenvalues)
	
	# 寄与率を表示
	accm = []
	total = 0.0
	for v in pca.eigenvalues:
		total += v
		accm.append(total)
	accm /= total
	plt.plot(accm, 'b-');
	plt.show()
	
	# 主成分空間への写像の表示
	X_pca = pca.project(dim=2)
	plt.plot(X_pca, 'b.')
	plt.show()

if __name__ == '__main__':
	argvs = sys.argv
	argc = len(argvs)
	if argc < 2:
		print "Usage: python " + argvs[0] + " <filename>"
		quit()
	
	test_pca(argvs[1])
