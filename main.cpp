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

	HSV_track_bars(img);	
}
