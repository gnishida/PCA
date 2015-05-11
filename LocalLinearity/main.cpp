/**
 * L-system for 2-d treeのhigh-level indicatorとPM parameterの関係が、
 * localではlinearで近似できるのかどうか、調べるための実験。
 *
 * high-level indicatorの各データについて、その近傍点のみを使って
 * linear regressionを行い、RMSEを計算する。
 * 近傍点までの距離を徐々に増やした場合、RMSEがどう変化するか、調べてみた。
 *
 * @author Gen Nishida
 * @date 5/10/2015
 */

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "MLUtils.h"
#include "LinearRegression.h"

using namespace std;

int main(int argc,char *argv[]) {
	if (argc < 3) {
		cout << endl;
		cout << "Usage: " << argv[0] << " <filename of X> <filename of Y>" << endl;
		cout << endl;

		return -1;
	}

	cv::Mat_<double> X, Y;
	ml::loadDataset(argv[1], X);
	ml::loadDataset(argv[2], Y);

	// normalize
	cv::Mat_<double> normalizedX, muX, maxX;
	ml::normalizeDataset(X, normalizedX, muX, maxX);
	cv::Mat_<double> normalizedY, muY, maxY;
	ml::normalizeDataset(Y, normalizedY, muY, maxY);

	ml::addBias(normalizedX);


#if 0
	FILE* fp = fopen("residue.txt", "w");

	double threshold = 3;
	int count = 0;
	for (int r = 0; r < normalizedX.rows; ++r) {
		// このデータ近傍のデータを集める
		vector<cv::Mat_<double> > listX;
		vector<cv::Mat_<double> > listY;
		for (int r2 = 0; r2 < normalizedX.rows; ++r2) {
			if (cv::norm(normalizedX.row(r) - normalizedX.row(r2)) > threshold) continue;

			listX.push_back(normalizedX.row(r2));
			listY.push_back(normalizedY.row(r2));
		}

		// 近傍データを集めて、行列X2を作成
		cv::Mat_<double> X2(listX.size(), X.cols);
		for (int i = 0; i < listX.size(); ++i) {
			for (int c = 0; c < X.cols; ++c) {
				X2(i, c) = listX[i](0, c);
			}
		}

		// 近傍データを集めて、行列Y2を作成
		cv::Mat_<double> Y2(listY.size(), Y.cols);
		for (int i = 0; i < listY.size(); ++i) {
			for (int c = 0; c < Y.cols; ++c) {
				Y2(i, c) = listY[i](0, c);
			}
		}

		if (X2.rows < X2.cols) continue;
		
		LinearRegression lr;
		double residue = lr.train(X2, Y2);

		fprintf(fp, "%d,%lf\n", X2.rows, residue);

		count++;
	}

	cout << count << "/" << normalizedX.rows << endl;

	fclose(fp);
#endif

#if 1
	FILE* fp = fopen("residue.txt", "w");

	for (double threshold = 1.0; threshold < 4.0; threshold += 0.2) {
		int count = 0;
		double total_num_data = 0.0;
		double total_residue = 0.0;
		for (int r = 0; r < X.rows; ++r) {
			// このデータ近傍のデータを集める
			vector<cv::Mat_<double> > listX;
			vector<cv::Mat_<double> > listY;
			for (int r2 = 0; r2 < normalizedX.rows; ++r2) {
				if (cv::norm(normalizedX.row(r) - normalizedX.row(r2)) > threshold) continue;

				listX.push_back(normalizedX.row(r2));
				listY.push_back(normalizedY.row(r2));
			}

			// 近傍データを集めて、行列X2を作成
			cv::Mat_<double> X2(listX.size(), X.cols);
			for (int i = 0; i < listX.size(); ++i) {
				for (int c = 0; c < X.cols; ++c) {
					X2(i, c) = listX[i](0, c);
				}
			}

			// 近傍データを集めて、行列Y2を作成
			cv::Mat_<double> Y2(listY.size(), Y.cols);
			for (int i = 0; i < listY.size(); ++i) {
				for (int c = 0; c < Y.cols; ++c) {
					Y2(i, c) = listY[i](0, c);
				}
			}

			if (X2.rows < X2.cols) continue;
		
			LinearRegression lr;
			total_residue += lr.train(X2, Y2);

			total_num_data += X2.rows;
			count++;
		}
		total_residue /= (double)count;
		total_num_data = (double)total_num_data / (double)count;

		cout << count << "/" << X.rows << ", Avg residue=" << total_residue << ", Avg #data=" << total_num_data << endl;

		fprintf(fp, "%lf,%lf,%lf\n", threshold, total_residue, total_num_data);
	}

	fclose(fp);
#endif

	return 0;
}
