#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
// layout (location = 3) in vec3 aNormal;

out vec4 VertexColor;
out vec2 TexCoord;
out vec3 Normal;

uniform mat4 modelRotation = mat4(1.0);
uniform mat4 modelPosition = mat4(1.0);
uniform mat4 model = mat4(1.0);

uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

void main() {
	//			  projection   view   {				model				    }
	gl_Position = projection * view * (modelRotation * modelPosition * model) * vec4(aPos, 1.0);
	VertexColor = vec4(aColor, 1.0);
	TexCoord = aTexCoord;
	Normal = vec3(1.0, 1.0, 1.0);
}
