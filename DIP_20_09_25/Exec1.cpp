#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 0
int main() {
	int j = 0;
	int i = 0;

	/*����Mat��ʽ����,imreadָ��·��,ע��Windows�µ�·����ʽ*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\lena.jpg");
	/*������������������*/
	int height = srcMat.rows;
	int weight= srcMat.cols;

	/*��srcMat.at<Vec3b(j,i)[0]�Ľ��:
	*ͨ�����������;
	* ������(j,i)ָ��<Vec3b>��λ��;
	*/
	for (j = 0; j < height; j++) {
		for (i = 0; i < weight; i++) {
			uchar aver = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			srcMat.at<Vec3b>(j, i)[0] = aver;
			srcMat.at<Vec3b>(j, i)[1] = aver;
			srcMat.at<Vec3b>(j, i)[2] = aver;
		}
	}
	imshow("Exec1-ȡ����ͨ��ƽ��ֵ��һ����ÿ�����ص�", srcMat);
	waitKey(0);
	return 0;
}
#endif