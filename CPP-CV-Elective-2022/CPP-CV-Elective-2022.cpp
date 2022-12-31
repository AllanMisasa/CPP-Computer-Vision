#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "basic.h"
#include "detectors.h"
#include "analysis.h"
#include "thresholding.h"
#include "chains.h"
#include "filters.h"

using namespace cv;

Mat temp, src, src_gray, imgGray, imgBlur, dst, edges, dilated, eroded; // Define image types

void document_scanner() {
    src = imread("C:/opencv_images/shapes_color.jpg");

}


void images() {
    // CommandLineParser parser(argc, argv, "{@input | fruits.jpg | input image}");
// string image_path = samples::findFile("starry_night.jpg");

    src = imread("C:/opencv_images/pills.jpg", IMREAD_GRAYSCALE);  // Load source image as color
    if (src.empty())                                            // Exception handling if file is not found
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        //std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
    }

    temp = imread("C:/opencv_images/pill.jpg");
    Histogram_gray(src);
    // temp = preprocessing(temp);
     //temp = resize_image(temp, 256, 256);

     //src = preprocessing(src);

     //match(src, temp);

     //src = resize_image(src, 600, 400);
     // dst.create(src.size(), src.type());
     //cvtColor(src, src_gray, COLOR_BGR2GRAY);                    // Convert image to grayscale
     //namedWindow(window_name, WINDOW_AUTOSIZE);
     //createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
     //CannyThreshold(0, 0);
     //waitKey(0);
     //return 0;
     //circle_detector(src_gray);
     //Histogram_color(src);
     //Blob_detector(src_gray);
     //OtsuThreshold(src);
     //examine_colors(src);
     //contours(src);
}

void videos() {
    src = imread("C:/opencv_images/stars_bg.jpg", IMREAD_COLOR);
    VideoCapture cap("C:/opencv_videos/justdoit.avi");

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
    }

    while (1) {
        Mat frame, mask, res;
        cap >> frame;               // Capture frame-by-frame
        if (frame.empty()) {        // Break if no frame
            break;
        }

        inRange(frame, Scalar(90, 0, 0), Scalar(150, 255, 255), mask);

        //frame = frame - res;
        frame.setTo(Scalar(0, 0, 0), mask);
        bitwise_and(frame, src, res, mask = mask);
        imshow("Frame", res);     // Display frame

        char c = (char)waitKey(25);
        if (c == 27) {              // Break if user press escape
            break;
        }
    }
    cap.release();
    destroyAllWindows();
}

int main(int argc, char** argv)     // Arguments optional for command line parsing
{
    //images();
    videos();
}