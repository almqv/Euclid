#version 330 core

out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoord;

uniform sampler2D inpTexture;

uniform float r;
uniform float g;
uniform float b;

void main() {
	FragColor = texture(inpTexture, TexCoord) * (VertexColor + vec4(r, g, b, 1.0f));
} 
