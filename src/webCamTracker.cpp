#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <deque>

using namespace cv;
using namespace std;

int main(int argc, char **argv ) {
	int maxLenth = 40; //max length of the trail
	//setting up the tracker with the MIL tracking algorithm
	Ptr<Tracker> tracker = TrackerKCF::create();
	
	//reading in webcam video
	VideoCapture stream1(0);
	namedWindow("Camera View", WINDOW_AUTOSIZE );

	//checking that the video stream has opened succesfully 
	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open camera";
	}

	deque<Rect2d> prevPoints;

	Mat frame;
	stream1.read(frame);

	Rect2d bbox(287, 23, 86, 320);

	// Uncomment the line below if you 
    // want to choose the bounding box
    bbox = selectROI(frame, false);

	tracker->init(frame, bbox);

	while (stream1.read(frame)) {
		tracker->update(frame, bbox);

		rectangle(frame, bbox, Scalar( 255, 0, 0), 2, 1);
		prevPoints.push_front(bbox);
		if(prevPoints.size() > maxLenth){
			prevPoints.pop_back();
		}
		//Draw a trail of circles at all of the recorded points
		for (int i = 0; i < prevPoints.size() && i < maxLenth; ++i) {
			circle(frame, cv::Point(int(prevPoints[i].x),int(prevPoints[i].y)), 20 - i/4, Scalar(0,0,255), -1, 8);
		}

		//stream1 >> frame;
		imshow("Tracking", frame);
		int k = waitKey(1);
        if(k == 27) break;
	}

	cout << CV_MAJOR_VERSION << CV_MINOR_VERSION;

	return(0);
}