#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat circle_detector(Mat src) {
	// medianBlur(src, src, 5);	// Median blur with kernel size of 5
	vector<Vec3f> circles;		// Vector of 3 floating point integers	
	HoughCircles(src, circles,  // circles: A vector that stores sets of 3 values: xc,yc,r for each detected circle.
				 HOUGH_GRADIENT,// Detection method - HOUGH_GRADIENT is the only one as of OpenCV 4.6.0
				 1,				// Inverse ratio of resolution 
				 src.rows/16,   // Minimum distance in pixels between the circles
				 100,			// Upper threshold for internal Canny edge detector
				 30,			// Threshold for center detection
				 1,				// Minimum radius to be detected. If unknown, set to zero.
				 70				// Maximum radius to be detected. If unknown, set to zero.
				);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];	// Convert circles vector to hold integers.
		Point center = Point(c[0], c[1]); // Define center points as Point object
		circle(src, center, 1, Scalar(0, 100, 100), 3, LINE_AA); // Define center dot size and color.
		int radius = c[2]; // Find radius of enclosing circles
		circle(src, center, radius, Scalar(178, 190, 181), 3, LINE_AA); // Draw gray circles around detected circles
	}
	imshow("Detected circles", src);
	waitKey();

	return src;
}

Mat Blob_detector(Mat src) {
	SimpleBlobDetector::Params params; 	// Setup SimpleBlobDetector parameters.

	params.minThreshold = 10;
	params.maxThreshold = 200;

	params.filterByArea = true;
	params.minArea = 1500;

	params.filterByCircularity = true;
	params.minCircularity = 0.1;

	params.filterByConvexity = true;
	params.minConvexity = 0.87;

	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;

	Mat image_with_keypoints;
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
	vector<KeyPoint> keypoints;
	detector->detect(src, keypoints);
	drawKeypoints(src, 
					keypoints, 
					image_with_keypoints, 
					Scalar(0, 0, 255),
					DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("Keypoints", image_with_keypoints);
	waitKey(0);
	return image_with_keypoints;
}

void getContours(Mat dilated, Mat src) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	 
	findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(src, contours, -1, Scalar(255, 0, 255), 2);
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;
	}
}

void contours(Mat img) {
	Mat imgGray, imgBlur, edges, dilated;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, edges, 25, 75);
	dilate(edges, dilated, kernel);

	getContours(dilated, img);

	imshow("Contoured image", img);
	waitKey(0);
}

Mat sift_keypoints(Mat image) {

	// Create a SIFT detector object
	Ptr<SIFT> detector = SIFT::create();

	// Detect keypoints in the image
	std::vector<KeyPoint> keypoints;
	detector->detect(image, keypoints);

	// Draw the keypoints on the image
	Mat keypoint_image;
	drawKeypoints(image, keypoints, keypoint_image, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	return keypoint_image;
}

void template_matching(Mat image, Mat temp) {
	// Perform template matching
	Mat result;
	matchTemplate(image, temp, result, TM_CCOEFF_NORMED);

	// Find the location of the best match
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	// Draw a rectangle around the best match
	rectangle(image, maxLoc, Point(maxLoc.x + temp.cols, maxLoc.y + temp.rows), Scalar(0, 255, 0), 2);

	// Display the image with the rectangle
	imshow("Image", image);
	waitKey(0);
}