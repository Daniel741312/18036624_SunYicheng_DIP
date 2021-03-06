#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace cv;
using namespace std;

void hsvreg(){
    Mat img= imread("C:/Users/Daniel/Desktop/sb.jpg");
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);//转为HSV
    imshow("srcMat", img);
    imshow("hsv", imgHSV);

    //HSV范围
    int iLowH = 230;
    int iHighH =250;

    int iLowS = 140;
    int iHighS = 160;

    int iLowV = 140;
    int iHighV = 160;

    inRange(imgHSV,);

    waitKey(0);
}

#if 1
int main(int argc, char* argv[]) {
    hsvreg();
    return 0;
}
#endif
