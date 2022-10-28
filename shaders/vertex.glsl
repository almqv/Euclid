#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 VertexColor;
out vec2 TexCoord;

uniform mat4 baseModel = mat4(1.0);
uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

void main() {
	gl_Position = projection * view * model * baseModel * vec4(aPos, 1.0);
	VertexColor = vec4(aColor, 1.0);
	TexCoord = aTexCoord;
} 
