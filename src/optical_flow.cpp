//
// Created by Michael Newton on 10/31/16.
//
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

String window_name = "Capture - Optical Flow";

void optical_flow(Mat current_frame, Mat previous_frame);

int main() {

    VideoCapture capture;
    Mat current_frame, previous_frame;

    capture.open( 0 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
    capture.read(previous_frame);
    while (  capture.read(current_frame) ) {
        if( current_frame.empty() || previous_frame.empty() ) {
            printf(" --(!) No captured frame -- Break!");
            break;
        }




        optical_flow(current_frame, previous_frame);

        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }


    return 0;
}

void optical_flow(Mat current_frame, Mat previous_frame) {


    imshow( window_name, current_frame );
}
