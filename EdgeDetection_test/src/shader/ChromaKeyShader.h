#pragma once

#include <iostream>
#include <GL/glew.h>
#include "ofShader.h"

class ChromaKeyShader
{
public:
    ChromaKeyShader();
    ~ChromaKeyShader() = default;
    
    void begin(const ofFloatColor& keyColor, const float threshold);
    void end();
    
private:
    ofShader mShader;
};