#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "CPP-CV-Elective-2022/analysis.h"
#include "CPP-CV-Elective-2022/filters.h"
#include "CPP-CV-Elective-2022/thresholding.h"
#include "CPP-CV-Elective-2022/pipeline.h"

#include <iostream>

using namespace std; 													// Standard C++ namespace
using namespace cv; 													// OpenCV namespace

vector<Mat> bgr_planes;
int histSize = 256;
float range[] = { 0, 256 }; //the upper boundary is exclusive
const float* histRange[] = { range };
Mat b_hist, g_hist, r_hist;
int hist_w = 512, hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );

string path = "images/"; 	
string image_path, image_path2, image_path3; 												// Path to image

//const int max_value_H = 360/2;
//const int max_value = 255;
//int low_H = 0, low_S = 0, low_V = 0;
//int high_H = max_value_H, high_S = max_value, high_V = max_value;

Mat img, pcb, out, hist, hist2, hist3, opencv, thresholded, hsv; 
Mat sobelx, sobely, sobelxy;

int main() {
    image_path = path + "italy.jpg"; 										// Path to image
    image_path2 = path + "pcb.jpg";
    image_path3 = path + "opencv.jpg";
	img = imread(image_path, IMREAD_COLOR); 									// Read the file
    pcb = imread(image_path2, IMREAD_COLOR);
    opencv = imread(image_path3, IMREAD_COLOR);   
    edge(img);
}
