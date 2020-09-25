#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	int i = 0;
	int j = 0;
	uchar threhold = 100;

	Mat srcM = imread("C:\\Users\\18798\\Desktop\\lena.jpg");
	imshow("ԭ����srcM", srcM);
	int weight = srcM.cols;
	int height = srcM.rows;

	Mat deepMat;
	Mat shallowMat;

	srcM.copyTo(deepMat);			//���,new��һ�����ڴ�,�������
	shallowMat = srcM;				//ǳ����,ֻ��һ��������,��new�ڴ�

	for (j = 0; j < height; j++) {
		for (i = 0; i < weight; i++) {
			uchar aver = srcM.at<Vec3b>(j, i)[0] + srcM.at<Vec3b>(j, i)[1] + srcM.at<Vec3b>(j, i)[2]/3;
			aver = aver > threhold ? 255 : 0;
			srcM.at<Vec3b>(j, i)[0] = aver;
			srcM.at<Vec3b>(j, i)[1] = aver;
			srcM.at<Vec3b>(j, i)[2] = aver;
		}
	}

	imshow("����ֵ����srcM", srcM);
	imshow("deepMat",deepMat);
	imshow("shallowMat",shallowMat);

	waitKey(0);
	return 0;
}
