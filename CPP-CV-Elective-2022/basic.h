#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

Mat resize_image(Mat src, int width, int height)
{
	Mat resized_down;
	resize(src, resized_down, Size(width, height), INTER_LINEAR);

	return resized_down;
}

