#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

using namespace cv;

Mat preprocessing(Mat img) {

    Mat imgGray, imgBlur, edges, dilated, eroded;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    //GaussianBlur(img, imgBlur, Size(5, 5), 3, 0);

    edgePreservingFilter(img, imgBlur, 1, 0.4);
    Canny(imgBlur, edges, 100, 255);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    dilate(edges, dilated, kernel);
    erode(dilated, eroded, kernel);
    //imwrite("C:/portfolio_images/image1.jpg", edges);
    return eroded;
}
