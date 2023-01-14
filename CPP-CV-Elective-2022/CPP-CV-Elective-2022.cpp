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

	RNG rng(12345);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat image = imread("C:/opencv_images/three_zebra.jpg", IMREAD_GRAYSCALE);
	Mat temp = imread("C:/opencv_images/pills.jpg");
	Mat drawing = Mat::zeros(edges.size(), CV_8UC3);

	//sift_keypoints(image);
	
	//Mat dog = DoG(image);
	//dog = OtsuThreshold(dog);
	//GaussianBlur(dog, dog, Size(11, 11), 2);
	//dog = contours_simple(dog);
	//imshow("Contours", dog);
	//i_am_blrrr(image);
	Mat dog = DoG(image);
	dog = contours_simple(dog);
	imshow("DoG", dog);
	waitKey(0);
}