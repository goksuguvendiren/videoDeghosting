//
// Created by Göksu Güvendiren on 28/07/16.
//

#ifndef VIDEODEGHOSTING_DEGHOSTING_H
#define VIDEODEGHOSTING_DEGHOSTING_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <unordered_map>
#include <string>

#include "Video.h"

using std::unordered_map;
using std::string;

class Deghosting
{
    string _outputName;
    cv::VideoWriter _outputWriter;
    Video _outputVideo;
    Video _inputLow;
    Video _inputHigh;

    // camera response functions :
    unordered_map<double, double> _crfRed;
    unordered_map<double, double> _crfGreen;
    unordered_map<double, double> _crfBlue;

    // inverse camera response functions :
    unordered_map<double, double> _i_crfRed;
    unordered_map<double, double> _i_crfGreen;
    unordered_map<double, double> _i_crfBlue;

public:
    Deghosting(const string& name) : _outputName(name) {}
    void Deghost(cv::VideoCapture& videoHigh, cv::VideoCapture& videoLow);
    void LoadCameraResponseFunctions();
    void MergeExposures(const Video& high, const Video& low);
    void AdjustExposure(double expRatio, Video& low);
    void WriteOutput();
    void ApplyInverseCameraResponse(cv::Vec3f& pix);
    void ApplyCameraResponse(cv::Vec3f& pix);
};


#endif //VIDEODEGHOSTING_DEGHOSTING_H
