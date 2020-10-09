#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#if 0
int main() {
	VideoCapture cap(0);

	double scale = 0.5;

	//0-180,��ɫ
	double i_minH = 0;
	double i_maxH = 20;

	//0-255
	double i_minS = 43;
	double i_maxS = 255;

	//0-255
	double i_minV = 55;
	double i_maxV = 255;

	while (1) {
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		//ԭʼ��֡ͼ��
		cap >> frame;

		//����
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		//ת��һ�²�ͬ��ɫ�ʿռ�
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

		//����һ�ݵ�detectMat
		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		//����Ч��
		imshow("while:in the range", detectMat);
		//ԭͼ
		imshow("frame", rFrame);

		waitKey(30);
	}
	return 0;
}
#endif

