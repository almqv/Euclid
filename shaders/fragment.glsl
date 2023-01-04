#version 330 core

out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoord;

uniform sampler2D inpTexture;
uniform vec3 lightColor;

void main() {
	FragColor = texture(inpTexture, TexCoord) * VertexColor * vec4(lightColor, 1.0);
} 
