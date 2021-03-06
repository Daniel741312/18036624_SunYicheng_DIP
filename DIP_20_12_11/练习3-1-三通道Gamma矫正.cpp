#if 0
/*根据图片显示加推测,文字内容是"李竹老师超级帅"*/

#define WINDOW_NAME "Gamma"
#define SHOWRGB

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int g_gm = 0;

void gamma(Mat& inputImage, Mat& outputImage) {
	int i = 0;
	int j = 0;
	double gm = g_gm / 100.0;
	int rowNum = inputImage.rows;
	int colNum = inputImage.cols;
	outputImage = inputImage.clone();

	double Lut[256] = { 0 };

	for (i = 0; i < 255; ++i)
		//Lut[i] = i / 255.0;
		Lut[i] = pow(i / 256.0, gm);

	/*竖着跑的外层循环*/
	for (i = 0; i < rowNum; ++i) {
		/*每到一行,拿到一个行首数据的指针,把这一行看作数组操作*/
		uchar* data = outputImage.ptr<uchar>(i);
		/*横着跑的内层循环*/
		for (j = 0; j < colNum; ++j) {
			data[j] = 255 * Lut[(int)data[j]];
		}
	}

	return;
}

void threeChannelsGamma(int g_gm,void* ptr) {
	vector<Mat> channels;
	Mat srcMat = *(Mat*)ptr;
	split(srcMat, channels);
	Mat B = channels.at(0);
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	/*对每一个通道Gamma矫正*/
	gamma(B, B);
	gamma(G, G);
	gamma(R, R);

#ifdef SHOWRGB
	imshow("red", R);
	imshow("green", G);
	imshow("blue", R);
#endif

	merge(channels, srcMat);
	imshow("mergeMat", srcMat);
	waitKey(0);

	return;
}

int main(int argc, char* argv[]) {

	Mat srcMat = imread("C:\\Users\\Daniel\\Desktop\\zft2.jpg");
	imshow("srcMat", srcMat);
	Mat dstMat = srcMat.clone();

	namedWindow(WINDOW_NAME, 1);
	char TrackbarName[16];
	sprintf_s(TrackbarName, "g_gm=%d", g_gm);

	createTrackbar(TrackbarName,WINDOW_NAME,&g_gm,100,threeChannelsGamma,(void*)&dstMat);

	waitKey(0);
	return 0;
}

#endif