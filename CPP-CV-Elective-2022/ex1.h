#pragma once

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// Exercise 1

void looper() {
    int number = 5;

    for (int i = 0; i < 100; i++) {
        if (number > 999) {
            cout << number / 2 << endl;
            break;
        }
        else {
            number = number * 2;
        }
    }
}

// Exercise 2 - 4

void average_gray_value(Mat src) {

    int pixvalue = 0, average, count = 0;

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            pixvalue = pixvalue + src.at<uchar>(j, i);
            count += 1;
        }
    }

    average = pixvalue / count;

    // Alt Scalar mean = mean(src);

    cout << average << endl;
}

// Exercise 5

void average_rgb(Mat src) {
    Mat channels[3];

    split(src, channels);

    Scalar blue_mean = mean(channels[0]);
    Scalar green_mean = mean(channels[1]);
    Scalar red_mean = mean(channels[2]);

    cout << "Mean of blue channel is: " << blue_mean << endl;
    cout << "Mean of green channel is " << green_mean << endl;
    cout << "Mean of red channel is " << red_mean << endl;
}

// Exercise 6-7

void channel_thresh(Mat src) {
    // Simple way
    Mat threshold, blue_thresh, green_thresh, red_thresh, new_image;
    new_image.create(src.size(), src.type());
    inRange(src, Scalar(0, 50, 50), Scalar(255, 200, 200), threshold);
    bitwise_and(src, src, new_image, threshold);
    imshow("Thresholded image", new_image);
    waitKey(0);

    // Hard way

    Mat blue, green, red;
    vector<Mat> channels(3);
    split(src, channels);

    blue = channels[0];
    green = channels[1];
    red = channels[2];
    
    inRange(blue, 0, 200, channels[0]);
    inRange(green, 0, 200, channels[1]);
    //inRange(red, 0, 200, channels[2]);

    merge(channels, src);
}