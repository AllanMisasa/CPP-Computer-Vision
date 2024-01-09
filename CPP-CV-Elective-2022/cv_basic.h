#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "filters.h"
#include "detectors.h"

using namespace cv;
using namespace std;

Mat temp, src, src_gray, imgGray, imgBlur, dst, edges, dilated, eroded;

Mat resize_image(Mat src, int width, int height)
{
	Mat resized_down;
	resize(src, resized_down, Size(width, height), INTER_LINEAR);
	return resized_down;
}

void video_background_replace() {

    src = imread("C:/opencv_images/stars_bg.jpg", IMREAD_COLOR);
    VideoCapture cap("C:/opencv_videos/justdoit.avi");

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
    }

    while (1) {
        Mat frame, hsv, mask, res;
        cap >> frame;               // Capture frame-by-frame
        if (frame.empty()) {        // Break if no frame
            break;
        }

        res = backgroundRemovalSimple(frame, src);
        imshow("Frame", res);     // Display frame

        char c = (char)waitKey(25);
        if (c == 27) {            // Break if user press escape
            break;
        }
    }
    cap.release();
    destroyAllWindows();
}

void video_edge_detection() {
    VideoCapture cap("C:/opencv_videos/justdoit.avi");

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
    }

    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    VideoWriter video("C:/portfolio_images/outcpp.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 24, Size(frame_width, frame_height));
    int counter = 0;
    while (true) {
        Mat frame, processed, contoured, res;
        cap.read(frame);               // Capture frame-by-frame
        counter++;
        if (frame.empty()) {           // Break if no frame
            break;
        }
        if (counter % 24 == 0) {
            processed = preprocessing(frame);
            contoured = extractContours(processed);
            video.write(frame);
        }
    }

    cap.release();
    video.release();
    destroyAllWindows();
}

void draw_rectangle(Mat src) {
    Point p1(30, 30);
    Point p2(255, 255);
    int thickness = 2;
    rectangle(src, p1, p2, Scalar(255, 0, 0), thickness);
    imshow("Overdrawn image", src);
    waitKey(0);
}

void draw_circle(Mat src) {
    Point center(100, 100);
    int radius = 50;
    Scalar line_color(0, 0, 0);
    int thickness = 2;
    circle(src, center, radius, line_color, thickness);
}

void draw_line(Mat src) {
    Point start(0, 0), end(250, 250);
    int thickness = 2;
    line(src, start, end, Scalar(255, 255, 255)); //LINE_8 as additional param
}

void video_player() {
    VideoCapture cap(0); // Use webcam as input

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
    }

    while (1) {
        Mat frame, hsv, mask, res;
        cap >> frame;               // Capture frame-by-frame
        if (frame.empty()) {        // Break if no frame
            break;
        }

        imshow("Frame", frame);     // Display frame

        char c = (char)waitKey(25);
        if (c == 27) {            // Break if user press escape
            break;
        }
    }
    cap.release();
    destroyAllWindows();
}

Mat blend_images(Mat img1, Mat img2) {
    Mat blended;
    double alpha = 0.5;  
    double beta = (1.0 - alpha);

    addWeighted(img1, alpha, img2, beta, 0.0, blended);

    return blended;
}