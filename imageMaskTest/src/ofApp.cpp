#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // load shader
    shader.load("mask");
    
    ofSetCircleResolution(128);
    ofEnableSmoothing();
    
    // prepare original image
    image.loadImage("IMG_7223.JPG");
    image.resize(100, 100);
    image.setAnchorPercent(0.5, 0.5);
    
    // fbo for canvas
    canvas.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    canvas.begin();
    {
        ofClear(0, 0);
    }
    canvas.end();
    
    // fbo for masking
    mask.allocate(image.width, image.height, GL_RGBA, 8);
    mask.begin();
    {
        ofClear(0, 0);
        ofFill();
        ofSetColor(255, 255);
        ofCircle(mask.getWidth() * 0.5, mask.getHeight() * 0.5, 40);
    }
    mask.end();
    
    // init positions
    for (int i = 0; i < 100; ++i) {
        positions.push_back(ofVec3f(ofRandom(500), ofRandom(500), ofRandom(-100, 100)));
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    canvas.begin();
    {
        ofClear(0, 0);
        
        cam.begin();
        {
            ofEnableDepthTest();
            
            ofPushMatrix();
            {
                ofTranslate(ofVec3f(500 * -0.5, 500 * -0.5, 0));
                
                for (unsigned int i = 0; i < positions.size(); ++i) {
                    shader.begin();
                    {
                        shader.setUniformTexture("imageMask", mask.getTextureReference(), 1);
                        image.draw(positions[i].x, positions[i].y, positions[i].z);
                    }
                    shader.end();
                }
            }
            ofPopMatrix();
        }
        cam.end();
    }
    canvas.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0, 0, 0);
    canvas.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if ('r' == key) {
        shader.unload();
        shader.load("mask");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}