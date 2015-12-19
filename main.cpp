//
// Created by owl on 8/21/15.
//

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String cascade_name;
CascadeClassifier cascade;
string window_name = "Classifier test: ";
RNG rng(12345);

/** @function main */
int main( int argc, const char** argv )
{
    VideoCapture capture(-1);
    Mat frame;

   if (argc != 2) { 
       printf("Usage: classifier_test <classifier.xml>\n");
       return -1;
   }
   else { 
		cascade_name = argv[1]; 
   		cout << "Loading " << cascade_name << " ..." << endl;
   };
   
    //-- 1. Load the cascades
    if( !cascade.load( cascade_name ) ) {printf("--(!)Error loading classifier. Exiting\n"); return -1; };
    window_name += cascade_name;

    //-- 2. Read the video stream
    
    if( capture.isOpened() )
    {
        while( true )
        {
            capture.read(frame);

            //-- 3. Apply the classifier to the frame
            if( !frame.empty() )
            { detectAndDisplay( frame ); }
            else
            { printf(" --(!) No captured frame -- Break!"); break; }

            int c = waitKey(10);
            if( (char)c == 'c' ) { break; }
        }
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> objectsDetected;
    Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Run classifierC++:
    // void CascadeClassifier::
    // detectMultiScale(const Mat& image,
    // vector<Rect>& objects,
    // double scaleFactor=1.1,
    // int minNeighbors=3,
    // int flags=0,
    // Size minSize=Size(),
    // Size maxSize=Size())
    cascade.detectMultiScale( frame_gray, objectsDetected, 1.1, 10 );

    for( size_t i = 0; i < objectsDetected.size(); i++ )
    {
        Point center( objectsDetected[i].x + objectsDetected[i].width*0.5, objectsDetected[i].y + objectsDetected[i].height*0.5 );
        //ellipse( frame, center, Size( objectsDetected[i].width*0.5, objectsDetected[i].height*0.5), 0, 0, 360, , 4, 8, 0 );
        Point topLeft (objectsDetected[i].x, objectsDetected[i].y);
        Point bottomRight(topLeft.x + objectsDetected[i].width, topLeft.y + objectsDetected[i].height);
        rectangle( frame, topLeft, bottomRight, Scalar( 0, 0, 255 ), 3);

        /*
        String topLabel = cascade_name;
        topLabel += ": " + i;

        int fontScale = objectsDetected[i].height / 150;
        String bottomLabel =  " x ";
        bottomLabel.push_back(objectsDetected[i].width);
        bottomLabel.append(objectsDetected[i].height);
        putText(frame, topLabel, topLeft, FONT_HERSHEY_PLAIN, fontScale, 1);
        putText(frame, bottomLabel, Point (bottomRight.x - bottomLabel.length(), bottomRight.y), FONT_HERSHEY_PLAIN, fontScale, 1);
        */



    }
    //-- Show what you got
    imshow( window_name, frame );
}
