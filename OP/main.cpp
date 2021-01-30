#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#define ARM_CENTER_RATIO 3.3
#define BUFFER_SIZE 3
using namespace cv;
using namespace std;

int R_min = 0, R_max = 233;
int G_min = 171, G_max = 255;
int B_min = 240, B_max = 255;

bool contValid(vector<Point> &contour);

int main() {

}
