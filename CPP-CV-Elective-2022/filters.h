#pragma once
#include <opencv2/video.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

const int max_value_H = 360/2;
const int max_value = 255;
const String window_capture_name = "Original Image";
const String window_detection_name = "HSV Thresholding";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;
static void on_low_H_thresh_trackbar(int, void *)
{
	low_H = min(high_H-1, low_H);
	setTrackbarPos("Low H", window_detection_name, low_H);
}
static void on_high_H_thresh_trackbar(int, void *)
{
	high_H = max(high_H, low_H+1);
	setTrackbarPos("High H", window_detection_name, high_H);
}
static void on_low_S_thresh_trackbar(int, void *)
{
	low_S = min(high_S-1, low_S);
	setTrackbarPos("Low S", window_detection_name, low_S);
}
static void on_high_S_thresh_trackbar(int, void *)
{
	high_S = max(high_S, low_S+1);
	setTrackbarPos("High S", window_detection_name, high_S);
}
static void on_low_V_thresh_trackbar(int, void *)
{
	low_V = min(high_V-1, low_V);
	setTrackbarPos("Low V", window_detection_name, low_V);
}
static void on_high_V_thresh_trackbar(int, void *)
{
	high_V = max(high_V, low_V+1);
	setTrackbarPos("High V", window_detection_name, high_V);
}

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
			BGRChannels[2] = Mat::zeros(src.rows, src.cols, CV_8UC1);// removing Red channel
			merge(BGRChannels, src); // pack the image
	}
	imshow("Stripped image", src);
	return src;
}

void HSV_track_bars(Mat img) {

	Mat img_HSV, frame_threshold;	// Create Mat objects for HSV image and thresholded image

    namedWindow(window_capture_name);
    namedWindow(window_detection_name);
	
    // Trackbars to set thresholds for HSV values
    createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
    createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
    createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
    createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
    createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
    createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);

	while (true) {

		cvtColor(img, img_HSV, COLOR_BGR2HSV);
		inRange(img_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);

		imshow(window_capture_name, img);
		imshow(window_detection_name, frame_threshold);
		char key = (char) waitKey(30);
		if (key == 'q' || key == 27)
		{
			break;
		}
	}
}

Mat HSV_filter(Mat src, int low_H, int low_S, int low_V, int high_H, int high_S, int high_V) {
	Mat img_HSV, frame_threshold;	// Create Mat objects for HSV image and thresholded image

	cvtColor(src, img_HSV, COLOR_BGR2HSV);
	inRange(img_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);

	return frame_threshold;
}

/*
void getContours(Mat dilated, Mat src) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(src, contours, -1, Scalar(255, 0, 255), 2);
}
*/

Mat edge_filter(Mat src) {
	float sigma_s = 60, sigma_r = 0.4;
	edgePreservingFilter(src, src, 1, sigma_s, sigma_r);
	return src;
}

Mat gabor_filter(Mat src) {
	Mat out, dest, src_float;
	src.convertTo(src_float, CV_32F);
	Mat kernel = getGaborKernel(Size(35, 35), 3, 1, 10, 0.5, 0, CV_32F);  // kernel size, sigma, theta, lambda, gamma, psi, ktype
	filter2D(src_float, dest, CV_32F, kernel);
	dest.convertTo(out, CV_8U, 1.0/255.0); 								// move to proper[0-255] range to show it
	return out;
}

Mat DoG(Mat src) {
	Mat g1, g2, dog;
	GaussianBlur(src, g1, Size(1, 1), 0);
	GaussianBlur(src, g2, Size(5, 5), 0);
	subtract(g1, g2, dog);
	return dog;
}

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

