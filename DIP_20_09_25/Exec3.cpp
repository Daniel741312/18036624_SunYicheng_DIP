#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 0
int main() {
	int i = 0;
	int j = 0;

	Mat srcMat=imread("C:\\Users\\18798\\Desktop\\lena.jpg");
	int weight = srcMat.cols;
	int height = srcMat.rows;

	/*定义一个阈值量*/
	uchar threhold = 100;
	for (j = 0; j < height; j++) {
		for (i = 0; i < weight; i++) {
			uchar aver = srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2] / 3;
			/*当aver>阈值取255,当aver<阈值取0,实现二值化*/
			aver = aver > threhold ? 255 : 0;
			srcMat.at<Vec3b>(j, i)[0] = aver;
			srcMat.at<Vec3b>(j, i)[1] = aver;
			srcMat.at<Vec3b>(j, i)[2] = aver;
		}
	}
	imshow("Exec3-彩色图转化为二值图", srcMat);
	waitKey(0);
	return 0;
}
#endif
