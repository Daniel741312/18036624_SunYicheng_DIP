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

	const Point2f src_pt[] = { Point2f(200,200),Point2f(250,200),Point2f(200,100)};
	const Point2f dst_pt[] = { Point2f(300,100),Point2f(300,50),Point2f(200,100)};

	Mat affine_matrix = getAffineTransform(src_pt, dst_pt);

	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
}
#endif
