#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
    ofGLWindowSettings settings_;
    settings_.setGLVersion(3, 2);
    settings_.width = 1920;
    settings_.height = 1080;
    ofCreateWindow(settings_);
    
	ofRunApp(new ofApp());
}
