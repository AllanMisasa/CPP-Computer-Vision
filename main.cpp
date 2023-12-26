#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "CPP-CV-Elective-2022/analysis.h"

#include <iostream>

using namespace std; // Standard C++ namespace
using namespace cv; // OpenCV namespace

int main() {
	// Set path to image
	std::string image_path = samples::findFile("starry_night.jpg");

	// Read image into Mat object
	Mat img = imread(image_path, IMREAD_COLOR); 

	// Check if image cannot be read. If not, return error.
	if (img.empty())
	{
		std::cout << "Image cannot be loaded" << std::endl; // Print error message
		return -1; // Return error
	}
	
	vector<Mat> bgr_planes; // Vector to store the 3 channels of the image
	split(img, bgr_planes); // Split the image into 3 channels

	int histSize = 256; // number of bins
	float range[] = { 0, 256 }; // the upper boundary is exclusive
	const float* histRange[] = {range}; // range of the histogram
	bool uniform = true, accumulate = false; // uniform distribution of bins and no accumulation
	
	Mat b_hist, g_hist, r_hist; // Mat objects to store the histograms
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate); // Calculate histogram for blue channel
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate); // Calculate histogram for green channel
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate); // Calculate histogram for red channel
	
	// Plot the histograms
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0)); // Create a black image to store the histograms
	
	// Normalize the histograms
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	
	// Draw the histograms
	for (int i = 1; i < histSize; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	
	// Display the histograms
	//imshow("Histogram", histImage);
	//waitKey(0);
	//return 0;
	Histogram_color(img);
}
