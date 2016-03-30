#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "AbstractChromaKeyShader.h"
#include "RGBChromaKeyShader.h"
#include "HSVChromaKeyShader.h"

class ofApp : public ofBaseApp
{
public:
    ofVideoGrabber mGrabber;
    
    std::vector<ofFbo> mCapturedImages;
    
    std::uint64_t mLastCaptureTimeMillis;
    std::uint32_t mCaptureIndex;
    
    AbstractChromaKeyShader mShader;
    RGBChromaKeyShader mRGBChromaKeyShader;
    HSVChromaKeyShader mHSVChromaKeyShader;
    
    ofParameter<float> mThreshold;
    ofParameter<float> mChromakeyTargetColorRed;
    ofParameter<float> mChromakeyTargetColorGreen;
    ofParameter<float> mChromakeyTargetColorBlue;
    
    ofxDatGui * mGui;
    ofFloatColor mChromakeyTargetColor;
    
    constexpr static const int numFbos = 8;
    
    void setup();
    void update();
    void draw();
    
    void mousePressed(int x, int y, int button);
    
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onButtonEvent(ofxDatGuiButtonEvent e);
};
