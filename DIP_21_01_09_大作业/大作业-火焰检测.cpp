#if 1
/*视频尺寸:480x268*/
/*喷口位置:174x34*/

#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

typedef enum {
	RGB,
	GRAY,
	HSV
}FRAME_TYPE;

/*找到用于拟合抛物线的三个点*/
void find3Points(Mat& frame,vector<Point>* parameter);
/*根据find3Pointers找到的三个点在frame上画出抛物线*/
void drawParabola(Mat& frame, const vector<Point>* parameter);
/*检测火焰*/
void CheckColor(Mat& inImg);
/*为ChechColor函数服务的,绘制火焰的边框*/
void DrawFire(Mat& inputImg, Mat foreImg);
/*(准备工作用的)获取start到end帧的图片到./frame目录*/
void getSomeFrame(int start,int end,int frame_type);

int main(int argc, char* argv[]) {
	/*保存3个用于拟合抛物线的三个点*/
	vector<Point>* parameter=new vector<Point>;
	/*
		*喷口位置:
		*在ROI中的坐标,由于图像二值化之后会有很多前景区域,如窗户和地面等,无法很好的提取出水柱,
		*所以只取喷口下方的一块区域作为ROI,在其中寻找水柱并找到三个点;
		*所以这个喷口位置是相对于ROI的坐标
	*/
	(*parameter).push_back(Point(76, 0));
	(*parameter).push_back(Point(0, 0));
	(*parameter).push_back(Point(0, 0));

	VideoCapture srcVideo;
	srcVideo.open("./3.mp4");

	size_t i = 0;
	Mat frame;
	char fileName[30] = "./dstFrame";

	while (1) {
		srcVideo >> frame;
		if (frame.empty())
			break;
		/*找到火焰*/
		CheckColor(frame);
		/*找到用于拟合抛物线的三个点*/
		find3Points(frame, parameter);
		/*绘制出抛物线*/
		drawParabola(frame, parameter);
		imshow("dst1", frame);

		sprintf_s(fileName, "./dstFrame/%03d.jpg", i++);
		imwrite(fileName, frame);

		waitKey(30);
	}

	/*释放内存*/
	delete parameter;
	waitKey(0);
	return 0;
}

/*找到用于拟合抛物线的三个点*/
void find3Points(Mat& frame,vector<Point>* parameter) {

	(*parameter)[0] = Point(76, 0);
	(*parameter)[1] = Point(0, 0);
	(*parameter)[2] = Point(0, 0);

	int cnt = 1;
	int i = 0;
	int j = 0;
	/*在帧图像中选择ROI*/
	Mat frameROI= frame(Rect(106, 36, 165, 41));
	/*二值化*/
	cvtColor(frameROI, frameROI, COLOR_BGR2GRAY);
	dilate(frameROI, frameROI, Mat(4,4,CV_8UC1));
	threshold(frameROI, frameROI, 200, 255, 0);
	/*保存下来*/
	imwrite("frameROI.jpg", frameROI);

	for (i = frameROI.rows - 1; i > 0; i =i/2) {
		for (j = frameROI.cols - 1; j > 0; j--) {
			/*从下向上,从右向左,遇到白色认为是水柱*/
			if (frameROI.at<uchar>(i, j) == 255) {
				(*parameter)[cnt++] = Point(j, i);
				break;
			}
		}
		/*找到三个点就break*/
		if (cnt==3)
			break;
	}

	/*将相对于ROI的坐标变成相对于整个图像的坐标*/
	for (i = 0; i < 3; i++) {
		(*parameter)[i].y += 35;
		(*parameter)[i].x += 100;
	}

	return;
}

