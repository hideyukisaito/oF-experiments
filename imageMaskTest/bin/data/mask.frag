#version 120

uniform sampler2DRect tex0;
uniform sampler2DRect imageMask;

varying vec2 texCoordVarying;

void main()
{
    vec4 texel0 = texture2DRect(tex0, texCoordVarying);
    vec4 texel1 = texture2DRect(imageMask, texCoordVarying);
    
    if (texel1.a < 0.6) {
        discard;
    }
    
    gl_FragColor = vec4(texel0.rgb, texel0.a * texel1.a);
}