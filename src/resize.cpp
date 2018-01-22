#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

void getimage(Mat src) //getting the input image
{

    if(! src.data )
    {
        cout <<  "src not filled" << endl ;
    }

    else
    {
        image_input = src.clone();
        storage = src.clone();              //initialising storage
        image_main_result = src.clone();    //initialising result

        cout << "got image" <<endl;
    }
}

void display_output()            //function to display output
{

    if(!image_main_result.empty() )
    {
        namedWindow("display_output");
        imshow("display_output",image_main_result);
        waitKey(0);
    }
}

void display_input()             // function to display input
{
    namedWindow("display_input");
    imshow("display_input",image_input);
    waitKey(0);
}


int main(int argc, char** argv) {
    Mat myImage;
    Mat myImage2;

    String inputFolder = String(argv[1]);
    String outputFolder = String(argv[2]);

    vector<String> filenames;
    String folder = String(argv[1]) + "/*.JPG";
    cout << "folder: " << folder << endl;
    glob(folder, filenames);

    for (vector<String>::const_iterator i = filenames.begin(); i != filenames.end(); ++i) {
        cout << *i << endl;
    }

    for(size_t i = 0; i < filenames.size(); i++)
    {
        // reads/opens an image
        myImage = imread(filenames[i], IMREAD_COLOR);
        // resizes the images
        resize(myImage, myImage2, Size(), .1, .1, CV_INTER_LINEAR);
        
        // error check here
        size_t found = filenames[i].find_first_of(inputFolder);
        // creates the new image names
        String image = String(string(filenames[i].c_str()).replace(found, inputFolder.length(), outputFolder));
        cout << "image: " << image << endl;

        imwrite(image, myImage2);       // saves the new image as the string image

    }

    return 0;
}


