#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include"rgb2bin.h"
using namespace cv;

/*调用本机摄像头,可以对每一帧进行处理*/
#if 1
int main() {
	VideoCapture cap;
	cap.open(0);

	/*检查是否打开成功*/
	if (!cap.isOpened()) {
		std::cout << "Open Error" << std::endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps=" << fps << std::endl;

	/*死循环,不断的刷新显示框,做到实时显示*/
	while (1) {
		Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess) {
			std::cout << "Read Error" << std::endl;
			break;
		}
		else {
			/*把第一节课的二值化练习封装成函数,实时处理每一帧*/
			frame = rgb2bin(frame,50);
			imshow("frame", frame);
		}
		waitKey(5);
	}
	return 0;
}
#endif