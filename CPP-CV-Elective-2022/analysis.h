#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

static void* Histogram_gray(Mat src) {
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange[] = { range };
	bool uniform = true, accumulate = false;
	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	Mat hist;
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, histRange, uniform, accumulate);
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("Source image", src);
	imshow("calcHist Demo", histImage);
	waitKey();
	return EXIT_SUCCESS;
}

static void* Histogram_color(Mat src) {
    vector<Mat> bgr_planes;

    split(src, bgr_planes);

    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;

    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++)
    {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
            Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
            Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
            Scalar(0, 0, 255), 2, 8, 0);
    }

    imshow("Source image", src);
    imshow("calcHist Demo", histImage);
    waitKey();
    return EXIT_SUCCESS;
}

Mat apply_mask(Mat& src, Mat& mask, Mat& result) {
    src.copyTo(result, mask);
    return result;
}

void examine_colors(Mat src) {
    Mat masked_img, mask, imghsv, result;
    int bmin = 0, gmin = 110, rmin = 153;
    int bmax = 19, gmax = 240, rmax = 255;
    //cvtColor(src, imghsv, COLOR_BGR2HSV);

    namedWindow("Trackbars", (640, 200));
    createTrackbar("Blue min", "Trackbars", &bmin, 255);
    createTrackbar("Blue max", "Trackbars", &bmax, 255);
    createTrackbar("Green min", "Trackbars", &gmin, 255);
    createTrackbar("Green max", "Trackbars", &gmax, 255);
    createTrackbar("Red min", "Trackbars", &rmin, 255);
    createTrackbar("Red max", "Trackbars", &rmax, 255);

    while (true) {
        Scalar lower(bmin, gmin, rmin);
        Scalar upper(bmax, gmax, rmax);

        inRange(src, lower, upper, mask);
        apply_mask(src, mask, masked_img);

        imshow("Source image", src);
        imshow("Image mask", mask);
        imshow("Masked image", masked_img);

        waitKey(1);
    }
}
