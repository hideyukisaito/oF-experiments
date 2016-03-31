#include "ofApp.h"


static const std::string kThreshold = "threshold";
static const std::string kCellSize = "cellSize";


//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
        
    ofFbo::Settings settings_;
    settings_.width = 1280;
    settings_.height = 720;
    settings_.internalformat = GL_RGBA;
    settings_.useDepth = false;
    settings_.useStencil = false;
    mFbo.allocate(settings_);
    
    mThreshold.set(kThreshold, 0.f, 0.f, 1.f);
    mCellSize.set(kCellSize, 3, 3, 30);
    mKeyColor.set(0.f, 1.f, 0.f);
    
    mGui = new ofxDatGui();
    mGui->addSlider(mThreshold);
    mGui->addSlider(mCellSize);
    mGui->addColorPicker("key color");
    mGui->setAutoDraw(true);
    
    bApplyChromaKey = true;
    bApplyEdgeDetection = false;
    
    for (const auto& device_ : mGrabber.listDevices())
    {
        if (ofIsStringInString(device_.deviceName, "Logicool"))
        {
            mGrabber.setDeviceID(device_.id);
            break;
        }
    }
    
    mGrabber.setup(1280, 720);
    ofSetWindowShape(mGrabber.getWidth(), mGrabber.getHeight());
}

//--------------------------------------------------------------
void ofApp::update()
{
    mGrabber.update();
    
    mFbo.begin();
    {
        ofClear(0, 0);
        
        if (bApplyChromaKey) { mChromaKeyShader.begin(mKeyColor, mThreshold); }
        {
            mGrabber.draw(0, 0);
        }
        if (bApplyChromaKey) { mChromaKeyShader.end(); }
    }
    mFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    if (bApplyEdgeDetection) { mEdgeDetectionShader.begin(); }
    {
        mFbo.draw(0, 0);
    }
    if (bApplyEdgeDetection) { mEdgeDetectionShader.end(); }
    
    ofPushStyle();
    {
        ofSetColor(mKeyColor);
        ofFill();
        ofDrawRectangle(0.f, (float)ofGetHeight() - 100.f, 100.f, 100.f);
        
        ofSetColor(ofColor::white);
        ofNoFill();
        ofDrawRectangle(0.f, (float)ofGetHeight() - 100.f, 100.f, 100.f);
        
        if (ofGetKeyPressed(OF_KEY_COMMAND))
        {
            ofSetColor(mGrabber.getPixels().getColor(ofGetMouseX(), ofGetMouseY()));
            ofFill();
            ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), 100.f, 100.f);
        }
    }
    ofPopStyle();
    
    ofSetWindowTitle(std::to_string(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if ('c' == key)
    {
        bApplyChromaKey = !bApplyChromaKey;
    }
    else if ('e' == key)
    {
        bApplyEdgeDetection = !bApplyEdgeDetection;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if (ofGetKeyPressed(OF_KEY_COMMAND))
    {
        ofColor color_ = mGrabber.getPixels().getColor(x, y);
        mKeyColor.set(color_.r / 255.f, color_.g / 255.f, color_.b / 255.f);
    }
}