#include<string>
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void threshold_Mat(int th, void* data);
string window_name = "binaryMat";

#if 1
int main() {

	Mat srcMat=imread("C:\\Users\\18798\\Desktop\\lena.jpg");
	Mat gryMat;
	int lowTh = 30;
	int maxTh = 255;

	if (!srcMat.data) {
		cout << "load image error" << endl;
		return 0;
	}

	cvtColor(srcMat, gryMat, CV_BGR2GRAY);
	imshow(window_name, gryMat);
	createTrackbar("threshold",
		window_name,
		&lowTh,
		maxTh,
		threshold_Mat,
		&gryMat
	);
	waitKey(0);

	return 0;
}

void threshold_Mat(int th, void* data) {
	Mat src = *(Mat*)data;
	Mat dst;
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}
#endif

