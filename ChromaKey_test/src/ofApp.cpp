#include "ofApp.h"

static const std::string kRGBChromaKeyShader("RGB chroma key");
static const std::string kHSVChromaKeyShader("HSV chroma key");


//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
//    ofSetFrameRate(120);
//    ofSetVerticalSync(true);
    
    for (const auto& device_ : mGrabber.listDevices())
    {
        if (ofIsStringInString(device_.deviceName, "THETA"))
        {
            mGrabber.setDeviceID(device_.id);
            break;
        }
    }
    
    mGrabber.setup(1920, 1080);
    
    ofFbo::Settings settings_;
    settings_.width = mGrabber.getWidth();
    settings_.height = mGrabber.getHeight();
    settings_.internalformat = GL_RGB;
    settings_.useDepth = false;
    settings_.useStencil = false;
    settings_.numSamples = 2;
    
    for (auto i = 0; i < numFbos; ++i)
    {
        ofFbo fbo_;
        fbo_.allocate(settings_);
        mCapturedImages.emplace_back(fbo_);
    }
    
    mLastCaptureTimeMillis = 0;
    mCaptureIndex = 0;
    
    mChromakeyTargetColorRed.set("chromakey target: red", 0.0, 0.0, 1.0);
    mChromakeyTargetColorGreen.set("chromakey target: green", 1.0, 0.0, 1.0);
    mChromakeyTargetColorBlue.set("chromakey target: blue", 0.0, 0.0, 1.0);
    mThreshold.set("threshold", 0.0, 0.0, 1.0);
    
    mGui = new ofxDatGui();
    mGui->setAutoDraw(true);
    mGui->addToggle(kRGBChromaKeyShader, true);
    mGui->addToggle(kHSVChromaKeyShader, false);
    mGui->addSlider(mThreshold);
    mGui->addSlider(mChromakeyTargetColorRed);
    mGui->addSlider(mChromakeyTargetColorGreen);
    mGui->addSlider(mChromakeyTargetColorBlue);
    mGui->onButtonEvent(this, &ofApp::onButtonEvent);
    mGui->onSliderEvent(this, &ofApp::onSliderEvent);
    mGui->setPosition(ofGetWidth() - mGui->getWidth(), 0);
    
    mShader = mRGBChromaKeyShader;
    mChromakeyTargetColor.set(0.0, 0.0, 0.0);
}

//--------------------------------------------------------------
void ofApp::update()
{
    mGrabber.update();
    
    if (100 < ofGetElapsedTimeMillis() - mLastCaptureTimeMillis)
    {
        mCapturedImages.at(mCaptureIndex).begin();
        {
            ofClear(0);
            
            mShader.begin(mChromakeyTargetColor, mThreshold);
            {
                mGrabber.draw(0, 0);
            }
            mShader.end();
        }
        mCapturedImages.at(mCaptureIndex++).end();
        
        mCaptureIndex %= numFbos;
        mLastCaptureTimeMillis = ofGetElapsedTimeMillis();
    }
    
    ofSetWindowTitle(std::to_string(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);
    
    mShader.begin(mChromakeyTargetColor, mThreshold);
    {
        mGrabber.draw(0, 0, 1920 * 0.5, 1080 * 0.5);
    }
    mShader.end();
    
    for (auto i = 0; i < mCapturedImages.size(); ++i)
    {
        mCapturedImages.at(i).draw(1920 * 0.25 * (i % 4), (1080 * 0.5) + (1080 * 0.25) * std::floor(((float)i / 4.0)), 1920 * 0.25, 1080 * 0.25);
    }
    
    ofPushStyle();
    {
        ofSetColor(mChromakeyTargetColor);
        ofDrawRectangle(ofGetWidth() * 0.5, 0, ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    }
    ofPopStyle();
    
    ofPushStyle();
    {
        ofDrawBitmapStringHighlight("click on the video stream with pressing command key to pick a key color", ofGetWidth() * 0.5 + 4, 12, ofColor::white, ofColor::black);
        ofDrawBitmapStringHighlight("chroma key type: " + mShader.getType(), ofGetWidth() * 0.5 + 4, 32, ofColor::white, ofColor::black);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if (ofGetKeyPressed(OF_KEY_COMMAND))
    {
        if (ofGetWidth() * 0.5 < x || ofGetHeight() * 0.5 < y)
        {
            return;
        }
        
        ofColor color_ = mGrabber.getPixels().getColor(x * 2.0, y * 2.0);
        mChromakeyTargetColor.set(color_.r / 255.f, color_.g / 255.f, color_.b / 255.f);
        ofLog() << mChromakeyTargetColor;
        
        mChromakeyTargetColorRed = mChromakeyTargetColor.r;
        mChromakeyTargetColorGreen = mChromakeyTargetColor.g;
        mChromakeyTargetColorBlue = mChromakeyTargetColor.b;
    }
}

//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    mChromakeyTargetColor.set(mChromakeyTargetColorRed, mChromakeyTargetColorGreen, mChromakeyTargetColorBlue);
}

//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (kRGBChromaKeyShader == e.target->getName())
    {
        mGui->getToggle(kHSVChromaKeyShader)->setEnabled(false);
        mShader = mRGBChromaKeyShader;
    }
    else if (kHSVChromaKeyShader == e.target->getName())
    {
        mGui->getToggle(kRGBChromaKeyShader)->setEnabled(false);
        mShader = mHSVChromaKeyShader;
    }
}