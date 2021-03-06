#if 1

#include<iostream>
#include<cmath>
#include<cstdlib>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void gamma(Mat& inputImage, Mat& outputImage) {
	int i = 0;
	int j = 0;
	double gm = 1.0/2.2;
	int rowNum = inputImage.rows;
	int colNum = inputImage.cols;
	outputImage = inputImage.clone();

	double Lut[256] = { 0 };

	for (i = 0; i < 255; ++i)
		//Lut[i] = i / 255.0;
		Lut[i] = pow(i/256.0,gm);

	/*竖着跑的外层循环*/
	for (i = 0; i < rowNum; ++i) {
		/*每到一行,拿到一个行首数据的指针,把这一行看作数组操作*/
		uchar* data = outputImage.ptr<uchar>(i);
		/*横着跑的内层循环*/
		for (j = 0; j < colNum; ++j) {
			data[j] =255*Lut[(int)data[j]];
		}
	}

	return;
}

int main() {
	Mat srcMat = imread("C:\\Users\\Daniel\\Desktop\\zft1.jpg");
	Mat dstMat;
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);
	imshow("srcMat", srcMat);

	gamma(srcMat, dstMat);
	imshow("dstMat", dstMat);

	waitKey(0);
	return 0;
}

#endif
