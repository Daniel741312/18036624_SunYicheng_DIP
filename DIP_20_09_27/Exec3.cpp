#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;

/*绘图*/
#if 0
int main() {
	int w = 500;
	int h=500;
	/*注意创建Mat时要初始化相关属性*/
	Mat dispMat_circle=Mat(500,500,CV_8UC3,Scalar(0,0,255));
	Mat dispMat_line=Mat(500,500,CV_8UC3,Scalar(0,0,255));
	Mat dispMat_rectangle=Mat(500,500,CV_8UC3,Scalar(0,0,255));

	Point pt;
	pt.x = 100;
	pt.y = 100;
	circle(dispMat_circle, pt, 50, CV_RGB(0,255,0), 1, 8, 0);
	imshow("circle", dispMat_circle);

	Point pt1;
	pt1.x = 150;
	pt1.y = 150;
	Point pt2;
	pt2.x = 350;
	pt2.y = 350;
	line(dispMat_line, pt1, pt2, CV_RGB(0,255, 0), 1, 8, 0);
	imshow("lins", dispMat_line);

	Rect rect;
	rect.x = 20;
	rect.y = 30;
	rect.width = 100;
	rect.height= 100;
	rectangle(dispMat_rectangle, rect, CV_RGB(0, 255, 0), 1, 8, 0);
	imshow("rect", dispMat_rectangle);

	waitKey(0);

	return 0;
}
#endif
