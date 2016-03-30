#include "RGBChromaKeyShader.h"

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
uniform vec3 keyColor = vec3(0.0, 1.0, 0.0);
uniform float threshold = 1.0;
uniform int mode = 0; // 0 = noise, 1 = discard

in vec2 texCoordVarying;
out vec4 fragColor;

float rand(float n)
{
    return fract(sin(n) * 43758.5453123);
}

void main()
{
    vec4 texel0 = texture(tex0, texCoordVarying);
    
    if (threshold > distance(texel0.rgb, keyColor))
    {
        if (0 == mode)
        {
            fragColor = vec4(rand(texel0.r), rand(texel0.r), rand(texel0.r), 1.0);
        }
        else if (1 == mode)
        {
            discard;
        }
    }
    else
    {
        fragColor = texel0;
    }
}
)";


RGBChromaKeyShader::RGBChromaKeyShader() : AbstractChromaKeyShader(VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC)
{
    mType = "rgb";
}