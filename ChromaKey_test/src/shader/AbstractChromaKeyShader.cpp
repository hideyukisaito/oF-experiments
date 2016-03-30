#include "AbstractChromaKeyShader.h"

AbstractChromaKeyShader::AbstractChromaKeyShader()
{
    
}

AbstractChromaKeyShader::AbstractChromaKeyShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
{
    mShader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderSrc);
    mShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    mShader.bindDefaults();
    mShader.linkProgram();
}

void AbstractChromaKeyShader::begin(const ofFloatColor &keyColor, float threshold)
{
    mShader.begin();
    mShader.setUniform3f("keyColor", ofVec3f(keyColor.r, keyColor.g, keyColor.b));
    mShader.setUniform1f("threshold", threshold);
}

void AbstractChromaKeyShader::end()
{
    mShader.end();
}

const std::string& AbstractChromaKeyShader::getType() const
{
    return mType;
}