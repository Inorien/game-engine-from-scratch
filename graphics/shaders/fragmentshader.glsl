#version 330 core

in vec2 uv;

out vec3 colour;

uniform sampler2D texSampler;

void main() {
	colour = texture(texSampler, uv).rgb;
}