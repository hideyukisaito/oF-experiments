#include "EdgeDetectionShader.h"

static const std::string VERTEX_SHADER_SRC = R"(
#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 texcoord;
out vec2 texCoordVarying;

void main()
{
    texCoordVarying = texcoord.xy;
    gl_Position = modelViewProjectionMatrix * position;
}
)";

static const std::string FRAGMENT_SHADER_SRC = R"(
#version 150

uniform sampler2DRect tex0;
uniform vec3 keyColor = vec3(0.157, 0.576, 0.129);
uniform float threshold;
uniform int cellSize = 3;

in vec2 texCoordVarying;
out vec4 fragColor;

float rand(float n)
{
    return fract(sin(n) * 43758.5453123);
}

void main()
{
    vec4 texel0 = texture(tex0, texCoordVarying);
    
    vec4 color;
    
    for (int i = 0; i < 9; ++i)
    {
        color += texture(tex0, vec2(texCoordVarying.x - 1.f + (i % 3), texCoordVarying.y - 1.f + (i / 3)));
    }
    
    color /= 9.f;
    
    if (0.f == color.a || color.a == 1.f)
    {
        discard;
    }
    else
    {
        fragColor = mix(vec4(1.f, 0.f, 0.f, 1.f), texel0, 0.5);
    }
}
)";

EdgeDetectionShader::EdgeDetectionShader()
{
    mShader.setupShaderFromSource(GL_VERTEX_SHADER, VERTEX_SHADER_SRC);
    mShader.setupShaderFromSource(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SRC);
    mShader.bindDefaults();
    mShader.linkProgram();
}

void EdgeDetectionShader::begin()
{
    mShader.begin();
}

void EdgeDetectionShader::end()
{
    mShader.end();
}