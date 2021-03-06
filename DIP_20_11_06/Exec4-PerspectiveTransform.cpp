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

	const Point2f src_pt[] = { Point2f(150,150),Point2f(150,300),Point2f(350,300) ,Point2f(350,150)};
	const Point2f dst_pt[] = { Point2f(200,150),Point2f(200,300),Point2f(340,270) ,Point2f(340,180)};

	Mat perspective_matrix = getPerspectiveTransform(src_pt, dst_pt);

	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
}
#endif
