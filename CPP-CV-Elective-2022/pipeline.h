#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>

using namespace std; 													// Standard C++ namespace
using namespace cv; 	

Mat edges;
Mat opencv_filtered;

Mat edge(Mat src) {
    opencv_filtered = edge_filter(src);
    //corner_detection(opencv_filtered);

    GaussianBlur(src, src, Size(5, 5), 0);
    imwrite("images/opencv_filtered.jpg", opencv_filtered);
    Canny(src, edges, 160, 220, 3, false);
    imwrite("images/opencv_canny.jpg", edges)

    imshow("Canny", edges);
    imshow("original", src);

    waitKey();
    return edges;
}

