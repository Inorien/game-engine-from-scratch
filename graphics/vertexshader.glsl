#version 330 core

layout(location = 0) in vec3 vertexPosition_modelSpace;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;

out vec2 uv;

void main() {

	gl_Position = MVP * vec4(vertexPosition_modelSpace,1);

	uv = vertexUV;
}