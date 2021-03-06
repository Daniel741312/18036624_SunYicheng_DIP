#if 0
/*
	Duncan-8000;
	Yao-1000;
	componnent-1500;
	程序存在的问题:
		1.对不同的问题实例,函数MyMatchTemplate中minDis低于一定阈值后break出循环返回时,对阈值的敏感性太高.
		要反复调节,否则只能等循环全部跑完才能返回;
		2.函数calcHOG和distance性能太差,计算太慢;
*/

#include<iostream>
#include<vector>
#include<cstdlib>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define POW 1

/*计算输入图片的HOG*/
int calcHOG(Mat& srclMat, float* hist, int nAngle, int blockSize);
/*计算两个list的距离*/
float distance(float* hist1, float* hist2, int bins);
/*计算两张图片在HOG视角下的相似度,值越小越相似*/
float calcSimilarityInHOG(Mat& img1, Mat& img2);
/*测试calcSimilarityInHOG*/
void test();
/*进行模板匹配*/
void MyMatchTemplate(Mat& baseMat, Mat& templateMat, Point& location);

int main(int argc, char* argv[]) {
	/*底板图*/
	Mat baseMatRGB = imread("./NBA0.jpg");
	Mat baseMat;
	cvtColor(baseMatRGB, baseMat, COLOR_BGR2GRAY);

	/*模板图*/
	Mat templateMat = imread("./Yao0.png");
	cvtColor(templateMat, templateMat, COLOR_BGR2GRAY);

	/*Distance最小的那个点*/
	Point location = Point(0, 0);
	MyMatchTemplate(baseMat, templateMat, location);

	/*测试一些图的HOG距离*/
	//test();

	/*根据模板匹配函数传出的location将模板图像用矩形画出来*/
	rectangle(baseMatRGB, location, Point(location.x + templateMat.cols, location.y + templateMat.rows), Scalar(0, 0, 255), 2, 8, 0);

	imshow("baseMatRGB", baseMatRGB);
	waitKey(0);
	return 0;
}

int calcHOG(Mat& src, float* hist, int nAngle, int cellSize) {
	Mat gx, gy;
	Mat mag, angle;
	/*求梯度*/
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	/*转化到极坐标*/
	cartToPolar(gx, gy, mag, angle, true);
	/*切割矩形*/
	Rect roi;
	roi.height = cellSize;
	roi.width = cellSize;

	int nX = src.cols / cellSize;
	int nY = src.rows / cellSize;

	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			Mat roiMat, roiMag, roiAgl;
			roi.x = j * cellSize;
			roi.y = i * cellSize;
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			int head = (i * nX + j) * nAngle;
			for (int n = 0; n < roiMat.rows; n++) {
				for (int m = 0; m < roiMat.cols; m++) {
					/*角度归类*/
					hist[head + (int)roiAgl.at<float>(n, m) / (360 / nAngle)] += roiMag.at<float>(n, m);
				}
			}
		}
	}
	return 0;
}

float distance(float* hist1, float* hist2, int bins) {
	int i = 0;
	float ret = 0;
	/*根据宏POW的不同选择不同的距离计算方式(第二种只要绝对值,算不上距离)*/
	if (POW) {
		for (i = 0; i < bins; ++i)
			ret = ret + ((*(hist1 + i)) - (*(hist2 + i))) * ((*(hist1 + i)) - (*(hist2 + i)));
			
		ret = sqrt(ret);
	}
	else {
		for (i = 0; i < bins; ++i)
			ret = ret + abs((hist1[i] - hist2[i]));
	}

	return ret;
}

float calcSimilarityInHOG(Mat& img1, Mat& img2) {
	int nAngle = 8;
	int cellSize = 9;
	int nX = img1.cols/cellSize;
	int nY = img1.rows/cellSize;
	int bins = nX * nY * nAngle;

	float dis = 0;

	/*动态的申请两个float数组,并初始化*/
	float* img1Hist = (float*)malloc(sizeof(float) * bins);
	float* img2Hist = (float*)malloc(sizeof(float) * bins);
	if (!img1Hist || !img2Hist) {
		exit(-1);
	}
	else {
		memset(img1Hist, 0, sizeof(float) * bins);
		memset(img2Hist, 0, sizeof(float) * bins);
	}

	/*算出HOG直方图*/
	calcHOG(img1, img1Hist, nAngle, cellSize);
	calcHOG(img2, img2Hist, nAngle, cellSize);

	/*算出两个数组之间的距离*/
	dis = distance(img1Hist, img2Hist, bins);

	/*归还空间*/
	free(img1Hist);
	free(img2Hist);
	return dis;
}

void test() {
	Mat img0 = imread("./Yao0.png");
	Mat img1 = imread("./Yao1.png");
	Mat img2 = imread("./Yao2.png");
	Mat img3 = imread("./Yao3.png");
	Mat img4 = imread("./Yao4.png");
	Mat img5 = imread("./Yao5.png");
	Mat img6 = imread("./Yao6.png");
	Mat img7 = imread("./Yao7.png");
	Mat img8 = imread("./Yao8.png");
	Mat img9 = imread("./Yao9.png");

	cvtColor(img0, img0, COLOR_BGR2GRAY);
	cvtColor(img1, img1, COLOR_BGR2GRAY);
	cvtColor(img2, img2, COLOR_BGR2GRAY);
	cvtColor(img3, img3, COLOR_BGR2GRAY);
	cvtColor(img4, img4, COLOR_BGR2GRAY);
	cvtColor(img5, img5, COLOR_BGR2GRAY);
	cvtColor(img6, img6, COLOR_BGR2GRAY);
	cvtColor(img7, img7, COLOR_BGR2GRAY);
	cvtColor(img8, img8, COLOR_BGR2GRAY);
	cvtColor(img9, img9, COLOR_BGR2GRAY);

	cout << calcSimilarityInHOG(img0, img0) << endl;
	cout << calcSimilarityInHOG(img0, img1) << endl;
	cout << calcSimilarityInHOG(img0, img2) << endl;
	cout << calcSimilarityInHOG(img0, img3) << endl;
	cout << calcSimilarityInHOG(img0, img4) << endl;
	cout << calcSimilarityInHOG(img0, img5) << endl;
	cout << calcSimilarityInHOG(img0, img6) << endl;
	cout << calcSimilarityInHOG(img0, img7) << endl;
	cout << calcSimilarityInHOG(img0, img8) << endl;
	cout << calcSimilarityInHOG(img0, img9) << endl;

	waitKey(0);
	return;
}

void MyMatchTemplate(Mat& baseMat, Mat& templateMat, Point& location) {
	int i = 0;
	int j = 0;
	int templateWidth = templateMat.cols;
	int templateHeight= templateMat.rows;

	Mat imageROI;
	float dis = 0;
	float minDis = 10000;

	for (i = 0; i < baseMat.rows-templateHeight; i++) {
		//uchar* data = baseMat.ptr<uchar>(i);
		//cout << "i=" << i << endl;
		for (j = 0; j < baseMat.cols-templateWidth; j++) {
			imageROI = baseMat(Rect(j, i, templateWidth, templateHeight));
			cout << "[" << i << "," << j << "]" << endl;
			dis = calcSimilarityInHOG(templateMat, imageROI);
			if (dis <= minDis) {
				minDis = dis;
				location.x = j;
				location.y = i;
				if (minDis <= 1500)
					return;
			}
		}
	}
	return;
}

#endif