#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "basic.h"
#include "detectors.h"
#include "analysis.h"
#include "thresholding.h"
#include "chains.h"
#include "filters.h"
#include "ex1.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat blurred;
	Mat image = imread("C:/opencv_images/distant_zebra.jpg");
	Mat temp = imread("C:/opencv_images/pills.jpg");

	contours_full(image);
	//imwrite("C:/portfolio_images/blurred_zebra2.jpg", blurred);
	//CannyThreshold(image);
	//video_edge_detection();
	//matchContoursFull(image, temp);
}