/*根据find3Pointers找到的三个点在frame上画出抛物线*/
void drawParabola(Mat& frame,const vector<Point>* parameter) {
	int x0 = (*parameter)[0].x;
	int x1 = (*parameter)[1].x;
	int x2 = (*parameter)[2].x;

	int y0 = (*parameter)[0].y;
	int y1 = (*parameter)[1].y;
	int y2 = (*parameter)[2].y;

	/*抄来的函数,具体我也不懂,应该是根据一个自变量和矩阵和一个因变量的矩阵计算出多项式的参数*/
	float A[3][3] = { {x0 * x0, x0, 1}, {x1 * x1, x1, 1}, {x2 * x2, x2, 1} };
	float B[3] = { y0, y1,y2 };
	float C[3] = { 0, 0, 0 };

	size_t i=0;
	CvMat* matA = cvCreateMat(3, 3, CV_32FC1);
	CvMat* matB = cvCreateMat(3, 1, CV_32FC1);

	CvMat* matC = cvCreateMat(3, 1, CV_32FC1);

	cvSetData(matA, A, CV_AUTOSTEP);
	cvSetData(matB, B, CV_AUTOSTEP);
	/*核心函数,二次曲线的参数存到了matC里*/
	cvSolve(matA, matB, matC, CV_LU);

	int result=0;

	for (i = 0; i < frame.cols; i++) {
		/*根据上面求出来的参数算出点的坐标*/
		result = (int)(i * i * matC->data.fl[0]) + i * matC->data.fl[1] + matC->data.fl[2];
		if (result < frame.rows) {
			/*画上去*/
			circle(frame, cvPoint(i, result), 2, Scalar(164, 73, 163), -1);
		}
	}
}

void CheckColor(Mat& inImg) {
	Mat fireImg;
	fireImg.create(inImg.size(), CV_8UC1);
	Mat multiRGB[3];
	int a = inImg.channels();
	split(inImg, multiRGB);

	for (int i = 0; i < inImg.rows; i++) {
		for (int j = 0; j < inImg.cols; j++) {
			float B, G, R;
			B = multiRGB[0].at<uchar>(i, j);
			G = multiRGB[1].at<uchar>(i, j);
			R = multiRGB[2].at<uchar>(i, j);
			/*认为橘色部分为火焰:橘色的特征:红色分量远高于绿色和蓝色分量,绿色分量也高于蓝色分量*/
			if ((R - B) >= 80 && (R - G) >= 50 && (G - B) >= 25) {
				/*火焰部分标记为白色*/
				fireImg.at<uchar>(i, j) = 255;
			}
			else {
				fireImg.at<uchar>(i, j) = 0;
			}
		}
	}

	medianBlur(fireImg, fireImg, 5);
	/*腐蚀去掉一些噪点*/
	erode(fireImg, fireImg, Mat(3, 3, CV_8UC1));
	/*膨胀扩大范围*/
	dilate(fireImg, fireImg, Mat(4, 4, CV_8UC1));
	/*绘制出上面的这个二值图*/
	imshow("Binary", fireImg);
	/*绘制矩形轮廓*/
	DrawFire(inImg, fireImg);
}

