#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 1
int main() {
	/*�ô�򷨶�ԭͼ��ֵ��*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\huixingzhen.jpg", 0);
	Mat binMat;
	threshold(srcMat, binMat, 100, 255, THRESH_OTSU);
	//imshow("srcBinMat", binMat);

	int g_nStructElementSize = 3; //�ṹԪ��(�ں˾���)�ĳߴ�
	Mat kernel = getStructuringElement(MORPH_RECT, Size(g_nStructElementSize, g_nStructElementSize));

#if 0
	/*����*/
	Mat dilateMat;
	morphologyEx(binMat, dilateMat, MORPH_DILATE, kernel, Point(-1, -1), 1, BORDER_CONSTANT);
	imshow("dilateMat", dilateMat);
#endif

	/*������*/
	Mat closeMat;
	morphologyEx(binMat, closeMat, MORPH_CLOSE, kernel, Point(-1, -1), 1, BORDER_CONSTANT);
	imshow("closeMat", closeMat);
	/*��ֵͼ��ɫһ��,����ǰ���ͱ���,���ں������ͨ����*/
	bitwise_not(closeMat, closeMat);

	/*��ͨ����*/
	Mat labels, stats, centroids;
	int num = 0;
	num = connectedComponentsWithStats(closeMat, labels, stats, centroids, 4, CV_32S);
	
	/*��ߵĺڱ߻ᱻ����һ����ͨ��,��������-2,���߽�ԭͼ�ĺڱ�Ĩȥ*/
	std::cout << "���������Ϊ" << std::endl;
	std::cout << num - 2 << std::endl;

	waitKey(0);
	return 0;
}
#endif