#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#if 0
int main() {
	/*Arg2=0的意思是直接将彩图转化为灰度图*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\lena.jpg", 0);
	Mat result1;
	Mat result2;

	threshold(srcMat, result1, 100, 255, THRESH_BINARY);

	adaptiveThreshold(srcMat,result2,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,10);

	imshow("bin1", result1);
	imshow("bin2", result2);
	waitKey(0);
	return 0;
}
#endif