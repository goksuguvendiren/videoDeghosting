//
// Created by Göksu Güvendiren on 29/07/16.
//

#ifndef VIDEODEGHOSTING_VIDEO_H
#define VIDEODEGHOSTING_VIDEO_H

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

using cv::Mat;
using cv::VideoCapture;
using cv::VideoWriter;
using std::vector;
using std::string;

class Video
{
    vector<Mat> _frames;
    string _name;
public:
    Video(const string& name, VideoCapture& input, int numFrames = -1);
    Video(const string& name) : _name(name) {}
    Video() : _name("default.avi") {}

    vector<Mat>& Frames() { return _frames; }
    const vector<Mat>& Frames() const { return _frames; }
    void Insert(const Mat &frame) { _frames.push_back(frame); }
};


#endif //VIDEODEGHOSTING_VIDEO_H
