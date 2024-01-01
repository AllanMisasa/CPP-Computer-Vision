#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "CPP-CV-Elective-2022/analysis.h"
#include "CPP-CV-Elective-2022/filters.h"

#include <iostream>

using namespace std; // Standard C++ namespace
using namespace cv; // OpenCV namespace

string path = "C:/Users/Andreas/Desktop/CPP-CV-Elective-2022/"; // Path to project folder

int main() {
	std::string image_path = samples::findFile("starry_night.jpg");  	// Set path to image
	Mat img = imread(image_path, IMREAD_COLOR);  	// Read image into Mat object

	Mat img_HSV, frame_threshold;	// Create Mat objects for HSV image and thresholded image

	if (img.empty())	// Check if image cannot be read. If not, return error.
	{
		std::cout << "Image cannot be loaded" << std::endl;
		return -1; // Return error
	}
Mat hsvImage; // Create a new empty image
cvtColor(img, hsvImage, COLOR_BGR2HSV); // Convert to HSV
Mat mask; // Create a new empty image
inRange(hsvImage, Scalar(0, 100, 100), Scalar(150, 255, 255), mask); // Apply threshold - first scalar is lower bound, second scalar is upper bound
Mat result; // Create a new empty image
bitwise_and(img, img, result, mask); // Apply mask
imshow("Lena", result); // Show the image
waitKey(0); // Wait for keypress
}
