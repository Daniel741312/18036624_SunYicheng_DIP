#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
/*连通域标记*/

#if 0
int main() {
	/*得到二值化图像*/
	Mat srcMat = imread("C:\\Users\\18798\\Desktop\\yingbi.jpg", 0);
	Mat binMat;
	threshold(srcMat, binMat, 100, 255, THRESH_BINARY);
	imshow("srcBinMat", binMat);

	/*连通域标记*/
	Mat labels, stats, centroids;
	int num = 0;
	num = connectedComponentsWithStats(binMat,labels,stats,centroids,8,CV_32S);

	/*输出连通域中心矩阵*/
	std::cout << "中心矩阵" << std::endl;
	std::cout << centroids << std::endl;
	std::cout << std::endl;

	/*输出状态矩阵*/
	std::cout << "状态矩阵" << std::endl;
	std::cout << stats << std::endl;
	std::cout << std::endl;

	std::cout << "硬币个数为" << std::endl;
	std::cout << stats.rows-1<< std::endl;

	/*用状态矩阵stats标记矩形*/
	int h = 0;
	int w = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;

	/*h=0是背景连通域,跳过*/
	for (int h = 1; h < stats.rows; ++h)
	{
		/*参数归零,处理下一个矩形*/
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		/*遍历这一行*/
		for (int w = 0; w < stats.cols; ++w)
		{
			/*case语句给每一个参数赋值*/
			switch (w) {
				case(0):
					x=stats.at<int>(h, w);
					break;
				case(1):
					y=stats.at<int>(h, w);
					break;
				case(2):
					width=stats.at<int>(h, w);
					break;
				case(3):
					height=stats.at<int>(h, w);
					break;
				default:
					break;
			}
		}
		/*在原图画出这个矩形*/
		rectangle(binMat, Point(x,y), Point(x+width,y+height), Scalar(255,255,255), 2, 4, 0);
	}
	imshow("rectBinMat", binMat);
	waitKey(0);
	return 0;
}
#endif
