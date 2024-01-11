#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "CPP-CV-Elective-2022/analysis.h"
#include "CPP-CV-Elective-2022/filters.h"
#include "CPP-CV-Elective-2022/thresholding.h"
#include "CPP-CV-Elective-2022/pipelines.h"
#include "CPP-CV-Elective-2022/cv_basic.h"

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
string image_path, image_path1, image_path2, image_path3; 												// Path to image

//const int max_value_H = 360/2;
//const int max_value = 255;
//int low_H = 0, low_S = 0, low_V = 0;
//int high_H = max_value_H, high_S = max_value, high_V = max_value;

Mat img, pcb, pcb2, out, opencv, thresholded, hsv, proc, proc2, gogh; 
Mat sobelx, sobely, sobelxy;
vector<vector<Point>> contour_test;
vector<vector<Point>> contour_template;


int main() {
    image_path = path + "italy.jpg"; 										// Path to image
    image_path1 = path + "pcb.jpg";
    image_path2 = path + "opencv.jpg";
    image_path3 = path + "pcb2.jpg";
	img = imread(image_path, IMREAD_COLOR); 									// Read the file
    pcb = imread(image_path1, IMREAD_COLOR);
    gogh = imread(image_path2, IMREAD_COLOR);   
    pcb2 = imread(image_path3, IMREAD_COLOR); 									// Read the file
    
    proc = preprocessing(pcb);
    proc2 = preprocessing(pcb2);
    //getContourAreas(proc, pcb2);

    contour_template = extractContours(pcb);
    contour_test = extractContours(img);
    cout << "Contour size of template: " << contour_template.size() << endl;
    //cout << "Template area: " << contourArea(contour_template[0]) << endl;

    for (int i = 0; i < contour_template.size(); i++) {
        cout << "Contour area of template: " << contourArea(contour_template[i]) << endl;
    }

    cout << "Contour size of test: " << contour_test.size() << endl;
    for (int i = 0; i < contour_test.size(); i++) {
        cout << "Contour area of test: " << contourArea(contour_test[i]) << endl;
    }
    
    matchContoursSimple(contour_template, contour_test);
}
