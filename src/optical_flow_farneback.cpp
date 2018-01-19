//
// Created by Michael Newton on 11/2/16.
//

#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

void optical_flow(Mat current_frame, Mat previous_frame);

String window_name = "Optical Flow - Farneback";

int main() {

    VideoCapture capture;
    Mat current_frame, previous_frame;
    Mat magnitude, angle, flow;


    capture.open( 0 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
    capture.read(previous_frame);
    while (  capture.read(current_frame) ) {
        if( current_frame.empty() || previous_frame.empty() ) {
            printf(" --(!) No captured frame -- Break!");
            break;
        }


        cvtColor(current_frame, current_frame, CV_BGR2GRAY);


        calcOpticalFlowFarneback(previous_frame, current_frame, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
        cartToPolar(flow(Range::all(), Range(0,1)), flow(Range::all(), Range(1,2)), magnitude, angle);

        optical_flow(current_frame, previous_frame);

        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
        swap(current_frame, previous_frame);
    }



    return 0;
}


void optical_flow(Mat current_frame, Mat previous_frame) {


    imshow( window_name, current_frame );
}