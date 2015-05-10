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

	# 主成分分析前のサイズ
	print X.shape

	# 主成分分析による次元削減
	pca = PCA(X)
	X_pca = pca.transform(dim=2)

	# 主成分分析後のサイズ
	print X_pca.shape
	
	# 表示
	plt.plot(X_pca, 'b.')
	plt.show()

if __name__ == '__main__':
	argvs = sys.argv
	argc = len(argvs)
	if argc < 2:
		print "Usage: python " + argvs[0] + " <filename>"
		quit()
	
	test_pca(argvs[1])
