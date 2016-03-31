#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
    ofGLWindowSettings settings_;
    settings_.setGLVersion(3, 2);
    ofCreateWindow(settings_);
    
	ofRunApp(new ofApp());
}
