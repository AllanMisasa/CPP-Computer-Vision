#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

Mat resize_image(Mat src, int width, int height)
{
	// Read the image using imread function
	Mat image = src;

	// Downscale the image using new  width and height
	Mat resized_down;
	resize(image, resized_down, Size(width, height), INTER_LINEAR);

	return resized_down;
}