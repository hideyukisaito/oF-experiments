#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
    
    for (const auto& device_ : mGrabber.listDevices())
    {
        if (ofIsStringInString(device_.deviceName, "THETA"))
        {
            mGrabber.setDeviceID(device_.id);
            break;
        }
    }
    
    mGrabber.setup(1280, 720);
}

//--------------------------------------------------------------
void ofApp::update()
{
    mGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    mGrabber.draw(0, 0);
}
