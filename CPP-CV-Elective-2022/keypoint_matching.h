#pragma once
#include <opencv2/video.hpp>
#include <opencv2/features2d.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat sift_keypoints(Mat image) {

	// Create a SIFT detector object
	Ptr<SIFT> detector = SIFT::create();

	// Detect keypoints in the image
	vector<KeyPoint> keypoints;
	detector->detect(image, keypoints);
	cout << "Number of SIFT keypoints, " << keypoints.size() << endl;
	// Draw the keypoints on the image
	Mat keypoint_image;
	drawKeypoints(image, keypoints, keypoint_image, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("Keypoints on image", keypoint_image);
	waitKey(0);

	return keypoint_image;
}

Mat sift_matching(Mat img1, Mat img2) {
	Ptr<SIFT> detector = SIFT::create();
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2, img_matches;

	detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
	detector->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	vector<vector<DMatch>> knn_matches;
	matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);

	const float ratio_thresh = 0.7f;
	vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);
		}
	}
	cout << "Of the SIFT keypoints, " << good_matches.size() << "matches were found after filtering with KNN" << endl;

	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches, Scalar::all(-1),
		Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("Good Matches", img_matches);
	waitKey();
	return img_matches;
}
