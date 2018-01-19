#include <iostream> 
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp> 
#include <opencv/cv.hpp> 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



using namespace std; 
using namespace cv; 

Mat src; Mat src_gray;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void contours(int );

 
int main(int argc, char** argv) { 

    // Load source image and convert it to gray
    //src_gray = imread( argv[1], 1 );


    //string src = argv[1];

    VideoCapture vc;

    if (!vc.open(argv[1])) {        
    	cout << "Not Opened" << endl;
        return -1;    
    }
    Mat frameRef;    
    namedWindow("Contours", CV_WINDOW_AUTOSIZE);    
   

    while (true) {        
    	vc >> frameRef;
    	if (frameRef.empty()) {            
    	   cout << "Done" << endl;            
       	   return 0;        
    	}  
	src_gray = frameRef;        
    	/// Convert image to gray and blur it
    	 //cvtColor( src, src_gray, CV_BGR2GRAY );
    	blur( src_gray, src_gray, Size(3,3) );
    	blur( src_gray, src_gray, Size(3,3) );
    	blur( src_gray, src_gray, Size(3,3) );
    	blur( src_gray, src_gray, Size(3,3) );
        //cvtColor( src_gray, frameRef, CV_BGR2GRAY );
      

        contours( 100 );
    	waitKey(0);    
    }        
    return 0; 
}




/** @function thresh_callback */
void contours(int thresh)
{
  Mat canny_output;
  vector<vector<Point> > contour;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contour, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contour.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contour, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
//  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}




