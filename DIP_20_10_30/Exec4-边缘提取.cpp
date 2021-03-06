#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 0
int main(int argc, char* argv[]) {
	VideoCapture cap;
	cap.open(0);

	int ksize = 3;
	double scale = 1;
	double delta = 0;

	/*检查是否打开成功*/
	if (!cap.isOpened()) {
		std::cout << "Open Error" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps=" << fps << std::endl;

	/*死循环,不断的刷新显示框,做到实时显示*/
	while (1) {
		Mat srcFrame;
		Mat dstFrameDx;
		Mat dstFrameDy;
		bool rSucess = cap.read(srcFrame);
		if (!rSucess) {
			std::cout << "Read Error" << std::endl;
			break;
		}
		else {
			Sobel(srcFrame, dstFrameDx, -1, 1, 0, 3);
			Sobel(srcFrame, dstFrameDy, -1, 0, 1, 3);
			imshow("srcFrame", srcFrame);
			imshow("dstFrameDx", dstFrameDx);
			imshow("dstFrameDy", dstFrameDy);
		}
		waitKey(5);
	}
	return 0;
}
#endif
