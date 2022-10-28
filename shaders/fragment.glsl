#version 330 core

out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoord;

uniform sampler2D inpTexture;
uniform vec3 rgbOffset = vec3(0.0, 0.0, 0.0);

void main() {
	FragColor = texture(inpTexture, TexCoord) * (VertexColor + vec4(rgbOffset, 1.0));
} 
