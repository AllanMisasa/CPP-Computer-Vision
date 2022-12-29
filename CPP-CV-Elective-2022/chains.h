#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
Mat preprocessing(Mat img) {
    Mat imgGray, imgBlur, edges, dilated;
    //cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, edges, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    //dilate(edges, dilated, kernel);
    //erode(dilated, eroded, kernel);
    return edges;
}
