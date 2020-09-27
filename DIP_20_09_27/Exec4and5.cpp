#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<fstream>
using namespace cv;
/*ֱ��ͼ����ʾ�ͼ���*/

#if 0
int main(){
	unsigned int histgram[256] = { 0 };
	int cntMax = 0;						//����ֵ0-255�������ص�ĸ���,����ֱ��ͼ�Ĺ�һ��
	int i = 0;
	int j = 0;
	int k = 0;

	Mat M1 = imread("C:\\Users\\18798\\Desktop\\lena.jpg",0);
	int height_M1 = M1.rows;			//����
	int width_M1= M1.cols;				//ÿ��Ԫ�ص�������

	imshow("�Ҷ�ͼ", M1);

	/*����Mat,ͳ�Ƹ�pixel��ֵ�����,����histgram������*/
	for (j = 0; j < height_M1; j++) {
		uchar* data = M1.ptr<uchar>(j);	//��j��ͷ�ĵ�ַ
		for (i = 0; i < width_M1; i++) {
			histgram[(unsigned int)data[i]]++;
		}
	}

	/*����һ��histgram,�ҳ����ĳ��ִ���:cntMax*/
	cntMax = histgram[0];
	for (i = 1; i < 255; i++) {
		if (histgram[i] > cntMax)
			cntMax = histgram[i];
	}

	/*����ֱ��ͼ*/
	Point pt1;
	Point pt2;
	Mat histgramMat = Mat(1080,1920,CV_8UC3, Scalar(255, 0, 0));
	for (k = 0; k <255; k++){
		pt1.x = k*2;					//�߶����
		pt1.y = 1000;
		pt2.x = k*2;					//�߶��յ�
		pt2.y = 1000-histgram[k]/(float)cntMax*1000;
		line(histgramMat, pt1, pt2, CV_RGB(255, 255, 0), 2, 8, 0);
	}
	imshow("histgramMat", histgramMat);

	waitKey(0);
	return 0;
}
#endif
