#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
    ofGLWindowSettings settings_;
    settings_.setGLVersion(3, 2);
    settings_.width = 1280;
    settings_.height = 720;
    ofCreateWindow(settings_);
    
	ofRunApp(new ofApp());
}
