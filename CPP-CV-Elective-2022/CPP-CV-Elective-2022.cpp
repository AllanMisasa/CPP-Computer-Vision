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
	utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
	Mat image = imread("C:/opencv_images/pills.jpg");
	//image = resize_image(image, 640, 480);
	Mat temp = imread("C:/opencv_images/pill.jpg");
	//temp = resize_image(temp, 640, 480);
	//dilated = preprocessing(image);
	//getContourAreas(dilated, image);
	//contours_full(image);
	//imwrite("C:/portfolio_images/blurred_zebra2.jpg", blurred);
	//CannyThreshold(image);
	//video_edge_detection();
	//matchContoursFull(image, temp);
	//Blob_detector(image);
	//circle_detector(image);
	sift_matching(image, temp);
}