#include <iostream>
#include <opencv2/opencv.hpp>

#include "Deghosting.h"
#include "Video.h"

using namespace std;
using namespace cv;

int main()
{
    cout << "Hello, World!" << endl;
    auto videoHigh = VideoCapture();
    auto videoLow = VideoCapture();

    videoHigh.open("/Users/goksu/Desktop/VideoDeghosting/InputVideos/towelHigh.mp4");
    videoLow.open("/Users/goksu/Desktop/VideoDeghosting/InputVideos/towelLow.mp4");

    if( !videoHigh.isOpened()) {
        cout << "Cannot open the video file" << endl;
        return -1;
    }

    Deghosting deghostedVideo("outputVideo.avi");
    deghostedVideo.Deghost(videoHigh, videoLow);

    videoHigh.release();
    videoLow.release();
    return 0;
}



//cap >> frame; // get a new frame from camera
//cvtColor(frame, edges, COLOR_BGR2GRAY);
//GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
//Canny(edges, edges, 0, 30, 3);