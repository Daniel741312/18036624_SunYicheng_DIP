#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace cv;
using namespace std;

#if 0
int main(int argc, char* argv[]) {
	int i = 0;
	int j = 0;
	float width = 0;
	float height = 0;
	float ratio = 0;

	/*以单通道的方式读入一张原图*/
	Mat srcMat = imread("C:/Users/Daniel/Desktop/xinpian.jpg",0);
	imshow("srcMat1", srcMat);
	/*再以三通道的方式读入,存入dstMat作为绘制的背景*/
	Mat dstMat= imread("C:/Users/Daniel/Desktop/xinpian.jpg");
	/*二值化的图像*/
	Mat binMat;
	/*开运算后的结果*/
	Mat openMat;

	/*二值化*/
	threshold(srcMat, binMat, 100, 255, THRESH_OTSU);
	imshow("binMat", binMat);

	/*进行一下开运算,消除白色细线的干扰*/
	int g_nStructElementSize = 3; //结构元素(内核矩阵)的尺寸
	Mat kernel = getStructuringElement(MORPH_RECT, Size(g_nStructElementSize, g_nStructElementSize));
	morphologyEx(binMat, openMat, MORPH_OPEN, kernel, Point(-1, -1), 1, BORDER_CONSTANT);
	imshow("openMat", openMat);

	/*寻找边缘点,存入contours中*/
	vector<vector<Point>> contours;
	findContours(openMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	/*绘制外接矩形*/
	for (i =60; i>0; --i) {
		RotatedRect rbox = minAreaRect(contours[i]);
		width = rbox.size.width;
		height = rbox.size.height;
		ratio = width / height;
		/*条件筛选*/
		if (ratio < 1.5 && ratio>0.5) {
			drawContours(dstMat, contours, i, Scalar(0, 0, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			/*手动画矩形*/
			for (j = 0; j < 4; ++j)
				line(dstMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0,255,0), 2, CV_AA);
			/*有一个小的矩形一直干扰,所以画完大的矩形之后就跑,break出来*/
			break;
		}
	}
	imshow("dstMat", dstMat);
	waitKey(0);
	return 0;
}
#endif
