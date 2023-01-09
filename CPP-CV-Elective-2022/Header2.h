#pragma once
#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "chains.h"

using namespace cv;
using namespace std;

void corner_detection(Mat src) {
	Mat src_gray;
	int thresh = 150;
	int MAX_THRESH = 255;
	string source_window("Source image");
	string corners_window("Harris Corner detection");
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	Mat dst = Mat::zeros(src.size(), CV_32FC1);
	cornerHarris(src_gray, dst, blockSize, apertureSize, k);
	Mat dst_norm, dst_norm_scaled;
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);

	for (int i = 0; i < dst_norm.rows; i++)
	{
		for (int j = 0; j < dst_norm.cols; j++)
		{
			if ((int)dst_norm.at<float>(i, j) > thresh)
			{
				circle(dst_norm_scaled, Point(j, i), 5, Scalar(255), 2, 8, 0);
			}
		}
	}
	namedWindow(corners_window.c_str());
	imshow(corners_window.c_str(), dst_norm_scaled);
	waitKey(0);
}

void alt_corner(Mat src)
{
	RNG rng(12345);
	int maxCorners = MAX(100, 1);
	vector<Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3, gradientSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	Mat copy = src.clone(), src_gray;

	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	goodFeaturesToTrack(src_gray,
		corners,
		maxCorners,
		qualityLevel,
		minDistance,
		Mat(),
		blockSize,
		gradientSize,
		useHarrisDetector,
		k);

	cout << "** Number of corners detected: " << corners.size() << endl;
	int radius = 4;
	for (size_t i = 0; i < corners.size(); i++)
	{
		circle(copy, corners[i], radius, Scalar(rng.uniform(0, 255), rng.uniform(0, 256), rng.uniform(0, 256)), FILLED);
	}

	imshow("Image with detected corners", copy);

	waitKey(0);
}