/*绘制矩形轮廓:
	传入参数:原彩图和标记的二值图
*/
void DrawFire(Mat& inputImg, Mat foreImg) {

	/*保存轮廓提取后的点集及拓扑关系*/
	vector<vector<Point>> contours_set;
	findContours(foreImg, contours_set, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	Point point1;
	Point point2;
	float a = 0.4, b = 0.75;
	float xmin1 = a * inputImg.cols, ymin1 = inputImg.rows, xmax1 = 0, ymax1 = 0;
	float xmin2 = b * inputImg.cols, ymin2 = inputImg.rows, xmax2 = a * inputImg.cols, ymax2 = 0;
	float xmin3 = inputImg.cols, ymin3 = inputImg.rows, xmax3 = b * inputImg.cols, ymax3 = 0;
	Rect finalRect1;
	Rect finalRect2;
	Rect finalRect3;
	vector<vector<Point> >::iterator iter = contours_set.begin();
	for (; iter != contours_set.end();) {
		Rect rect = boundingRect(*iter);
		float radius;
		Point2f center;
		minEnclosingCircle(*iter, center, radius);

		if (rect.area() > 0) {
			point1.x = rect.x;
			point1.y = rect.y;
			point2.x = point1.x + rect.width;
			point2.y = point1.y + rect.height;

			if (point2.x < a * inputImg.cols) {
				if (point1.x < xmin1)
					xmin1 = point1.x;
				if (point1.y < ymin1)
					ymin1 = point1.y;
				if (point2.x > xmax1 && point2.x < xmax2)
					xmax1 = point2.x;
				if (point2.y > ymax1)
					ymax1 = point2.y;
			}

			if (point2.x < b * inputImg.cols && point2.x > a * inputImg.cols) {
				if (point1.x < xmin2 && point1.x>xmin1)
					xmin2 = point1.x;
				if (point1.y < ymin2)
					ymin2 = point1.y;
				if (point2.x > xmax2 && point2.x < xmax3)
					xmax2 = point2.x;
				if (point2.y > ymax2)
					ymax2 = point2.y;
			}

			if (point2.x < inputImg.cols && point2.x > b * inputImg.cols) {
				if (point1.x < xmin3 && point1.x>xmin2)
					xmin3 = point1.x;
				if (point1.y < ymin3)
					ymin3 = point1.y;
				if (point2.x > xmax3)
					xmax3 = point2.x;
				if (point2.y > ymax3)
					ymax3 = point2.y;
			}

			++iter;
		}
		else
			iter = contours_set.erase(iter);
	}

	if (xmin1 == a * inputImg.cols && ymin1 == inputImg.rows && xmax1 == 0 && ymax1 == 0)
		xmin1 = ymin1 = xmax1 = ymax1 = 0;

	if (xmin2 == b * inputImg.cols && ymin2 == inputImg.rows && xmax2 == a * inputImg.cols && ymax2 == 0)
		xmin2 = ymin2 = xmax2 = ymax2 = 0;

	if (xmin3 == inputImg.cols && ymin3 == inputImg.rows && xmax3 == b * inputImg.cols && ymax3 == 0)
		xmin3 = ymin3 = xmax3 = ymax3 = 0;

	finalRect1 = Rect(xmin1, ymin1, xmax1 - xmin1, ymax1 - ymin1);
	finalRect2 = Rect(xmin2, ymin2, xmax2 - xmin2, ymax2 - ymin2);
	finalRect3 = Rect(xmin3, ymin3, xmax3 - xmin3, ymax3 - ymin3);
	rectangle(inputImg, finalRect1, Scalar(0, 255, 0), 2);
	rectangle(inputImg, finalRect2, Scalar(0, 255, 0), 2);
	rectangle(inputImg, finalRect3, Scalar(0, 255, 0), 2);
}

void getSomeFrame(int start, int end, int frame_type = 0) {

	int skip = start;
	VideoCapture capVideo;
	capVideo.open("./3.mp4");
	Mat frame;
	char path[20] = "./frameGRAY/";

	cout << "Getting frame..." << endl;

	/*跳过前stat帧*/
	while (skip > 0) {
		capVideo >> frame;
		if (frame.empty()) {
			cout << "End of video!Start too lagre!" << endl;
			return;
		}
		skip--;
	}

	/*将从start帧到end帧的数据写成图片到指定目录*/
	while (start < end) {
		capVideo >> frame;
		if (frame.empty()) {
			cout << "End of video!All frames have been written." << endl;
			return;
		}

		if (frame_type == GRAY) {
			cvtColor(frame, frame, COLOR_BGR2GRAY);
		}
		else if (frame_type == HSV) {
			cvtColor(frame, frame, COLOR_BGR2HSV);
		}

		sprintf_s(path, "./frameGRAY/%03d.jpg", start);
		imwrite(path, frame);
		start++;
	}

	cout << "Over" << endl;
	return;
}
#endif