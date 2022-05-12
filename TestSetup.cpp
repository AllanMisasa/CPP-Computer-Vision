/*

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

# include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	cv::CommandLineParser parser(argc, argv,
		"{@input | lena.jpg | input image}"
		"{ksize   k|1|ksize (hit 'K' to increase its value at run time)}"
		"{scale   s|1|scale (hit 'S' to increase its value at run time)}"
		"{delta   d|0|delta (hit 'D' to increase its value at run time)}"
		"{help    h|false|show help message}");

	cout << "The sample uses Sobel OpenCV functions for edge detection \n\n";
	parser.printMessage();
	cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values ( ksize will be -1 equal to Scharr function )";

	// First we declare the variables we will use
	Mat image, src, src_gray;
	Mat grad;
	const String window_name = "Sobel";
	int ksize = parser.get<int>("ksize");
	int scale = parser.get<int>("scale");
	int delta = parser.get<int>("delta");
	int ddepth = CV_16S;

	String imageName = parser.get<String>("@input");
	image = imread(samples::findFile(imageName), IMREAD_COLOR); // Load an image

	if (image.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		return EXIT_FAILURE;
	}
	for (;;)
	{
		// Remove noise by blurring with a Gaussian filter
		GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

		// Convert the image to grayscale
		cvtColor(src, src_gray, COLOR_BGR2GRAY);

		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;

		Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
		Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);

		// Converting back to CV_8U
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);

		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		imshow(window_name, grad);
		char key = (char)waitKey(0);

		if (key == 27)
			break;
		else if (key == 'k' || key == 'K')
			ksize = ksize < 30 ? ksize + 2 : -1;
		else if (key == 's' || key == 'S')
			scale = scale++;
		else if (key == 'd' || key == 'D')
			delta = delta++;
		else if (key == 'r' || key == 'R')
		{
			ksize = 1;
			scale = 1;
			delta = 0;
		}
	}
	return EXIT_SUCCESS;
}
*/