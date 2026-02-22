#version 300 es
precision mediump float;

layout(location = 0) in vec2 position;

uniform vec2 u_WindowSize; 
uniform vec2 u_Position;
uniform float u_Rotation;
uniform vec2 u_Scale; 

void main() {
    vec2 scaled = position * u_Scale;

    float c = cos(u_Rotation);
    float s = sin(u_Rotation);

    vec2 rotated;
    rotated.x = scaled.x * c - scaled.y * s;
    rotated.y = scaled.x * s + scaled.y * c;

    vec2 ndc = ((rotated + u_Position) / u_WindowSize) * 2.0 - 1.0;
    gl_Position = vec4(ndc, 0.0, 1.0);
}