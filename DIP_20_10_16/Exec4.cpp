#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

#if 1
int main() {
	/*用大津法对原图二值化*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\huixingzhen.jpg", 0);
	Mat binMat;
	threshold(srcMat, binMat, 100, 255, THRESH_OTSU);
	//imshow("srcBinMat", binMat);

	int g_nStructElementSize = 3; //结构元素(内核矩阵)的尺寸
	Mat kernel = getStructuringElement(MORPH_RECT, Size(g_nStructElementSize, g_nStructElementSize));

#if 0
	/*膨胀*/
	Mat dilateMat;
	morphologyEx(binMat, dilateMat, MORPH_DILATE, kernel, Point(-1, -1), 1, BORDER_CONSTANT);
	imshow("dilateMat", dilateMat);
#endif

	/*闭运算*/
	Mat closeMat;
	morphologyEx(binMat, closeMat, MORPH_CLOSE, kernel, Point(-1, -1), 1, BORDER_CONSTANT);
	imshow("closeMat", closeMat);
	/*二值图反色一下,交换前景和背景,便于后面的连通域标记*/
	bitwise_not(closeMat, closeMat);

	/*连通域标记*/
	Mat labels, stats, centroids;
	int num = 0;
	num = connectedComponentsWithStats(closeMat, labels, stats, centroids, 4, CV_32S);
	
	/*左边的黑边会被当做一个连通域,所以下面-2,或者将原图的黑边抹去*/
	std::cout << "回形针个数为" << std::endl;
	std::cout << num - 2 << std::endl;

	waitKey(0);
	return 0;
}
#endif
