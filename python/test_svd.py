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
		rec = [int(d) for d in data]
		X.append(rec)

	X = np.array(X)
	print X

	# 主成分分析前のサイズ
	print X.shape

	# SVD
	U, S, V = np.linalg.svd(X)
	
	print S

if __name__ == '__main__':
	argvs = sys.argv
	argc = len(argvs)
	if argc < 2:
		print "Usage: python " + argvs[0] + " <filename>"
		quit()
	
	test_pca(argvs[1])
