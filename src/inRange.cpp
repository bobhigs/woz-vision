//
// Created by Michael Newton on 2/16/17.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdlib.h>

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
int high_r=255, high_g=255, high_b=90;
int blur_size = 3;

Mat filtered_img, orig_img, blurred_img;
int main(int argc, char** argv)
{

    namedWindow("Original", WINDOW_NORMAL);
    namedWindow("Blurred", WINDOW_NORMAL);
    namedWindow("Filtered", WINDOW_NORMAL);

    orig_img = imread(argv[1]);

    //-- Trackbars to set thresholds for RGB values
    createTrackbar("Low R","Filtered", &low_r, 255, on_low_r_thresh_trackbar);
    createTrackbar("High R","Filtered", &high_r, 255, on_high_r_thresh_trackbar);
    createTrackbar("Low G","Filtered", &low_g, 255, on_low_g_thresh_trackbar);
    createTrackbar("High G","Filtered", &high_g, 255, on_high_g_thresh_trackbar);
    createTrackbar("Low B","Filtered", &low_b, 255, on_low_b_thresh_trackbar);
    createTrackbar("High B","Filtered", &high_b, 255, on_high_b_thresh_trackbar);
    createTrackbar("Blur Size", "Blurred", &blur_size, 19, on_blur_trackbar);


    //-- Blur and inRange
    medianBlur(orig_img, blurred_img, (blur_size * 2) + 1);
    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r), filtered_img);


    //-- Show the frames
    imshow("Original", orig_img);
    imshow("Blurred", blurred_img);
    imshow("Filtered",filtered_img);

    waitKey(0);

    return 0;
}
void on_low_r_thresh_trackbar(int, void *)
{
    low_r = min(high_r-1, low_r);
    setTrackbarPos("Low R","Filtered", low_r);

    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),filtered_img);
    imshow("Filtered", filtered_img);
}
void on_high_r_thresh_trackbar(int, void *)
{
    high_r = max(high_r, low_r+1);
    setTrackbarPos("High R", "Filtered", high_r);

    cout << "high_r: " << high_r << endl;

    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),filtered_img);
    imshow("Filtered", filtered_img);
}
void on_low_g_thresh_trackbar(int, void *)
{
    low_g = min(high_g-1, low_g);
    setTrackbarPos("Low G","Filtered", low_g);

    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),filtered_img);
    imshow("Filtered", filtered_img);
}
void on_high_g_thresh_trackbar(int, void *)
{
    high_g = max(high_g, low_g+1);
    setTrackbarPos("High G", "Filtered", high_g);

    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),filtered_img);
    imshow("Filtered", filtered_img);
}
void on_low_b_thresh_trackbar(int, void *)
{
    low_b= min(high_b-1, low_b);
    setTrackbarPos("Low B","Filtered", low_b);

    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),filtered_img);
    imshow("Filtered", filtered_img);
}
void on_high_b_thresh_trackbar(int, void *)
{
    high_b = max(high_b, low_b+1);

    cout << "New Value: " << high_b << endl;

    setTrackbarPos("High B", "Filtered", high_b);

    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),filtered_img);
    imshow("Filtered", filtered_img);
}

void on_blur_trackbar(int, void *) {
    cout << "blur: " << blur_size << endl;
    medianBlur(orig_img, blurred_img, (blur_size * 2) + 1);
    inRange(blurred_img, Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r), filtered_img);
    imshow("Blurred", blurred_img);
    imshow("Filtered", filtered_img);
}