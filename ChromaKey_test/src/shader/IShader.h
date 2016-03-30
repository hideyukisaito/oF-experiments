#pragma once

#include "ofColor.h"

class IShader
{
public:
    virtual ~IShader() {};
    
    virtual void begin(const ofFloatColor& keyColor, float threshold) = 0;
    virtual void end() = 0;
};