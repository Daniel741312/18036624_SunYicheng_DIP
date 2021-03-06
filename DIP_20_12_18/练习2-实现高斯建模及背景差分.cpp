/*摄像头尺寸480 x 640*/
#if 1

/*测试开关*/
#define TEST

#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/*要获取前多少帧做建模*/
#define N 100

/*查看一下average和variance,不是图片的话显示不出来*/
Mat averageImg;
Mat varianceImg;

/*获取前N帧*/
void getNFrame(vector<Mat>& arr);
/*计算均值*/
void calAverage(Mat& average, vector<Mat>& arr);
/*计算方差*/
void calVariance(Mat& average, vector<Mat>& arr, Mat& variance);
/*进行对后面视频流的进行背景差分*/
void calFrame(Mat& average, Mat& variance);

int main(int argc, char* argv[]) {
	/*平均值的Mat:average,要用16位数据乃至32位,否则随着累加的进行结果可能会溢出*/
	Mat average = Mat(480, 640, CV_16UC1);
	average = 0;
	/*方差的Mat:variance*/
	Mat variance = Mat(480, 640, CV_16UC1);
	variance = 0;
	/*将前N帧保存到arr中*/
	vector<Mat> arr;

	getNFrame(arr);

	calAverage(average, arr);
	imshow("averageImg", averageImg);

	calVariance(average, arr, variance);
	imshow("varianceImg", varianceImg);

	calFrame(average, variance);
	waitKey(0);
	return 0;
}

void getNFrame(vector<Mat>& arr) {
	/*获取视频帧流*/
	VideoCapture capVideo;
	capVideo.open(0);
	Mat frame;

	int i = 0;

	/*取前N帧到arr*/
	for (i = 0; i < N; i++) {
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		arr.push_back(frame);
		//cout << "frame.size=" << frame.size<<" arr[i].size="<<arr[i].size<< endl;
	}
	/*把那两个全局的Mat用frame初始化一下*/
	frame.copyTo(averageImg);
	frame.copyTo(varianceImg);
	return;
}

void calAverage(Mat& average, vector<Mat>& arr) {
	int i = 0;
	int j = 0;
	int k = 0;

	int rowNum = average.rows;
	int colNum = average.cols;
	//cout << "rowNum=" << rowNum << " colNum=" << colNum << endl;

	/*k循环遍历arr中每一个Mat*/
	for (k = 0; k < N; ++k) {

		//cout << "average.size=" << average.size << " arr.size=" << arr[k].size << endl;
		for (i = 0; i < rowNum; ++i) {
			uchar* arrPtr = arr[k].ptr<uchar>(i);
			/*16位无符号整型的指针类型对应为(ushort*)*/
			ushort* averagePtr = average.ptr<ushort>(i);
			for (j = 0; j < colNum; ++j) {
				averagePtr[j] += arrPtr[j];
			}
		}
	}

	/*都用的整数近似计算*/
	average /= N;

	/*把average中的数据拿到averageImg里面去,当成一张图片去显示*/
	for (i = 0; i < rowNum; ++i) {
		ushort* averagePtr = average.ptr<ushort>(i);
		uchar* averageImgPtr = averageImg.ptr<uchar>(i);
		for (j = 0; j < colNum; ++j) {
			averageImgPtr[j] = averagePtr[j];
		}
	}

	return;
}

void calVariance(Mat& average, vector<Mat>& arr,Mat& variance) {
	int i = 0;
	int j = 0;
	int k = 0;

	int rowNum = arr[0].rows;
	int colNum = arr[0].cols;
	/*k循环遍历arr中每一个Mat*/
	for (k = 0; k < N; ++k) {

		for (i = 0; i < rowNum; ++i) {
			uchar* arrPtr = arr[k].ptr<uchar>(i);
			ushort* averagePtr = average.ptr<ushort>(i);
			ushort* variancePtr = variance.ptr<ushort>(i);

			for (j = 0; j < colNum; ++j) {
				variancePtr[j] += pow((arrPtr[j] - averagePtr[j]), 2);
			}
		}
	}

	variance /= N;

	/*把variance中的数据拿到varianceImg中去,当成一张图片去显示*/
	for (i = 0; i < rowNum; ++i) {
		ushort* variancePtr = variance.ptr<ushort>(i);
		uchar* varianceImgPtr = varianceImg.ptr<uchar>(i);
		for (j = 0; j < colNum; ++j) {
			varianceImgPtr[j] = variancePtr[j];
		}
	}
	return;
}

void calFrame(Mat& average,Mat& variance) {
	int i = 0;
	int j = 0;
	int k = 0;
	int rowNum = average.rows;
	int colNum = average.cols;

	/*获取视频帧流*/
	VideoCapture capVideo;
	capVideo.open(0);
	Mat frame;

	while (1) {
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		cout << "average.size=" << average.size << " varianve.size=" << variance.size << " frame.size=" << frame.size << endl;

		for (i = 0; i < rowNum; ++i) {
			uchar* framePtr = frame.ptr<uchar>(i);
			ushort* averagePtr = average.ptr<ushort>(i);
			ushort* variancePtr = variance.ptr<ushort>(i);
			for (j = 0; j < colNum; ++j) {
				framePtr[j] = (abs(framePtr[j] - averagePtr[j]) > variancePtr[j]*3) ? 255 : 0;
			}
		}
		imshow("frame", frame);
		waitKey(20);
	}

	return;
}

#endif