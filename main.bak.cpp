#include <highgui.h>
#include <iostream>
#include <stdio.h>
#include <cv.h>

using namespace std;
using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage: classifier_test <path/to/classifier.xml>" << endl;
        return 0;
    }

    cvNamedWindow("classifier_test detecting camera", 1);
    // Capture images from any camera connected to the system
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);

    // Load the trained model
    CascadeClassifier classifier;
    classifier.load(argv[1]);

    if (classifier.empty()) {
        printf("Empty model.");
        return 0;
    }

    char key;
    while (true) {

        // Get a frame from the camera
        Mat frame = cvQueryFrame(capture);

        std::vector<Rect> objects;

        // Detect objects
        classifier.detectMultiScale(frame, objects, 1.1, 30,
                                        0 | CV_HAAR_SCALE_IMAGE, Size(200, 320));

        for (int i = 0; i < (int) objects.size(); i++) {
            Point pt1(objects[i].x, objects[i].y);
            Point pt2(objects[i].x + objects[i].width,
                      objects[i].y + objects[i].width);

            // Draw a rectangle around the detected brezel
            rectangle(frame, pt1, pt2, Scalar(0, 0, 255), 2);
            putText(frame, "Brezel", pt1, FONT_HERSHEY_PLAIN, 1.0,
                    Scalar(255, 0, 0), 2.0);

        }

        // Show the transformed frame
        imshow("Object detecting camera", frame);

        // Read keystrokes, exit after ESC pressed
        key = cvWaitKey(10);
        if (char(key) == 27) {
            break;
        }
    }

    return 0;
}
