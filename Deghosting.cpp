//
// Created by Göksu Güvendiren on 28/07/16.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Deghosting.h"

using namespace std;
using namespace cv;

void ByteToDouble()
{

}

void Deghosting::Deghost(cv::VideoCapture& videoHigh, cv::VideoCapture& videoLow)
{
    _outputWriter.open("/Users/goksu/Desktop/VideoDeghosting/InputVideos/" + _outputName, // I can only save .avi for now.
                       CV_FOURCC('M','J','P','G'),  // videoLow.get(CV_CAP_PROP_FOURCC);
                       videoLow.get(CV_CAP_PROP_FPS),
                       cv::Size((int)videoLow.get(CV_CAP_PROP_FRAME_WIDTH),
                            (int)videoLow.get(CV_CAP_PROP_FRAME_HEIGHT)),
                       true);

    _inputHigh   = Video("/Users/goksu/Desktop/VideoDeghosting/InputVideos/towelHigh.mp4", videoHigh, 5);
    _inputLow    = Video("/Users/goksu/Desktop/VideoDeghosting/InputVideos/towelLow.mp4", videoLow, 5);
    _outputVideo = Video("/Users/goksu/Desktop/VideoDeghosting/InputVideos/" + _outputName);

    LoadCameraResponseFunctions();

    ByteToDouble();

    // 2^expVal = expTime
    double val = 1.0 * 8.0;
    AdjustExposure(val, _inputLow);

    MergeExposures(_inputHigh, _inputLow);

    WriteOutput();
}

void Deghosting::WriteOutput()
{
    for (int i = 0; i < _outputVideo.Frames().size(); i++){
        Mat fr = _outputVideo.Frames()[i];
        imshow("hai", fr);
        cv::waitKey(0);
        _outputWriter << fr;
    }
}

void Deghosting::LoadCameraResponseFunctions()
{
    ifstream textFile;
    textFile.open("/Users/goksu/Desktop/VideoDeghosting/CRFs.txt");
    double value;
    vector<double> Ill;
    Ill.resize(1024);

    for (int i = 0; i < 1024; i++){     // read the illuminance values.
        textFile >> value;
        Ill[i] = value;
    }
    for (int i = 0; i < 1024; i++){     // read the brightness values.
        textFile >> value;
        _crfRed.insert(make_pair(Ill[i], value));
        _i_crfRed.insert(make_pair(value, Ill[i]));
    }

    for (int i = 0; i < 1024; i++){     // read the illuminance values.
        textFile >> value;
        Ill[i] = value;
    }
    for (int i = 0; i < 1024; i++){     // read the brightness values.
        textFile >> value;
        _crfGreen.insert(make_pair(Ill[i], value));
        _i_crfGreen.insert(make_pair(value, Ill[i]));
    }

    for (int i = 0; i < 1024; i++){     // read the illuminance values.
        textFile >> value;
        Ill[i] = value;
    }
    for (int i = 0; i < 1024; i++){     // read the brightness values.
        textFile >> value;
        _crfBlue.insert(make_pair(Ill[i], value));
        _i_crfBlue.insert(make_pair(value, Ill[i]));
    }
}

void Deghosting::MergeExposures(const Video& high, const Video& low)
{
//    cv::Mat frameHigh, frameLow;
//    //while(high.read(frameHigh) && low.read(frameLow)) {
    for (int i = 0; i < high.Frames().size(); i++){
        _outputVideo.Insert(low.Frames()[i]);
        _outputVideo.Insert(high.Frames()[i]);
    }
}

void Deghosting::ApplyInverseCameraResponse(cv::Vec3f& pix)
{
    pix[0] = _i_crfBlue[pix[0]];
    pix[1] = _i_crfGreen[pix[1]];
    pix[2] = _i_crfRed[pix[2]];
}

void Deghosting::ApplyCameraResponse(cv::Vec3f& pix)
{
    pix[0] = _crfBlue[pix[0]];
    pix[1] = _crfGreen[pix[1]];
    pix[2] = _crfRed[pix[2]];
}

void Deghosting::AdjustExposure(double expRatio, Video& low)
{
    for(int n = 0; n < low.Frames().size(); n++){
        auto& frame = low.Frames()[n];low.Frames()[n];
        for (int i = 0; i < frame.rows; i++){
            for (int j = 0; j < frame.cols; j++){
                auto& pixel = frame.at<cv::Vec3b>(i, j);   // get the pixel value   // THIS IS IN BGR SPACE !

                //ApplyInverseCameraResponse(pixel);

                pixel[0] = std::min(255., pixel[0] * expRatio);
                pixel[1] = std::min(255., pixel[1] * expRatio);
                pixel[2] = std::min(255., pixel[2] * expRatio);

                //ApplyCameraResponse(pixel);

                if (pixel[0] == 255 || pixel[1] == 255 || pixel[2] == 255){
                    //pixel[0] = 0; pixel[1] = 0; pixel[2] = 255  ;
                }

            }
        }
    }

}