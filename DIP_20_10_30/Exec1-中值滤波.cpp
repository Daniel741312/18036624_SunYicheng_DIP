#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;
/*读取摄像头图像,并对摄像头图像进行中值滤波-实现了磨皮效果*/

#if 0
int main(int argc, char* argv[]) {
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
			Mat srcFrame;
			Mat dstFrame;
			bool rSucess = cap.read(srcFrame);
			if (!rSucess) {
				std::cout << "Read Error" << std::endl;
				break;
			}
			else {
				medianBlur(srcFrame, dstFrame, 7);
				imshow("srcFrame", srcFrame);
				imshow("dstFrame", dstFrame);
			}
			waitKey(5);
		}
		return 0;
}
#endif
