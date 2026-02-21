#version 300 es
precision mediump float;
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

uniform vec2 u_WindowSize;
uniform vec2 u_Offset;       // desplazamiento en píxeles
uniform vec2 u_Scale;

out vec2 TexCoord;

void main() {
    vec2 pos = position * u_Scale + u_Offset;
    vec2 ndc = (pos / u_WindowSize) * 2.0 - 1.0;
    // ndc.y *= -1.0;
    gl_Position = vec4(ndc, 0.0, 1.0);
    TexCoord = texCoord;
}
