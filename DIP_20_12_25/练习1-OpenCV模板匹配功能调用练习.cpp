#if 1

#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	VideoCapture capVideo;
	capVideo.open(0);
	Mat srcImage;
	Mat templateImage;

	int i = 0;
	int cnt = 0;

	Mat resultImage;
	int resultImage_rows;
	int resultImage_cols;

	double minValue = 0;
	double maxValue = 0;
	Point minLocation = Point(0, 0);
	Point maxLocation = Point(0, 0);
	Point matchLocation = Point(0, 0);

	while (1) {
		capVideo >> srcImage;
		/*趁还没转换成灰度图之前imshow*/
		rectangle(srcImage, matchLocation, Point(matchLocation.x + templateImage.cols, matchLocation.y + templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);
		imshow("srcImage", srcImage);

		cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);

		if (cnt == 0) {
			Rect2d r;
			r = selectROI(srcImage, true);
			templateImage= srcImage(r);
			//imshow("tempMat", templateImage);
			resultImage_rows = srcImage.rows - templateImage.rows + 1;
			resultImage_cols= srcImage.cols- templateImage.cols+ 1;
			resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);
			cnt++;
		}
		else {

			matchTemplate(srcImage, templateImage, resultImage, TM_SQDIFF);
			normalize(resultImage, resultImage, 0, 1, NORM_MINMAX, -1, Mat());

			minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

			matchLocation = minLocation;

			waitKey(30);
		}

	}

	waitKey(0);
	return 0;
}

#endif