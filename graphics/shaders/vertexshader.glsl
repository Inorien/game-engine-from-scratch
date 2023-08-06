#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uv;

out vec2 uvCoord;

uniform mat4 matrix;

void main() {

	gl_Position = matrix * vec4(vertex, 1);
	uvCoord = uv;
}