#pragma once

#include <iostream>
#include <GL/glew.h>
#include "ofShader.h"

class EdgeDetectionShader
{
public:
    EdgeDetectionShader();
    ~EdgeDetectionShader() = default;
    
    void begin();
    void end();
    
private:
    ofShader mShader;
};