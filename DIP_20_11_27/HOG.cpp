#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>
#include<cstring>
using namespace cv;
using namespace std;

#if 1

int calcHOG(Mat srclMat, float* hist, int nAngle, int blockSize);
float normaL2(float* hist1, float* hist2, int bins);

int main(int argc, char* argv[]) {
	Mat refMat = imread("C:\\Users\\Daniel\\Desktop\\ref.jpg");
	Mat plMat = imread("C:\\Users\\Daniel\\Desktop\\pl.jpg");
	Mat bgMat = imread("C:\\Users\\Daniel\\Desktop\\bg.jpg");

	int blockSize = 16;
	int nX = refMat.cols / blockSize;
	int nY = refMat.rows / blockSize;
	int nAngle = 8;
	int bins = nX * nY * nAngle;
	/*������*/
	float dis1 = 0;
	float dis2 = 0;
	/*��鷵��ֵ*/
	int reCode = 0;

	/*�������鲢��ʼ��Ϊ0*/
	float* ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);

	float* pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float) * bins);

	float* bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float) * bins);


	/*����HOG����鷵��ֵ,һ�������ͷ��ڴ沢����-1*/
	reCode = calcHOG(refMat, ref_hist, nAngle, blockSize);
	
	reCode = calcHOG(plMat, pl_hist, nAngle, blockSize);

	reCode = calcHOG(bgMat, bg_hist, nAngle, blockSize);

	/*ref��pl�ľ���*/
	dis1 = normaL2(ref_hist, pl_hist, bins);
	/*ref��bg�ľ���*/
	dis2 = normaL2(ref_hist, bg_hist, bins);
	cout << dis1 << endl;
	cout << dis2 << endl;
	
	/*�ͷ��ڴ沢�˳�����*/
	delete[] ref_hist;
	delete[] pl_hist;
	delete[] bg_hist;
	return 0;
}

/*��������ͼƬ��HOG*/
int calcHOG(Mat src, float* hist, int nAngle, int cellSize) {
	Mat gx, gy;
	Mat mag, angle;
	/*���ݶ�*/
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	/*ת����������*/
	cartToPolar(gx, gy, mag, angle, true);
	/*�и����*/
	Rect roi;
	roi.height = cellSize;
	roi.width = cellSize;

	int nX = src.cols / cellSize;
	int nY = src.rows / cellSize;

	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			Mat roiMat, roiMag, roiAgl;
			roi.x = j * cellSize;
			roi.y = i * cellSize;
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			int head = (i * nX + j) * nAngle;
			for (int n = 0; n < roiMat.rows; n++) {
				for (int m = 0; m < roiMat.cols; m++) {
					hist[head + (int)roiAgl.at<float>(n, m) / (360 / nAngle)] += roiMag.at<float>(n, m);
				}
			}
		}
	}
	return 0;
}

/*��������list�ľ���*/
float normaL2(float* hist1, float* hist2, int bins) {
	int i = 0;
	float ret = 0;

	for (i = 0; i < bins; ++i)
		ret = ret + ((*(hist1 + i)) - (*(hist2 + i))) * ((*(hist1 + i)) - (*(hist2 + i)));

	ret = sqrt(ret);
	return ret;
}

#endif