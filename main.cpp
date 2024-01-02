#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "CPP-CV-Elective-2022/analysis.h"
#include "CPP-CV-Elective-2022/filters.h"

#include <iostream>

using namespace std; 													// Standard C++ namespace
using namespace cv; 													// OpenCV namespace

string path = "images/"; 		

int low = 0;
int high = 255;
const String window = "Binary thresholds";

static void onTrackbar(int, void *) {
	low_H = min(high-1, low);
	setTrackbarPos("Low", window, low_H);
}

int main() {
	std::string image_path = samples::findFile("starry_night.jpg");  	// Set path to image
	string italy = path + "italy.jpg";									// Set path to image
	Mat threshold;
	Mat img1 = imread(italy, 0);  										// Read image into Mat object
	Mat img2 = imread(image_path, 0);  									// Read image into Mat object

	namedWindow(window, WINDOW_AUTOSIZE); 								// Create a window
	createTrackbar("Low", window, &low , 255, onTrackbar); // Create a trackbar

	while (true) {	
		inRange(img1, low_H, high_H, threshold);
		imshow("Lena", threshold); 										// Show the image
		char key = (char) waitKey(30);
		if (key == 'q' || key == 27)
		{
			break;
		}			
	}								
}

/*
Mat img_HSV, frame_threshold;											// Create Mat objects for HSV image and thresholded image
Mat hsvImage; 															// Create a new empty image
cvtColor(img, hsvImage, COLOR_BGR2HSV); 								// Convert to HSV
Mat mask; 																// Create a new empty image
inRange(hsvImage, Scalar(0, 100, 100), Scalar(150, 255, 255), mask); 	// Apply threshold - first scalar is lower bound, second scalar is upper bound
Mat result;																// Create a new empty image
bitwise_and(img, img, result, mask); 									// Apply mask
imshow("Lena", result); 												// Show the image
waitKey(0); 															// Wait for keypress
}
*/
