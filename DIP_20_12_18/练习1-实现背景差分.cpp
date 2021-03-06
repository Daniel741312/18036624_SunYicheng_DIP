#if 0

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	Mat frame;
	Mat bgMat;
	Mat subMat;
	Mat bny_subMat;
	VideoCapture capVideo;
	capVideo.open(0);
	int cnt = 0;

	while (1) {
		capVideo >> frame;
		cout << frame.size<<endl;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		if (cnt == 0) {
			frame.copyTo(bgMat);
		}else {
			absdiff(frame, bgMat, subMat);
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

			imshow("bny_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}
		cnt++;
	}

	waitKey(0);
	return 0;
}

#endif