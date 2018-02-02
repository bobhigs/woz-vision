#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>
#include "people_detect.h"

using namespace cv;
using namespace std;
using namespace std::chrono;

PeopleDetect::PeopleDetect() {
	fullBodyCascade.load("haarcascade_fullbody.xml");
	upperBodyCascade.load("haarcascade_upperbody.xml");
	peopleHog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

void PeopleDetect::detectPeople(Mat frame, vector<Rect> &output) {
	Mat modified;
	cvtColor(frame, modified, CV_BGR2GRAY);
	resize(modified, modified, Size(), resizePercentage, resizePercentage, CV_INTER_LINEAR);
	equalizeHist(modified, modified);
	

	long long T1 = (duration_cast< milliseconds >(system_clock::now().time_since_epoch())).count();
//  detectWithCascadeFullBody(frame, output); //TODO: pretty sure if you run multiple of these, they will overwrite each other
//	detectWithCascadeUpperBody(frame, output);
    detectPeopleDefaultPeopleDetector(modified, output);
	long long T2 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
	cout << "detect_people -> " << (T2 - T1) << endl;

	for (auto &rect : output) {
        rect.x /= resizePercentage;
        rect.y /= resizePercentage;
        rect.width /= resizePercentage;
        rect.height /= resizePercentage;
	}
}


void PeopleDetect::detectWithCascadeFullBody(Mat frame, vector<Rect> &output) {
	fullBodyCascade.detectMultiScale(frame, output, 1.1, 2, 0, Size(10,10));
}

void PeopleDetect::detectWithCascadeUpperBody(Mat frame, vector<Rect> &output) {
	upperBodyCascade.detectMultiScale(frame, output, 1.1, 2, 0, Size(10,10));
}

void PeopleDetect::detectPeopleDefaultPeopleDetector(Mat frame, vector<Rect> &output) {
	peopleHog.detectMultiScale(frame, output, 0, Size(4,4), Size(4,4), 1.1, 2);
	// groupRectangles(peopleLocations, 5);
}