#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;

/*分离三个通道*/
#if 0
int main() {
	Mat src_color = imread("C:\\Users\\18798\\Desktop\\rgbDemo.png");
	std::vector<Mat> channels;
	split(src_color, channels);
	Mat B = channels.at(0);
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	imshow("red", R);
	imshow("green",G);
	imshow("blue",R);
	imshow("origin Mat", src_color);

	waitKey(0);
	return 0;
}
#endif
