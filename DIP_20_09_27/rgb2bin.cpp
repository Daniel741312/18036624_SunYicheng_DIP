#include"rgb2bin.h"

cv::Mat& rgb2bin(cv::Mat &M1,uchar threhold) {
	int i = 0;
	int j = 0;

	int weight = M1.cols;
	int height = M1.rows;

	for (j = 0; j < height; j++) {
		for (i = 0; i < weight; i++) {
			uchar aver = (M1.at<Vec3b>(j, i)[0] + M1.at<Vec3b>(j, i)[1] + M1.at<Vec3b>(j, i)[2]) / 3;
			/*当aver>阈值取255,当aver<阈值取0,实现二值化*/
			aver = aver > threhold ? 255 : 0;
			M1.at<Vec3b>(j, i)[0] = aver;
			M1.at<Vec3b>(j, i)[1] = aver;
			M1.at<Vec3b>(j, i)[2] = aver;
		}
	}
	return M1;

}
