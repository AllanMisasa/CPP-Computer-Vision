#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/features2d.hpp>
#include <iostream>
#include "pipelines.h"

using namespace cv;
using namespace std;

Mat circle_detector(Mat src) {
	medianBlur(src, src, 5);	// Median blur with kernel size of 5
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
		Vec3i c = circles[i];				// Convert circles vector to hold integers.
		Point center = Point(c[0], c[1]); 	// Define center points as Point object
		circle(src, center, 5, Scalar(128, 0, 128), 3, LINE_AA); // Define center dot size and color.
		int radius = c[2]; 										// Find radius of enclosing circlesk.
		//circle(src, center, radius, Scalar(255, 0, 255), 3, LINE_AA); // Draw gray circles around detected circles
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
	params.minArea = 150;			// Filter out any blob object below 150 px in area

	params.filterByCircularity = true;
	params.minCircularity = 0.7;	// Filter out any blob that is less circular in %

	params.filterByConvexity = false;
	params.minConvexity = 0.87;

	params.filterByInertia = false;
	params.minInertiaRatio = 0.7;

	src = preprocessing(src);		

	Mat image_with_keypoints;
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
	vector<KeyPoint> keypoints;
	detector->detect(src, keypoints);
	cout << keypoints.size() << endl;
	drawKeypoints(src, 
					keypoints, 
					image_with_keypoints, 
					Scalar(0, 0, 255),
					DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("Keypoints", image_with_keypoints);
	waitKey(0);

	return image_with_keypoints;
}

/*
getContours() takes as input first the binary image that needs contour approximation
The second input is the original image, so we can overpaint the contours.
The for loop shows the areas of the detected contours
*/
void getContourAreas(Mat dilated, Mat src) {
	vector<vector<Point>> contours;
	vector<vector<Point>> contours_filtered;
	vector<Vec4i> hierarchy;
	 
	findContours(dilated,
		contours,
		hierarchy,
		RETR_EXTERNAL,
		CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		if (area > 12000) {
			contours_filtered.push_back(contours[i]);
		}
		cout << area << endl;
		cout << "Found" << contours_filtered.size() << "zebras" << endl;
	}
	drawContours(src, contours_filtered, -1, Scalar(255, 0, 255), 2);
	imshow("Contours", src);
	waitKey(0);
}

void contoursBounded(Mat src) {
	Mat imgBlur, edges, dilated;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	GaussianBlur(src, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, edges, 25, 75);
	dilate(edges, dilated, kernel);

	vector<vector<Point>> contours;
	vector<vector<Point>> contours_filtered;
	vector<Vec4i> hierarchy;

	findContours(dilated,
		contours,
		hierarchy,
		RETR_EXTERNAL,
		CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		if (area > 12000) {
			contours_filtered.push_back(contours[i]);
		}
		cout << area << endl;
		cout << "Found" << contours_filtered.size() << "contours above size threshold" << endl;
	}

	vector<Rect> boundRect(contours_filtered.size());
	vector<Point2f>centers(contours_filtered.size());
	vector<float>radius(contours_filtered.size());

	vector<vector<Point>> contours_poly(contours_filtered.size());
	for (size_t i = 0; i < contours_filtered.size(); i++)
	{
		approxPolyDP(contours_filtered[i], contours_poly[i], 3, true);
		boundRect[i] = boundingRect(contours_poly[i]);
		minEnclosingCircle(contours_poly[i], centers[i], radius[i]);
	}
	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours_filtered.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours_poly, (int)i, color);
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
		circle(drawing, centers[i], (int)radius[i], color, 2);
	}
	imshow("Contours", drawing);
	waitKey(0);
}

vector<vector<Point>> extractContours(Mat src) {
	vector<vector<Point>> contours;
	vector<vector<Point>> contours_filtered;
	vector<Vec4i> hierarchy;
	cvtColor(src, src, COLOR_BGR2GRAY);
	findContours(src,
		contours,
		hierarchy,
		RETR_EXTERNAL,
		CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		if (area > 15000) {
			contours_filtered.push_back(contours[i]);
		}
	}
	return contours_filtered;
}

void matchContoursSimple(vector<vector<Point>> contour_temp, vector<vector<Point>> array_of_contours) {
	double ans;
	for (int i = 0; i < array_of_contours.size(); i++)
	{
		ans = matchShapes(contour_temp.back(), array_of_contours[i], CONTOURS_MATCH_I1, 0);
		cout << ans << " ";
	}
}

