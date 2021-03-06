#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#if 1
int main(int argc, char* argv[]) {
	Mat srcMat = imread("C:/Users/Daniel/Desktop/lena.jpg");
	Mat dstMat;
	Point2f center(srcMat.cols / 2.0, srcMat.rows / 2.0);

	double angle = 10.0;
	double scale = 1.0;

	Mat rot = getRotationMatrix2D(center, angle, scale);
	Rect bbox = RotatedRect(center,srcMat.size(),angle).boundingRect();

	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

	warpAffine(srcMat, dstMat, rot, bbox.size());
	imshow("dstMat", dstMat);

	waitKey(0);
	return 0;
}
#endif