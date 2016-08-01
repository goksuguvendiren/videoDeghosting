//
// Created by Göksu Güvendiren on 29/07/16.
//

#include "Video.h"

Video::Video(const string &name, VideoCapture& input, int numOfFrames)
{
    _name = name;
    if (numOfFrames == -1) numOfFrames = (int) input.get(CV_CAP_PROP_FRAME_COUNT);

    for (int i = 0; i < numOfFrames; i++) {
        Mat frame;
        input.read(frame);
        Insert(frame);
    }
}