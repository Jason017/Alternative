//
// Created by jason on 1/23/21.
//

#ifndef OP_TARGETDETECTOR_H
#define OP_TARGETDETECTOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#endif //OP_TARGETDETECTOR_H

using namespace cv;
using namespace std;

class TargetDetector {
public:
    TargetDetector();

    vector<vector<Point>> find(Mat frame);

    float accuracy();

private:
    float found = 0;
    float notFound = 0;
    vector<Mat> missed;
    int R_min = 0, R_max = 233;
    int G_min = 171, G_max = 255;
    int B_min = 240, B_max = 255;

    bool contValid(vector<Point> contour);

    vector<Mat> missedFrames();
};