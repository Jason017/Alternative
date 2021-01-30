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
    Mat frame;
    VideoCapture cap("/home/jason/Desktop/IMG_0270.MOV");

    if (!cap.isOpened()) {
        cout << "cannot read or open the video" << endl;
        return -1;
    }

    while (true) {
        cap.read(frame);
        if (frame.empty())
            break;
        cvtColor(frame, frame, COLOR_BGR2RGB);
        pyrDown(frame, frame);

        vector<Mat> vec;
        split(frame, vec);
        Mat red = vec[0];
        Mat green = vec[1];
        Mat blue = vec[2];
        threshold(red, red, R_max, 255, THRESH_TRUNC);
        threshold(red, red, R_min, 255, THRESH_TOZERO);
        threshold(green, green, G_max, 255, THRESH_TRUNC);
        threshold(green, green, G_min, 255, THRESH_TOZERO);
        threshold(blue, blue, B_max, 255, THRESH_TRUNC);
        threshold(blue, blue, B_min, 255, THRESH_TOZERO);

        namedWindow("RGB Threshold", WINDOW_NORMAL);
        createTrackbar("R_max", "RGB Threshold", &R_max, 255);
        createTrackbar("R_min", "RGB Threshold", &R_min, R_max);
        createTrackbar("G_max", "RGB Threshold", &G_max, 255);
        createTrackbar("G_min", "RGB Threshold", &G_min, G_max);
        createTrackbar("B_max", "RGB Threshold", &B_max, 255);
        createTrackbar("B_min", "RGB Threshold", &B_min, B_max);

        Mat output;
        inRange(frame, Scalar(0, 0, B_min), Scalar(255, 255, B_max), output);
        Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(2, 2));
        dilate(output, output, element);
        dilate(output, output, element);
        erode(output, output, element);
        erode(output, output, Mat());
        imshow("Threshold Window", output);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++) {
            if (contValid(contours[i])) {
                Point2f vertices[4];
                RotatedRect rect = minAreaRect(contours[i]);
                rect.points(vertices);
                for (int j = 0; j < 4; j++) {
                    line(frame, vertices[j], vertices[(j + 1) % 4], Scalar(255, 0, 0), 3);
                }
                float parent_area = contourArea(contours[i]);
                int cur_childIndx = hierarchy[i][2];
                if (cur_childIndx == -1) {
                    continue;
                }
                bool found = false;
                float cp_areaRatio = 0;
                while (!found) {
                    vector<Point> cur_child = contours[cur_childIndx];
                    RotatedRect child_rect = minAreaRect(cur_child);
                    float a = child_rect.size.height;
                    float b = child_rect.size.width;
                    float dim_ratio = (a > b) ? (a / b) : (b / a);
                    cp_areaRatio = parent_area / contourArea(cur_child);
                    if ((dim_ratio > 1.6 && 2 > dim_ratio) && (cp_areaRatio > 2.9 && 3.7 > cp_areaRatio))
                        found = true;
                    if (hierarchy[cur_childIndx][0] == -1)
                        break;
                    else
                        cur_childIndx = hierarchy[cur_childIndx][0];
                }

                RotatedRect child_rect = minAreaRect(contours[cur_childIndx]);
                if (found) {
                    int cur_parentIndx = hierarchy[cur_childIndx][3];
                    circle(frame, child_rect.center, 4, Scalar(255, 0, 0), 3);
                }

            }
        }
        cvtColor(frame, frame, COLOR_BGR2RGB);
        imshow("Display Window", frame);
        waitKey(5);
    }
    return 0;
}

bool contValid(vector<Point> &contour) {
    float area = contourArea(contour);
    if (area < 500)
        return false;
    RotatedRect rect = minAreaRect(contour);
    float a = rect.size.height;
    float b = rect.size.width;
    float dim_ratio = (a > b) ? (a / b) : (b / a);
    if (dim_ratio < 1.9 || 2.3 < dim_ratio)
        return false;
    return true;
}
