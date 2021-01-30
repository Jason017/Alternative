#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;


int main() {
    Mat test_image(200, 200, CV_8UC3, Scalar(0));
    RotatedRect rRect = RotatedRect(Point2f(100, 100), Size2f(100, 50), 30);
    Point2f vertices[4];
    rRect.points(vertices);
    for (int i = 0; i < 4; i++)
        line(test_image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
    Rect brect = rRect.boundingRect();
    rectangle(test_image, brect, Scalar(255, 0, 0), 2);
    imshow("rectangles", test_image);
    waitKey(0);
}
