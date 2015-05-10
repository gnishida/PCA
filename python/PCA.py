import numpy as np
import matplotlib.pyplot as plt

### 主成分分析の実装
class PCA:
	def __init__(self, X, normalize):
		self.X = X
		
		# 平均を引く
		self.X_bar = np.array([row - np.mean(row) for row in X.transpose()]).transpose()
		
		# 分散でわる
		if normalize == True:
			self.X_bar /= np.var(self.X_bar, 0)

		# 共分散行列を求める
		m = np.dot(self.X_bar.T, self.X_bar) / X.shape[0]
		
		# 固有値問題を解く
		(w, v) = np.linalg.eig(m)
		v = v.T
		 
		# 固有値の大きい順に固有値と固有ベクトルをソート
		tmp = {}
		for i, value in enumerate(w):
			tmp[value] = i
		
		# 固有ベクトルを計算
		# （各行が、各固有ベクトル）
		self.eigenvectors = []
		for key in sorted(tmp.keys(), reverse=True):
			self.eigenvectors.append(v[tmp[key]])
		self.eigenvectors = np.array(self.eigenvectors)
		
		self.eigenvalues = np.array(sorted(w, reverse=True))
		
		print self.eigenvalues
		print self.eigenvectors
		
	### 主成分分析による次元削減
	def transform(self, dim):
		# 最初のdim個の固有ベクトルを取得
		components = self.eigenvectors[:dim,]
		
		# データと固有ベクトルの内積
		# 固有ベクトルは、PCA空間における、元のデータ空間での係数を表す
		# 例えば、第一の固有ベクトルは、第一成分の、元のデータ空間での係数を表す
		X_pca = np.dot(self.X_bar, components.T)
		
		return X_pca