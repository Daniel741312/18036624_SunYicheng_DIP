#include<iostream>
#include"rgb2bin.h"
#include<opencv2/opencv.hpp>
using namespace cv;
/*图像形态学:腐蚀,膨胀,开运算,闭运算*/
#if 0
int main() {
	/*得到二值化图像*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\yingbi.jpg", 0);
	Mat binMat;
	threshold(srcMat, binMat, 100, 255, THRESH_BINARY);
	imshow("binMat", binMat);

	/*产生kernel*/
	int g_nStructElementSize = 5; //结构元素(内核矩阵)的尺寸
	Mat kernel = getStructuringElement(MORPH_RECT, Size(g_nStructElementSize, g_nStructElementSize));

	/*腐蚀*/
	Mat erodeMat;
	morphologyEx(binMat, erodeMat, MORPH_ERODE, kernel, Point(-1, -1),1,BORDER_CONSTANT);
	imshow("erodeMat", erodeMat);

	/*膨胀*/
	Mat dilateMat;
	morphologyEx(binMat, dilateMat, MORPH_DILATE, kernel, Point(-1, -1),1,BORDER_CONSTANT);
	imshow("dilateMat",dilateMat);

	/*开运算*/
	Mat openMat;
	morphologyEx(binMat, openMat, MORPH_OPEN, kernel, Point(-1, -1),1,BORDER_CONSTANT);
	imshow("openMat", openMat);

	/*闭运算*/
	Mat closeMat;
	morphologyEx(binMat, closeMat, MORPH_CLOSE, kernel, Point(-1, -1),1,BORDER_CONSTANT);
	imshow("closeMat", closeMat);


	waitKey(0);
	return 0;
}
#endif
