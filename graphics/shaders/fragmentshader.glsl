#version 330 core

in vec2 uvCoord;

out vec3 colour;

uniform sampler2D texSampler;

void main() {
	colour = texture(texSampler, uvCoord).rgb;
}