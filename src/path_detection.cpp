//

// Created by Michael Newton on 2/16/17.

//

//STD includes
#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <stdlib.h>


//CV includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>

//Namespaces
using namespace std;
using namespace cv;

//Function protoypes

//Mouse click event
void mouse_callback(int event, int x, int y, int flag, void *param);

//Operations on the frames
void Erosion(int, void*);
void Dilation(int, void*);
//Debug functions
void debugPrint(MatSize toPrint);
void debugPrint(string toPrint);
void debugPrint(int toPrint);
void debugPrint(Size toPrint);

//Vars/consts
int low_r = 140, low_g = 140, low_b = 140;
int high_r = 250, high_g = 250, high_b = 250;
int blur_size = 6;
//Used to draw the rectangle on the screen
const int rect_top_left[] = {300, 250};
const int rect_bot_right[] = {450, 400};
//Used for the erosion and dilation functions
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 2;
int dilation_size = 4;
//Used for the debugPrint functions
bool debugOutput = false;

int cameraSource = -1;
string videoPath = "";


//Mats
Mat frame_threshold, img, orig_img, frame;

int main(int argc, char** argv)
{



	//Runs through the commandline arguments
	for (int i = 2; i < argc; i++) {
		if (strcmp(argv[i], "-debug") == 0) {
			debugOutput = true;
		}
	}

	//checks the first commandline arg to see if it is a file or a number
	if (isdigit(argv[1][0])) {
		cameraSource = atoi(argv[1]);
	} else {
		videoPath = argv[1];
	}

	VideoCapture cap;
	
	//if cameraSource is negitive then opens from a file. If not then it opens the cameraSource camera.
	if (cameraSource < 0) {
		if (!cap.open(videoPath)) {
			cout << "Not Opened" << endl;
			return -1;
		}
	} else {
		cap.open(cameraSource);
	}


	
	//Opens two windows
	namedWindow("Video Capture", WINDOW_NORMAL);
	namedWindow("Object Detection", WINDOW_NORMAL);
	//reads the image in from the source dest
	
	

	//Loops through until the 'q' key is pressed
	while ((char)waitKey(1) != 'q') {

		//take in a frame from the video/feed cap
		cap >> frame;
		//print the frame size if debug is set true
		debugPrint(frame.size);


		//Should remove the break
		if (frame.empty())
			break;

		//blur the image to make edges less sharp
		blur(frame, frame, Size(blur_size + 1, blur_size + 1));
		//print frame size after blur if debug is true
		debugPrint(frame.size());
		Dilation(0, 0);
		
		//This is where the actaul color change happens to the path
		inRange(frame, Scalar(low_b, low_g, low_r), Scalar(high_b, high_g, high_r), frame_threshold);

		//Convert back to normal BGR color scheme to allow multicolor lines to be drawn for visual sake
		cvtColor(frame_threshold, orig_img, COLOR_GRAY2BGR);
		//create a rectangle to visualize space that we will do tests on
		//rectangle(orig_img, Point(rect_top_left[0], rect_top_left[1]), Point(rect_bot_right[0], rect_bot_right[1]), Scalar(255, 0, 0));

		//if the users presses space then we print the size of the Mat
		if (GetKeyState(VK_SPACE) & 0x8000) {
			cout << "Frame Threshold: " <<frame_threshold.size << endl;
			cout << "Frame: " << frame.size << endl;
		}

		//show the frames
		imshow("Video Capture", frame);
		imshow("Object Detection", orig_img);

		//Bind the mouse event
		setMouseCallback("Object Detection", mouse_callback);
	}


	return 0;

}


//Print statments that only print if the -debug flag has been added to the command line
void debugPrint(string toPrint) {
	if (debugOutput) {
		cout << "[Debug] " << toPrint << endl;
	}
}

void debugPrint(int toPrint) {
	if (debugOutput) {
		cout << "[Debug] " << toPrint << endl;
	}
}

void debugPrint(MatSize toPrint) {
	if (debugOutput) {
		cout << "[Debug] " << toPrint << endl;
	}
}

void debugPrint(Size toPrint) {
	if (debugOutput) {
		cout << "[Debug] " << toPrint << endl;
	}
}

//Mouse click event
void mouse_callback(int event, int x, int y, int flag, void *param) {
	if (event == EVENT_LBUTTONDOWN) {
		cout << "(" << x << ", " << y << ")" << endl;
	}
}


void Erosion(int, void*) {
	int erosion_type;
	if (erosion_elem == 0) {
		erosion_type = MORPH_RECT;

	} else if (erosion_elem == 1) {
		erosion_type = MORPH_CROSS;

	} else if (erosion_elem == 2) {
		erosion_type = MORPH_ELLIPSE;
	}
	Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));

	// Apply the erosion operation    
	erode(frame, frame, element);

}



void Dilation(int, void*) {
	int dilation_type;
	if (dilation_elem == 0) {
		dilation_type = MORPH_RECT;
	} else if (dilation_elem == 1) {
		dilation_type = MORPH_CROSS;
	} else if (dilation_elem == 2) {
		dilation_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	// Apply the dilation operation    
	dilate(frame, frame, element);
}