﻿#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;

int main() {
	// 3x3の行列
	// 1 2 3
	// 3 1 0
	// 2 1 4
	cv::Mat_<double> X = (cv::Mat_<double>(3, 3) << 1,2,3,3,1,0,2,1,4);

	// 各行が、各データ
	cv::PCA pca(X, cv::Mat(), CV_PCA_DATA_AS_ROW);
	cout << pca.eigenvalues << endl;

	// 固有ベクトル（各行が各固有ベクトル）
	cout << pca.eigenvectors << endl;

	cout << pca.project(X) << endl;

	return 0;
}
