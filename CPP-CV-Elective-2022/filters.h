#pragma once
#include <opencv2/video.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat RemoveColor(Mat src, int color)
{
	vector<Mat> BGRChannels;
	split(src, BGRChannels);

	switch (color) {
		case 0:
			BGRChannels[0] = Mat::zeros(src.rows, src.cols, CV_8UC1);// removing Blue channel
			merge(BGRChannels, src); // pack the image
		case 1:
			BGRChannels[1] = Mat::zeros(src.rows, src.cols, CV_8UC1);// removing Green channel
			merge(BGRChannels, src); // pack the image
		case 2:
			BGRChannels[1] = Mat::zeros(src.rows, src.cols, CV_8UC1);// removing Green channel
			merge(BGRChannels, src); // pack the image
	}
	imshow("Stripped image", src);
	return src;
}

/*
void getContours(Mat dilated, Mat src) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(src, contours, -1, Scalar(255, 0, 255), 2);
}
*/

Mat backgroundRemovalSimple(Mat frame, Mat src) {
	Mat hsv, mask, res;
	cvtColor(frame, hsv, COLOR_BGR2HSV);

	inRange(hsv, Scalar(30, 0, 0), Scalar(100, 255, 255), mask);

	//frame = frame - res;
	frame.setTo(Scalar(0, 0, 0), mask);
	bitwise_or(frame, src, res);
	return res;
}


Mat backgroundRemovalComplex(Mat src) {
	Mat foregroundMask, foregroundImg, backgroundImg;
	Ptr<BackgroundSubtractor> backSub;

	backSub = createBackgroundSubtractorMOG2();						// Initialize backgroundsubtractor

	if (foregroundMask.empty()) {
		foregroundMask.create(src.size(), src.type());
	}
	backSub->apply(src, foregroundMask, true ? -1 : 0);				// Use backgroundsubtractor to find the foreground mask

	GaussianBlur(foregroundMask, foregroundMask, Size(5, 5), 3.5, 3.5);
	threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY);

	foregroundImg = Scalar::all(0);									

	src.copyTo(foregroundImg, foregroundMask);
	backSub->getBackgroundImage(backgroundImg);

	return foregroundMask;
}