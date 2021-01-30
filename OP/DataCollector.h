//
// Created by jason on 1/23/21.
//

#ifndef OP_DATACOLLECTOR_H
#define OP_DATACOLLECTOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#endif //OP_DATACOLLECTOR_H

using namespace cv;
using namespace std;

class DataCollector {
public:
    DataCollector();

    void readData(vector<Point> target, vector<Point> center, Mat frame);

    Point predictSin();

    Point predictConst();

    void changeType();

private:
    bool type = false; // true if sin, false if const.

}
