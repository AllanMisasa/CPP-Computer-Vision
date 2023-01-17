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
#include "keypoint_matching.h"

#include <opencv2/core/utils/logger.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	utils::logging::setLogLevel(utils::logging::LogLevel::LOG_LEVEL_SILENT);

	Mat image = imread("C:/opencv_images/three_zebra.jpg", IMREAD_GRAYSCALE);
	Mat temp = imread("C:/opencv_images/pills.jpg");

	//sift_keypoints(image);

	i_am_blrrr(image);
	//Mat dog = DoG(image);
	//contoursBounded(dog);
	//video_background_replace();
}