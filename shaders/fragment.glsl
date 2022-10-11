#version 330 core
out vec4 FragColor;
in vec4 vertexColor;

uniform float r;
uniform float g;
uniform float b;

void main() {
	FragColor = vertexColor + vec4(r, g, b, 1.0f);
} 
