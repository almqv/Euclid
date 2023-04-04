#version 330 core

out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D inpTexture;
uniform vec3 lightColor;
uniform float ambientStrength;

void main() {
	FragColor = texture(inpTexture, TexCoord) * VertexColor * vec4(lightColor * ambientStrength, 1.0);
}
