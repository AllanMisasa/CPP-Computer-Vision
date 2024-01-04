#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "CPP-CV-Elective-2022/analysis.h"
#include "CPP-CV-Elective-2022/filters.h"

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
string image_path; 												// Path to image	

Mat img;

int main() {
	image_path = path + "italy.jpg"; 										// Path to image
	img = imread(image_path, IMREAD_COLOR); 									// Read the file
	if (img.empty()) { 													// Check for invalid input
		cout << "Could not open or find the image" << endl;
		return 0;
	}

	split(img, bgr_planes );

	bool uniform = true, accumulate = false;
	
	calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }

	imshow("Original", histImage); 												// Show our image inside it.
	waitKey(0); 			
	return 0;				
}

/*
Mat img_HSV, frame_threshold;											// Create Mat objects for HSV image and thresholded image
Mat hsvImage; 															// Create a new empty image
cvtColor(img, hsvImage, COLOR_BGR2HSV); 								// Convert to HSV
Mat mask; 																// Create a new empty image
inRange(hsvImage, Scalar(0, 100, 100), Scalar(150, 255, 255), mask); 	// Apply threshold - first scalar is lower bound, second scalar is upper bound
Mat result;																// Create a new empty image
bitwise_and(img, img, result, mask); 									// Apply mask
imshow("Lena", result); 												// Show the image
waitKey(0); 															// Wait for keypress
}
*/
