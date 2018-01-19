#include <iostream>
#include <stdlib.h>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv/cv.hpp"

using namespace std;
using namespace cv;

void on_low_r_thresh_trackbar(int, void *);
void on_high_r_thresh_trackbar(int, void *);
void on_low_g_thresh_trackbar(int, void *);
void on_high_g_thresh_trackbar(int, void *);
void on_low_b_thresh_trackbar(int, void *);
void on_high_b_thresh_trackbar(int, void *);
void on_blur_trackbar(int, void *);

int low_r=0, low_g=0, low_b=0;
int high_r=120, high_g=255, high_b=95;
int blur_size = 9;

Mat frame_threshold, img, orig_img, frame;

int main(int argc, char** argv)
{
    VideoCapture cap;
    const string source = argv[1];

    if (!cap.open(source)) {
        cout << "Not Opened" << endl;
        return -1;
    }

    // -- Video Out Stuff

    string::size_type pAt = source.find_last_of('.');                  // Find extension point
    const string NAME = source.substr(0, pAt) + "-new.avi";   // Form the new name with container
    int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form

    // Transform from int to char via Bitwise operators
    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};


//    Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
//                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));

    Size S = Size(225,400);

    VideoWriter outputVideo;
    outputVideo.open(NAME, ex, cap.get(CV_CAP_PROP_FPS), S, false);

    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << source << endl;
        return -1;
    }

    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << cap.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    cout << "Input codec type: " << EXT << endl;

    // -- End Video Out Stuff


    namedWindow("Video Capture", WINDOW_NORMAL);
    namedWindow("Object Detection", WINDOW_NORMAL);

//    orig_img = imread(source);


    //-- Trackbars to set thresholds for RGB values

    createTrackbar("Low R","Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
    createTrackbar("High R","Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
    createTrackbar("Low G","Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
    createTrackbar("High G","Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
    createTrackbar("Low B","Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
    createTrackbar("High B","Object Detection", &high_b, 255, on_high_b_thresh_trackbar);
    createTrackbar("Blur Size", "Object Detection", &blur_size, 19, on_blur_trackbar);

    int frameCount = 0;
    while((char)waitKey(1)!='q'){
//    while (true) {
        cap >> frame;

        if(frame.empty())
            break;

        frameCount++;

        cout << "in loop" << endl;
        //rotate image
        transpose(frame, frame);
        flip(frame, frame, 1);
        resize(frame, frame, Size(225,400));

        cout << "after transpose" << endl;
        medianBlur(frame, frame, (blur_size * 2) + 1);
        cout << "after blur" << endl;

        //-- Detect the object based on RGB Range Values
        inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
        cout << "after inRange" << endl;

        //-- Show the frames
        imshow("Video Capture",frame);
        imshow("Object Detection",frame_threshold);
        cout << "after imshow" << endl;

        outputVideo << frame_threshold;
        cout << "after write" << endl;
//        waitKey(0);
    }

    outputVideo.release();
    cout << "Frames: " << frameCount << endl;

    cout << "CV Frames: " << (int)cap.get(CV_CAP_PROP_FRAME_COUNT) << endl;



/*
    blur(orig_img, img, Size(blur_size+1, blur_size+1));

    inRange(img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);

    //-- Show the frames

    imshow("Video Capture", orig_img);

    imshow("Object Detection",frame_threshold);



    waitKey(0);


*/
    return 0;

}

void on_low_r_thresh_trackbar(int, void *)
{
    low_r = min(high_r-1, low_r);
    setTrackbarPos("Low R","Object Detection", low_r);

    inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
    imshow("Object Detection", frame_threshold);

}

void on_high_r_thresh_trackbar(int, void *)
{
    high_r = max(high_r, low_r+1);
    setTrackbarPos("High R", "Object Detection", high_r);


    inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
    imshow("Object Detection", frame_threshold);
}

void on_low_g_thresh_trackbar(int, void *)
{
    low_g = min(high_g-1, low_g);
    setTrackbarPos("Low G","Object Detection", low_g);

    inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
    imshow("Object Detection", frame_threshold);
}

void on_high_g_thresh_trackbar(int, void *)
{
    high_g = max(high_g, low_g+1);
    setTrackbarPos("High G", "Object Detection", high_g);

    inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
    imshow("Object Detection", frame_threshold);
}

void on_low_b_thresh_trackbar(int, void *)
{
    low_b= min(high_b-1, low_b);
    setTrackbarPos("Low B","Object Detection", low_b);

    inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
    imshow("Object Detection", frame_threshold);
}

void on_high_b_thresh_trackbar(int, void *)
{
    high_b = max(high_b, low_b+1);

    cout << "New Value: " << high_b << endl;

    setTrackbarPos("High B", "Object Detection", high_b);

    inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
    imshow("Object Detection", frame_threshold);
}

void on_blur_trackbar(int, void *) {

    cout << "blur Value: " << blur_size << endl;
    medianBlur(frame, frame, (blur_size * 2) + 1);
    inRange(frame, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),frame_threshold);
    imshow("Object Detection", frame_threshold);
}
