#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	float histgram[256];
	Mat M1 = imread("C:\\Users\\18798\\Desktop\\lena.jpg");
	int height_M3 = M3.rows;					//����
	int width_M3 = M3.cols * M3.channels();		//ÿ��Ԫ�ص�������
	for (int j = 0; j < height; j++) {
		uchar* data = M3.ptr<uchar>(j);			//��j��ͷ�ĵ�ַ
		for (int i = 0; i < width; i++) {
			data[i] = data[i] / 2;
		}
	}



	waitKey(0);
	return 0;
}