void matchContoursFull(Mat image, Mat temp) {
	RNG rng(12345);

	Mat hsv_base;
	Mat hsv_test1;

	int thresh = 150;
	double ans = 0, result = 0;

	Mat imageresult1, imageresult2;

	//cvtColor(image, hsv_base, COLOR_BGR2HSV);
	//cvtColor(temp, hsv_test1, COLOR_BGR2HSV);

	vector<vector<Point>>contours1, contours2;
	vector<Vec4i>hierarchy1, hierarchy2;

	Canny(image, imageresult1, thresh, thresh * 2);
	Canny(temp, imageresult2, thresh, thresh * 2);

	findContours(imageresult1, contours1, hierarchy1, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	for (int i = 0; i < contours1.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(imageresult1, contours1, i, color, 1, 8, hierarchy1, 0, Point());
	}

	findContours(imageresult2, contours2, hierarchy2, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	for (int i = 0; i < contours2.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(imageresult2, contours2, i, color, 1, 8, hierarchy2, 0, Point());
	}

	for (int i = 0; i < contours2.size(); i++)
	{
		ans = matchShapes(contours1[0], contours2[i], CONTOURS_MATCH_I1, 0);
		cout << ans << " ";
		getchar();
	}
}

Mat contours_simple(Mat img) {
	Mat imgBlur, edges, dilated;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, edges, 25, 75);
	dilate(edges, dilated, kernel);

	getContourAreas(dilated, img);

	return img;
}

Mat contours_full(Mat src) {
	Mat imgGray, imgBlur, edges, dilated;
	Mat contoured = Mat::zeros(src.rows, src.cols, CV_8UC3);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	cvtColor(src, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(5, 5), 3, 0);
	Canny(imgBlur, edges, 50, 150);
	dilate(edges, dilated, kernel);

	findContours(dilated,
		contours,
		hierarchy,
		RETR_EXTERNAL,
		CHAIN_APPROX_SIMPLE);

	// iterate through all the top-level contours,
	// draw each connected component with its own random color
	int idx = 0;
	for (; idx >= 0; idx = hierarchy[idx][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(contoured, contours, idx, color, FILLED, 8, hierarchy);
	}
	imshow("Components", contoured);
	waitKey(0);
	return contoured;
}

void simple_match(Mat image, Mat temp) {
	// Perform template matching
	Mat result;
	matchTemplate(image, temp, result, TM_CCOEFF_NORMED);

	// Find the location of the best match
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	// Draw a rectangle around the best match
	rectangle(image, maxLoc, Point(maxLoc.x + temp.cols, maxLoc.y + temp.rows), Scalar(255, 0, 255), 2);

	// Display the image with the rectangle
	imshow("Image", image);
	waitKey(0);
}

int match(Mat ref, Mat tpl)
{
	Mat gref, gtpl;
	cvtColor(ref, gref, COLOR_BGR2GRAY);									 // Convert input image to grayscale
	cvtColor(tpl, gtpl, COLOR_BGR2GRAY);									 // Convert template image to grayscale

	const int low_canny = 110;												 // Set low threshold of the Canny edge detection
	Canny(gref, gref, low_canny, low_canny * 3);							 // High threshold is 3x of low
	Canny(gtpl, gtpl, low_canny, low_canny * 3);

	imshow("file", gref);
	imshow("template", gtpl);

	Mat res_32f(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1); // Set up result image - 32 bits floating point, 1 channel
	matchTemplate(gref, gtpl, res_32f, TM_CCOEFF_NORMED);					 // Template match and mark matched objects in res

	Mat res;
	res_32f.convertTo(res, CV_8U, 255.0);									 // After matching we do not need the precision of 32F, so we downscale to 8bit uint representation
	imshow("result", res);

	int size = ((tpl.cols + tpl.rows) / 4) * 2 + 1;							 // Force size to be odd
	adaptiveThreshold(res, res, 255, ADAPTIVE_THRESH_MEAN_C,				 // Adaptive thresholding on 
					  THRESH_BINARY, size, -64);
	imshow("result_thresh", res);

	while (1)																 // This loop fills rectangles around matched objects
	{
		double minval, maxval;
		Point minloc, maxloc;
		minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

		if (maxval > 0)
		{
			rectangle(ref, maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows), Scalar(0, 255, 0), 2);
			floodFill(res, maxloc, 0); //mark drawn blob
		}
		else
			break;
	}

	imshow("final", ref);
	waitKey(0);

	return 0;
}

void corner_detection(Mat src) {
	Mat src_gray;
	int thresh = 120;
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

void alt_corner(Mat src) {
	RNG rng(12345);
	int maxCorners = MAX(400, 1);
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