#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 VertexColor;
out vec2 TexCoord;

uniform mat4 modelRotation = mat4(1.0);
uniform mat4 modelPosition = mat4(1.0);
uniform mat4 model = mat4(1.0);

uniform mat4 camPos = mat4(1.0);
uniform mat4 camRot = mat4(1.0);
uniform mat4 camProjection = mat4(1.0);

void main() {
	//			  projection 	  {	view		  }   {				model				    }
	gl_Position = camProjection * (camRot * camPos) * (modelRotation * modelPosition * model) * vec4(aPos, 1.0);
	VertexColor = vec4(aColor, 1.0);
	TexCoord = aTexCoord;
} 
