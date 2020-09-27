#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<fstream>
using namespace cv;
/*直方图的显示和计算*/

#if 0
int main(){
	unsigned int histgram[256] = { 0 };
	int cntMax = 0;						//像素值0-255最多的像素点的个数,用于直方图的归一化
	int i = 0;
	int j = 0;
	int k = 0;

	Mat M1 = imread("C:\\Users\\18798\\Desktop\\lena.jpg",0);
	int height_M1 = M1.rows;			//行数
	int width_M1= M1.cols;				//每行元素的总数量

	imshow("灰度图", M1);

	/*遍历Mat,统计各pixel的值的情况,存入histgram数组中*/
	for (j = 0; j < height_M1; j++) {
		uchar* data = M1.ptr<uchar>(j);	//第j行头的地址
		for (i = 0; i < width_M1; i++) {
			histgram[(unsigned int)data[i]]++;
		}
	}

	/*遍历一下histgram,找出最大的出现次数:cntMax*/
	cntMax = histgram[0];
	for (i = 1; i < 255; i++) {
		if (histgram[i] > cntMax)
			cntMax = histgram[i];
	}

	/*绘制直方图*/
	Point pt1;
	Point pt2;
	Mat histgramMat = Mat(1080,1920,CV_8UC3, Scalar(255, 0, 0));
	for (k = 0; k <255; k++){
		pt1.x = k*2;					//线段起点
		pt1.y = 1000;
		pt2.x = k*2;					//线段终点
		pt2.y = 1000-histgram[k]/(float)cntMax*1000;
		line(histgramMat, pt1, pt2, CV_RGB(255, 255, 0), 2, 8, 0);
	}
	imshow("histgramMat", histgramMat);

	waitKey(0);
	return 0;
}
#endif
