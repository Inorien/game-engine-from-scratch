#version 330 core

in vec2 uv;

out vec3 colour;

uniform sampler2D textureSampler;

void main() {
	colour = texture(textureSampler, uv).rgb;
}