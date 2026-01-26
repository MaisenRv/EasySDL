#version 300 es
precision mediump float;

layout(location = 0) in vec2 position;      // en píxeles

uniform vec2 u_WindowSize;                  // ancho, alto de la ventana
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

    // pasa de píxeles (0…w, 0…h) a NDC (-1…1, -1…1)
    vec2 ndc = ((rotated + u_Position) / u_WindowSize) * 2.0 - 1.0;
    // si tu sistema Y crece hacia abajo, invierte Y: ndc.y = 1.0 - ndc.y;
    gl_Position = vec4(ndc, 0.0, 1.0);
}