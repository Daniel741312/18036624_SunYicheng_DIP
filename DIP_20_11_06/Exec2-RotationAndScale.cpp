#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 0
int main(int argc, char* argv[]) {
	Mat dstMat;
	Mat srcMat = imread("C:\\Users\\Daniel\\Desktop\\lena.jpg");
	if (srcMat.empty()) {
		std::cout << "打开失败" << std::endl;
		return -1;
	}

	float angle = -10.0;
	float scale = 1;

	Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	Mat affine_matrix = getRotationMatrix2D(center, angle, scale);

	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
}
#endif
