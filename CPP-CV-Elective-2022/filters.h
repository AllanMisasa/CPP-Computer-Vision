#pragma once
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
	return src;
}

void getContours(Mat dilated, Mat src) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(src, contours, -1, Scalar(255, 0, 255), 2);
}