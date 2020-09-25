#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 0
int main() {
	/*Arg2=0的意思是直接将彩图转化为灰度图*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\lena.jpg",0);
	imshow("Exec2-彩色图像转灰度图像", srcMat);

	waitKey(0);
	return 0;
}
#endif
