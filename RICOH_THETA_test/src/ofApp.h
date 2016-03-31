#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
    ofVideoGrabber mGrabber;
    
    void setup();
    void update();
    void draw();
};
