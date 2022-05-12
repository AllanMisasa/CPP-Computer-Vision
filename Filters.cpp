/*

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

# include <iostream>

using namespace cv;
using namespace std;

int filter() {
	// Set path to image
	std::string image_path = samples::findFile("starry_night.jpg");
	
	// Read image into Mat object
	Mat img = imread(image_path, IMREAD_COLOR);
	
	// Check if image cannot be read. If not, return error.
	if(img.empty())
		{
		std::cout << "Image cannot be loaded" << std::endl;
		return -1;
		}

	// Blur image
	blur(img, img, Size(5, 5));

	// Display blurred image
	imshow("Display window", img);
	int k = waitKey(0);

	if (k == 's')
	{
		imwrite("starry_night.jpg", img);
	}
	return 0;
}
*/