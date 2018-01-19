#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>

using namespace std;
using namespace cv;

void something(Mat &frameRef) {
    imshow("window", frameRef);
}

int main(int argc, char** argv) {
    string src = argv[1];
    VideoCapture vc;

    if (!vc.open(src)) {
        cout << "Not Opened" << endl;
        return -1;
    }


    Mat frameRef;

    namedWindow("window", CV_WINDOW_AUTOSIZE);

    while (true) {
        vc >> frameRef;

        if (frameRef.empty()) {
            cout << "Done" << endl;
            return 0;

        }


        something(frameRef);
        waitKey(0);
    }

    return 0;
}
