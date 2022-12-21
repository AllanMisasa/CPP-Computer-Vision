#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "cvh.h"
#include "detectors.h"

using namespace cv;

Mat src, src_gray, dst; // Define image types

int main(int argc, char** argv) // arguments optional for command line parsing
{
    // CommandLineParser parser(argc, argv, "{@input | fruits.jpg | input image}");
    // std::string image_path = samples::findFile("starry_night.jpg");

    src = imread("C:/opencv_images/shapes.jpg", IMREAD_COLOR);  // Load source image as color
    if (src.empty())                                            // Exception handling if file is not found
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }
    //src = resize_image(src, 600, 400);
    // dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);                    // Convert image to grayscale
    //namedWindow(window_name, WINDOW_AUTOSIZE);
    //createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
    //CannyThreshold(0, 0);
    //waitKey(0);
    //return 0;
    circle_detector(src_gray);
}