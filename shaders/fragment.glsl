#version 330 core

out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoord;

uniform sampler2D inpTexture;
uniform vec3 diffuseColor;
uniform float diffuseStrength;

void main() {
	FragColor = texture(inpTexture, TexCoord) * VertexColor * vec4(diffuseColor * diffuseStrength, 1.0);
} 
