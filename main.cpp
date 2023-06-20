#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

void getCorners(Mat imgin, Mat imgout) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imgin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(imgout, contours, -1, Scalar(255, 0, 255), 2);
}


int main() {

	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgout;
	//resize(img, img,Size(), 0.75, 0.75);

	//Mat imggray, imgcanny, imgblur, imgdil;
	//cvtColor(img, imggray, COLOR_BGR2GRAY);
	//GaussianBlur(imggray, imgblur, Size(3, 3), 3, 0);
	//Canny(imgblur, imgcanny, 25, 75);
	//Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//dilate(imgcanny, imgdil, kernel);

	getCorners(img, imgout);
	imshow("imgout", imgout);

	waitKey(0);
	return 0;
}

