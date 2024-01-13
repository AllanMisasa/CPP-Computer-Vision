#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/features2d.hpp>
#include <tesseract/baseapi.h>
#include <iostream>

using namespace std;
using namespace cv;

void tess(Mat src) {
    string outText;
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);  // Init tesseract to use English (eng) and the LSTM OCR engine only.
    ocr->SetPageSegMode(tesseract::PSM_AUTO);  
    ocr->SetImage(src.data, src.cols, src.rows, 3, src.step);
    outText = string(ocr->GetUTF8Text());
    cout << outText << endl;
    ocr->End();
}

g++ main.cpp -o output `pkg-config --cflags --libs opencv4 tesseract` -std=c++17 && ./output