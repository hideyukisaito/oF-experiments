#pragma once

#include <iostream>
#include <GL/glew.h>
#include "IShader.h"
#include "ofShader.h"

class AbstractChromaKeyShader : public IShader
{
public:
    AbstractChromaKeyShader();
    virtual ~AbstractChromaKeyShader() = default;
    
    virtual void begin(const ofFloatColor& keyColor, float threshold);
    void end();
    
    const std::string& getType() const;
    
protected:
    ofShader mShader;
    std::string mType;
    
    AbstractChromaKeyShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
};