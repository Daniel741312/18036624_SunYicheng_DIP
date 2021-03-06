#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
/*读取摄像头图像,并对摄像头图像进行均值滤波*/

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
				blur(srcFrame, dstFrame, Size(5, 5),Point(-1, -1), BORDER_DEFAULT);
				imshow("srcFrame", srcFrame);
				imshow("dstFrame", dstFrame);
			}
			waitKey(5);
		}
		return 0;
}
#endif
