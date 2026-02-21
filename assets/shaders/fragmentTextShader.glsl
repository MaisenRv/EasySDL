#version 300 es
precision mediump float;


in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D text;
void main() {
    FragColor = texture(text, TexCoord);
}
