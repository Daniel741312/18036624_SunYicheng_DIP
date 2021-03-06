#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<Windows.h>
using namespace cv;

#if 1
int main(int argc, char* argv[]) {
	Mat dstMat;
	Mat srcMat = imread("C:\\Users\\Daniel\\Desktop\\lena_lean.jpg");
	/*读一张灰度图,用于找那三个点,彩图太麻烦*/
	Mat srcMatGray = imread("C:\\Users\\Daniel\\Desktop\\lena_lean.jpg",0);
	//imshow("gray", srcMatGray);
	//waitKey(0);
	int weight = srcMat.rows;
	int height = srcMat.cols;
	uchar aver = 0;

	/*错误检查*/
	if (srcMat.empty()) {
		std::cout << "打开失败" << std::endl;
		return -1;
	}

	/*这是倾斜图中的三个点,下面会用三个过程找到这三个点*/
	Point pt1_1, pt1_2, pt1_3;

	/*这是修正后的三个点,分别初始化为左上角,左下角和右下角*/
	Point pt2_1, pt2_2, pt2_3;
	pt2_1 = Point(0, 0);
	pt2_2 = Point(0,srcMat.rows - 1);
	pt2_3 = Point(weight-1,height-1);

	int i = 0;
	/*灰度阈值*/
	uchar a = 127;

	/*遍历第一行像素*/
	for (i = 0; i < weight; ++i) {
		//uchar* ptr = image.ptr<uchar>(row_index);
		//uchar* ptr = srcMatGray.ptr<uchar>(0);
		/*这个at函数好像是以图片右下角为坐标原点,因为这么做的话会正确*/
		aver = srcMatGray.at<uchar>(i,height-1);
		if (aver < a) {
			pt1_1 = Point(i,0);
			break;
		}
	}
	//pt1_1 = Point(43,0);

	/*遍历第一列像素,if判断中的阈值用原来的不行,试了试250可以,当然考虑通用性应该小一点更好*/
	for (i = 0; i < height; ++i) {
		aver = srcMatGray.at<uchar>(0,i);
		if (aver<250) {
			pt1_2 = Point(0,height-i);
			break;
		}
	}
	//pt1_2=(0,274)

	/*遍历最后一行像素*/
	for (i = 0; i < weight; ++i) {
		//uchar* ptr = srcMatGray.ptr<uchar>(height-1);
		aver = srcMatGray.at<uchar>(i,0);
		if (aver < a) {
			pt1_3 = Point(i,height-1);
			break;
		}
	}
	//pt1_3=(270,315)

	const Point2f src_pt[] = {pt1_1,pt1_2,pt1_3};
	const Point2f dst_pt[] = {pt2_1,pt2_2,pt2_3};

	/*得到变换矩阵*/
	Mat affine_matrix = getAffineTransform(src_pt, dst_pt);

	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
}
#endif
