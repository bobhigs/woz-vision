#include <stdio.h>
#include <opencv2/opencv.hpp>
// #include <opencv2/tracking.hpp>
#include <deque>
#include <chrono>
#include "people_detect.h"

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    int maxLenth = 40; //max length of the trail
    //setting up the tracker with the MIL tracking algorithm
    // Ptr<Tracker> tracker = TrackerKCF::create();

    PeopleDetect PeopleDetect;

    long long prev = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();

    //reading in webcam video
//    VideoCapture stream1("http://10.5.5.9:8080/live/amba.m3u8");
//    VideoCapture stream1(0);
	VideoCapture stream1("people_walking.mp4");
    namedWindow("Camera View", WINDOW_AUTOSIZE);

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
    //boundingBoxes.push_back(selectROI(frame, false)); //choose the bounding box of object to track

    //send detected people's boxes into the

    // tracker->init(frame, bbox); //track bbox

    cout << frame.size() << endl;

    vector<Rect> boundingBoxes;
    while (stream1.read(frame)) {

        if (!frame.empty()) {
            vector<Rect> newpeople;
            PeopleDetect.detectPeople(frame, newpeople);
            long long current = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
            cout << "loop time -> " << current - prev << endl;
            prev = current;

            // vector<Rect> newpeople = detectWithCascade(frame);
            //check that none of the new detected people are already being tracked
            /*for(int i = 0; i < newpeople.size(); i++){
                bool intersect = false;
                for (int j = 0; j < boundingBoxes.size(); j++){
                    if ((newpeople[i] & boundingBoxes[j]).area() > 0){
                        intersect = true;
                        break;
                    }
                }
                if(!intersect)
                    boundingBoxes.push_back(newpeople[i]);
            }*/

            for (auto &personRect : newpeople) {
                bbox = Rect2d(personRect.x, personRect.y, personRect.width, personRect.height);

                // tracker->update(frame, bbox); //update the position tracking

                rectangle(frame, bbox, Scalar(0, 255, 0), 2, 1); //draw the bounding rectanle
            }

            /*for(int i = 0; i < boundingBoxes.size(); i++) {
                bbox = Rect2d(boundingBoxes[i]);

                tracker->update(frame, bbox); //update the position tracking

                rectangle(frame, bbox, Scalar( 255, 0, 0), 2, 1); //draw the bounding rectanle
            }*/
            prevPoints.push_front(bbox);
            if (prevPoints.size() > maxLenth) {
                prevPoints.pop_back();
            }

            cv::Point velocity;
            cv::Point currentPos = cv::Point(int(prevPoints[0].x + prevPoints[0].width / 2),
                                             int(prevPoints[0].y + prevPoints[0].height / 2));

            //Draw a trail of circles at all of the recorded points
            /*
            for (int i = 0; i < prevPoints.size() && i < maxLenth; ++i) {
                cv::Point pointI = cv::Point(int(prevPoints[i].x+prevPoints[i].width/2),int(prevPoints[i].y+prevPoints[i].height/2));
                circle(frame, pointI, 20 - i/4, Scalar(0,0,255), -1, 8);
                //weight makes more recent data more significant when calculating velocity
                float weight = 1/(i+1);
                int xvel = int((prevPoints[0].x-prevPoints[prevPoints.size()/3].x)*weight);
                int yvel = int((prevPoints[0].y-prevPoints[prevPoints.size()/3].y)*weight);
                velocity += cv::Point(xvel,yvel);
            }
            */
            arrowedLine(frame, currentPos, currentPos + velocity, Scalar(255, 0, 0), 10, 8, 0, 0.1);
        }

        imshow("Tracking", frame);
        int k = waitKey(1);
        if (k == 27) break;
    }

    cout << CV_MAJOR_VERSION << CV_MINOR_VERSION;

    return (0);
}