#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 0
int main() {
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened()) {
		std::cout << "Open Error" << std::endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps=" << fps << std::endl;

	while (1) {
		Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess) {
			std::cout << "Read Error" << std::endl;
			break;
		}
		else {
			imshow("frame", frame);
		}
		waitKey(5);
	}
	return 0;
}
#endif