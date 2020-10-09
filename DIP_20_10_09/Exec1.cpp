#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#if 0
int main() {
	VideoCapture cap(0);

	double scale = 0.5;

	//0-180,肤色
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

		//原始的帧图像
		cap >> frame;

		//缩放
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		//转换一下不同的色彩空间
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

		//复制一份到detectMat
		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		//阴间效果
		imshow("while:in the range", detectMat);
		//原图
		imshow("frame", rFrame);

		waitKey(30);
	}
	return 0;
}
#endif

