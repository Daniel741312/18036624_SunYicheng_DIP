#if 0

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void threeChannelsEqualizeHist(Mat& srcMat,Mat& dstMat) {
	vector<Mat> channels;
	split(srcMat, channels);
	Mat B = channels.at(0);
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	equalizeHist(B, B);
	equalizeHist(G, G);
	equalizeHist(R, R);

#ifdef SHOWRGB
	imshow("red", R);
	imshow("green", G);
	imshow("blue", R);
#endif

	merge(channels, dstMat);

	return;
}

int main(int argc, char* argv[]) {
	Mat srcMat = imread("C:\\Users\\Daniel\\Desktop\\zft2.jpg");
	Mat dstMat=srcMat.clone();

	imshow("origin Mat", srcMat);
	threeChannelsEqualizeHist(srcMat, dstMat);
	imshow("dstMat", dstMat);

	waitKey(0);
	return 0;
}

#endif