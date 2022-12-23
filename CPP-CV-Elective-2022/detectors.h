#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/features2d.hpp>
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
	std::vector<KeyPoint> keypoints;
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