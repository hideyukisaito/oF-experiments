#include "HSVChromaKeyShader.h"

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
uniform int mode = 0; // 0 = noise, 1 = discard

in vec2 texCoordVarying;
out vec4 fragColor;

float rand(float n)
{
    return fract(sin(n) * 43758.5453123);
}

vec3 rgb2hsv(vec3 rgb)
{
    float Cmax = max(rgb.r, max(rgb.g, rgb.b));
    float Cmin = min(rgb.r, min(rgb.g, rgb.b));
    float delta = Cmax - Cmin;
    
    vec3 hsv = vec3(0., 0., Cmax);
    
    if (Cmax > Cmin)
    {
        hsv.y = delta / Cmax;
        
        if (rgb.r == Cmax)
        {
            hsv.x = (rgb.g - rgb.b) / delta;
        }
        else
        {
            if (rgb.g == Cmax)
            {
                hsv.x = 2. + (rgb.b - rgb.r) / delta;
            }
            else
            {
                hsv.x = 4. + (rgb.r - rgb.g) / delta;
            }
        }
        
        hsv.x = fract(hsv.x / 6.);
    }
    return hsv;
}

float chromaKey(vec3 color)
{
    vec3 weights = vec3(4., 1., 2.);
    
    vec3 src = rgb2hsv(color);
    vec3 key = rgb2hsv(keyColor);
    
    return length(weights * (key - src));
}

vec3 changeSaturation(vec3 color, float saturation)
{
    float luma = dot(vec3(0.213, 0.715, 0.072) * color, vec3(1.));
    return mix(vec3(luma), color, saturation);
}

void main()
{
    vec4 texel0 = texture(tex0, texCoordVarying);
    
    float len = length(vec3(4.0, 1.0, 2.0) * (rgb2hsv(keyColor) - rgb2hsv(texel0.rgb)));
    
    if (threshold > len)
    {
        if (0 == mode)
        {
            fragColor = vec4(rand(len), rand(len), rand(len), 1.0);
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


HSVChromaKeyShader::HSVChromaKeyShader() : AbstractChromaKeyShader(VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC)
{
    mType = "hsv";
}