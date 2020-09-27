#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include"rgb2bin.h"
using namespace cv;

/*���ñ�������ͷ,���Զ�ÿһ֡���д���*/
#if 1
int main() {
	VideoCapture cap;
	cap.open(0);

	/*����Ƿ�򿪳ɹ�*/
	if (!cap.isOpened()) {
		std::cout << "Open Error" << std::endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps=" << fps << std::endl;

	/*��ѭ��,���ϵ�ˢ����ʾ��,����ʵʱ��ʾ*/
	while (1) {
		Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess) {
			std::cout << "Read Error" << std::endl;
			break;
		}
		else {
			/*�ѵ�һ�ڿεĶ�ֵ����ϰ��װ�ɺ���,ʵʱ����ÿһ֡*/
			frame = rgb2bin(frame,50);
			imshow("frame", frame);
		}
		waitKey(5);
	}
	return 0;
}
#endif