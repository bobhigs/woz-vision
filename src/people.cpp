#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

vector<Rect> detectPeople(Mat frame);

// int main(int argc, char** argv) {

// 	// HOGDescriptor hog;
// 	// hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
// 	vector<Rect> peopleLocations;

// 	// Mat originalImage;
// 	// Mat resizedImage;
// 	// const static Scalar colors[] =  { CV_RGB(0,0,255),CV_RGB(0,255,0),CV_RGB(255,0,0),CV_RGB(255,255,0),CV_RGB(255,0,255),CV_RGB(0,255,255),CV_RGB(255,255,255),CV_RGB(128,0,0),CV_RGB(0,128,0),CV_RGB(0,0,128),CV_RGB(128,128,128),CV_RGB(0,0,0)};

// 	// String imagePath = String(argv[1]);

// 	// originalImage = imread(imagePath, IMREAD_COLOR);
// 	// // resizes the images
// 	// resize(originalImage, resizedImage, Size(), .1, .1, CV_INTER_LINEAR);

// 	// hog.detectMultiScale(originalImage, peopleLocations, 0, Size(8,8), Size(32,32), 1.05, 2);
// 	peopleLocations = printRect();
// 	// draws rectangles
// 	for( vector<Rect>::const_iterator it = peopleLocations.begin(); it != peopleLocations.end(); it++ )
// 	{
// 		//rectangle(originalImage, *it, CV_RGB(0,0,255), 3, 8, 0);
// 		cout << *it << endl;
// 	}
// 	// namedWindow("display_output");
// 	// imshow("display_output",originalImage);
// 	// waitKey(0);

// 	return 0;
// }

vector<Rect> detectPeople(Mat frame) {

	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	//Mat originalImage;
	Mat resizedImage;
	//Mat frame;
	vector<Rect> peopleLocations;

	//String imagePath = String(frame);

	//originalImage = imread(imagePath, IMREAD_COLOR);
	// resizes the images
	resize(frame, resizedImage, Size(), .5, .5, CV_INTER_LINEAR);

	hog.detectMultiScale(resizedImage, peopleLocations, 0, Size(4,4), Size(8,8), 1.05, 2);
	// groupRectangles(peopleLocations, 5);

	return peopleLocations;

}