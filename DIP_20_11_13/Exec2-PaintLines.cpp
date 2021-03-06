#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#if 0
int main(int argc, char* argv[]) {
	Mat srcMat = imread("C:/Users/Daniel/Desktop/18.jpg");
	Mat cannyMat1;
	int i = 0;
	int j = 0;
	imshow("srcMat1", srcMat);

	int ratio = 3;
	double lowThreshold = 65;
	Canny(srcMat, cannyMat1, lowThreshold, lowThreshold * ratio, 3, false);
	imshow("cannyMat1", cannyMat1);

	//Mat lineMat;
	vector<Vec2f> lines;
	double rho=1;
	double theta=CV_PI/180;
	int threshold = 100;
	HoughLines(cannyMat1, lines, rho, theta, threshold, 0, 0, 0, CV_PI);

	for (vector<Vec2f>::iterator it = lines.begin(); it != lines.end(); ++it) {
		float rho = (*it)[0];
		float theta = (*it)[1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = saturate_cast<int>(y0 - 1000 * (a));
		line(srcMat, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}

	imshow("lineMat", srcMat);
	waitKey(0);
	return 0;
}
#endif
