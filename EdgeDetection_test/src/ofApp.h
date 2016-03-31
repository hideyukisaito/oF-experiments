#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ChromaKeyShader.h"
#include "EdgeDetectionShader.h"

class ofApp : public ofBaseApp
{
public:
    ofVideoGrabber mGrabber;
    ofShader mShader;
    ChromaKeyShader mChromaKeyShader;
    EdgeDetectionShader mEdgeDetectionShader;
    
    ofFbo mFbo;
    ofImage mImage;
    
    ofxDatGui * mGui;
    
    ofParameter<float> mThreshold;
    ofParameter<int> mCellSize;
    ofFloatColor mKeyColor;
    
    bool bApplyChromaKey;
    bool bApplyEdgeDetection;
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
};
