#version 300 es
precision mediump float;

layout(location = 0) in vec2 position;      // en píxeles
uniform vec2 u_WindowSize;                  // ancho, alto de la ventana

void main() {
    // pasa de píxeles (0…w, 0…h) a NDC (-1…1, -1…1)
    vec2 ndc = (position / u_WindowSize) * 2.0 - 1.0;
    // si tu sistema Y crece hacia abajo, invierte Y: ndc.y = 1.0 - ndc.y;
    gl_Position = vec4(ndc, 0.0, 1.0);
}