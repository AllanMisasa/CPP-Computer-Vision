#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

Mat CannyThreshold(Mat src)
{
    Mat dst, detected_edges;
    int lowThreshold = 0;
    const int max_lowThreshold = 100;
    const int ratio = 3;
    const int kernel_size = 3;
    const char* window_name = "Edge Map";

    GaussianBlur(src, detected_edges, Size(3, 3), 0);
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    return dst;
}

Mat OtsuThreshold(Mat src) {
    Mat dst;
    int thresh = 0;
    int maxValue = 255;
    long double thres = threshold(src, dst, thresh, maxValue, THRESH_OTSU); // thres is the approximated threshold for Otsu
    cout << "Otsu threshold: " << thres << endl;                            // print approximated threshold
    return dst;
}