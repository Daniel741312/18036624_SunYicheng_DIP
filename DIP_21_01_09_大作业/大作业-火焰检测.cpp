#if 1
/*��Ƶ�ߴ�:480x268*/
/*���λ��:174x34*/

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

/*�ҵ�������������ߵ�������*/
void find3Points(Mat& frame,vector<Point>* parameter);
/*����find3Pointers�ҵ�����������frame�ϻ���������*/
void drawParabola(Mat& frame, const vector<Point>* parameter);
/*������*/
void CheckColor(Mat& inImg);
/*ΪChechColor���������,���ƻ���ı߿�*/
void DrawFire(Mat& inputImg, Mat foreImg);
/*(׼�������õ�)��ȡstart��end֡��ͼƬ��./frameĿ¼*/
void getSomeFrame(int start,int end,int frame_type);

int main(int argc, char* argv[]) {
	/*����3��������������ߵ�������*/
	vector<Point>* parameter=new vector<Point>;
	/*
		*���λ��:
		*��ROI�е�����,����ͼ���ֵ��֮����кܶ�ǰ������,�細���͵����,�޷��ܺõ���ȡ��ˮ��,
		*����ֻȡ����·���һ��������ΪROI,������Ѱ��ˮ�����ҵ�������;
		*����������λ���������ROI������
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
		/*�ҵ�����*/
		CheckColor(frame);
		/*�ҵ�������������ߵ�������*/
		find3Points(frame, parameter);
		/*���Ƴ�������*/
		drawParabola(frame, parameter);
		imshow("dst1", frame);

		sprintf_s(fileName, "./dstFrame/%03d.jpg", i++);
		imwrite(fileName, frame);

		waitKey(30);
	}

	/*�ͷ��ڴ�*/
	delete parameter;
	waitKey(0);
	return 0;
}

/*�ҵ�������������ߵ�������*/
void find3Points(Mat& frame,vector<Point>* parameter) {

	(*parameter)[0] = Point(76, 0);
	(*parameter)[1] = Point(0, 0);
	(*parameter)[2] = Point(0, 0);

	int cnt = 1;
	int i = 0;
	int j = 0;
	/*��֡ͼ����ѡ��ROI*/
	Mat frameROI= frame(Rect(106, 36, 165, 41));
	/*��ֵ��*/
	cvtColor(frameROI, frameROI, COLOR_BGR2GRAY);
	dilate(frameROI, frameROI, Mat(4,4,CV_8UC1));
	threshold(frameROI, frameROI, 200, 255, 0);
	/*��������*/
	imwrite("frameROI.jpg", frameROI);

	for (i = frameROI.rows - 1; i > 0; i =i/2) {
		for (j = frameROI.cols - 1; j > 0; j--) {
			/*��������,��������,������ɫ��Ϊ��ˮ��*/
			if (frameROI.at<uchar>(i, j) == 255) {
				(*parameter)[cnt++] = Point(j, i);
				break;
			}
		}
		/*�ҵ��������break*/
		if (cnt==3)
			break;
	}

	/*�������ROI�����������������ͼ�������*/
	for (i = 0; i < 3; i++) {
		(*parameter)[i].y += 35;
		(*parameter)[i].x += 100;
	}

	return;
}

/*����find3Pointers�ҵ�����������frame�ϻ���������*/
void drawParabola(Mat& frame,const vector<Point>* parameter) {
	int x0 = (*parameter)[0].x;
	int x1 = (*parameter)[1].x;
	int x2 = (*parameter)[2].x;

	int y0 = (*parameter)[0].y;
	int y1 = (*parameter)[1].y;
	int y2 = (*parameter)[2].y;

	/*�����ĺ���,������Ҳ����,Ӧ���Ǹ���һ���Ա����;����һ��������ľ�����������ʽ�Ĳ���*/
	float A[3][3] = { {x0 * x0, x0, 1}, {x1 * x1, x1, 1}, {x2 * x2, x2, 1} };
	float B[3] = { y0, y1,y2 };
	float C[3] = { 0, 0, 0 };

	size_t i=0;
	CvMat* matA = cvCreateMat(3, 3, CV_32FC1);
	CvMat* matB = cvCreateMat(3, 1, CV_32FC1);

	CvMat* matC = cvCreateMat(3, 1, CV_32FC1);

	cvSetData(matA, A, CV_AUTOSTEP);
	cvSetData(matB, B, CV_AUTOSTEP);
	/*���ĺ���,�������ߵĲ����浽��matC��*/
	cvSolve(matA, matB, matC, CV_LU);

	int result=0;

	for (i = 0; i < frame.cols; i++) {
		/*��������������Ĳ�������������*/
		result = (int)(i * i * matC->data.fl[0]) + i * matC->data.fl[1] + matC->data.fl[2];
		if (result < frame.rows) {
			/*����ȥ*/
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
			/*��Ϊ��ɫ����Ϊ����:��ɫ������:��ɫ����Զ������ɫ����ɫ����,��ɫ����Ҳ������ɫ����*/
			if ((R - B) >= 80 && (R - G) >= 50 && (G - B) >= 25) {
				/*���沿�ֱ��Ϊ��ɫ*/
				fireImg.at<uchar>(i, j) = 255;
			}
			else {
				fireImg.at<uchar>(i, j) = 0;
			}
		}
	}

	medianBlur(fireImg, fireImg, 5);
	/*��ʴȥ��һЩ���*/
	erode(fireImg, fireImg, Mat(3, 3, CV_8UC1));
	/*��������Χ*/
	dilate(fireImg, fireImg, Mat(4, 4, CV_8UC1));
	/*���Ƴ�����������ֵͼ*/
	imshow("Binary", fireImg);
	/*���ƾ�������*/
	DrawFire(inImg, fireImg);
}

/*���ƾ�������:
	�������:ԭ��ͼ�ͱ�ǵĶ�ֵͼ
*/
void DrawFire(Mat& inputImg, Mat foreImg) {

	/*����������ȡ��ĵ㼯�����˹�ϵ*/
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

	/*����ǰstat֡*/
	while (skip > 0) {
		capVideo >> frame;
		if (frame.empty()) {
			cout << "End of video!Start too lagre!" << endl;
			return;
		}
		skip--;
	}

	/*����start֡��end֡������д��ͼƬ��ָ��Ŀ¼*/
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