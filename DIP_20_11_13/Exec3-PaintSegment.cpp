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
	vector<Vec4i> lines;
	double rho = 1;
	double theta = CV_PI / 180;
	int threshold = 20;
	double minLineLength = 20;
	double maxLineGap = 20;
	HoughLinesP(cannyMat1, lines, rho, theta, threshold,minLineLength,maxLineGap);

	for (vector<Vec4i>::iterator it = lines.begin(); it != lines.end(); ++it) {
		int x1 = it[0][0];
		int y1 = it[0][1];
		int x2 = it[0][2];
		int y2 = it[0][3];
		Point pt1 = Point(x1, y1);
		Point pt2 = Point(x2, y2);
		line(srcMat, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}

	imshow("lineMat", srcMat);
	waitKey(0);
	return 0;
}
#endif
