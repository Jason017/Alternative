//
// Created by jason on 1/23/21.
//

#include "TargetDetector.h"

vector<vector<Point>> TargetDetector::find(Mat frame) {
    while (true) {
        if (frame.empty())
            break;
        cvtColor(frame, frame, COLOR_BGR2RGB);

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
    }
}

float TargetDetector::accuracy() {

}

vector<Mat> TargetDetector::missedFrames() {

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

