#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 0
int main() {
	int j = 0;
	int i = 0;

	/*读入Mat格式数据,imread指明路径,注意Windows下的路径格式*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\lena.jpg");
	/*行数和列数两个属性*/
	int height = srcMat.rows;
	int weight= srcMat.cols;

	/*对srcMat.at<Vec3b(j,i)[0]的解读:
	*通道数放在最后;
	* 括号中(j,i)指明<Vec3b>的位置;
	*/
	for (j = 0; j < height; j++) {
		for (i = 0; i < weight; i++) {
			uchar aver = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			srcMat.at<Vec3b>(j, i)[0] = aver;
			srcMat.at<Vec3b>(j, i)[1] = aver;
			srcMat.at<Vec3b>(j, i)[2] = aver;
		}
	}
	imshow("Exec1-取三个通道平均值逐一赋给每个像素点", srcMat);
	waitKey(0);
	return 0;
}
#endif