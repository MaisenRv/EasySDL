#version 300 es
precision mediump float;

layout(location = 0) in vec2 position;   // posición local en radio=1
uniform vec2 u_WindowSize;               // ancho, alto de la ventana (px)
uniform vec2 u_Position;                 // centro en píxeles
uniform float u_Scale;                   // radio en píxeles

void main() {
    vec2 worldPos = position * u_Scale + u_Position;         // en píxeles
    vec2 ndc = (worldPos / u_WindowSize) * 2.0 - 1.0;
    ndc.y = -ndc.y; // si tu sistema Y crece hacia abajo (pantalla)
    gl_Position = vec4(ndc, 0.0, 1.0);
}