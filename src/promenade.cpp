#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void findRed(Mat image);

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: promenade.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    findRed(image);

    return 0;
}

void findRed(Mat image)
{

    Mat3b hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);

    Mat mask1, mask2;

    inRange(hsv, Scalar(0, 0, 10), Scalar(10, 255, 255), mask1);
    //inRange(hsv, Scalar(70, 0, 10), Scalar(255, 255, 255), mask2);

    Mat1b mask = mask1;// | mask2;



    namedWindow("Promenade", WINDOW_AUTOSIZE );
    imshow("Promenade", mask);
    waitKey();
}
