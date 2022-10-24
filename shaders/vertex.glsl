#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 VertexColor;
out vec2 TexCoord;

uniform mat4 transform = mat4(
		1.0, 0.0, 0.0, 0.0, 
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
		);

void main() {
	gl_Position = transform * vec4(aPos, 1.0);
	VertexColor = vec4(aColor, 1.0);
	TexCoord = aTexCoord;
} 
