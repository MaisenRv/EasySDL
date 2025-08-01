#version 300 es
precision highp float;
layout(location = 0) in vec2 aPos;
uniform float u_ShiftX;
out vec2 vPos;
void main() {
    vPos = vec2(aPos.x - u_ShiftX, aPos.y);
}
