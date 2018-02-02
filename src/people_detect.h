//
// Created by Michael Newton on 2/1/18.
//

#ifndef WOZ_VISION_PEOPLE_DETECT_H
#define WOZ_VISION_PEOPLE_DETECT_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace std::chrono;


class PeopleDetect {
public:
    PeopleDetect();
    void detectPeople(Mat frame, vector<Rect> &output);
private:
    void detectWithCascadeFullBody(Mat frame, vector<Rect> &output);
    void detectWithCascadeUpperBody(Mat frame, vector<Rect> &output);
    void detectPeopleDefaultPeopleDetector(Mat frame, vector<Rect> &output);

    CascadeClassifier fullBodyCascade;
    CascadeClassifier upperBodyCascade;
    HOGDescriptor peopleHog;
    static constexpr double resizePercentage = .4;
};

#endif //WOZ_VISION_PEOPLE_DETECT_H
