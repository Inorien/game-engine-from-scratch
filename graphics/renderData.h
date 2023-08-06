#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

//anything we want to run through the graphics thingy
struct RenderData {
//public:
//
//	RenderData() = delete;
//	~RenderData() = default;
//	RenderData(const RenderData&) = delete;
//	RenderData& operator=(const RenderData&) = delete;
//	RenderData(RenderData&&) = delete;
//	RenderData& operator=(RenderData&&) = delete;
//
//	RenderData()
//
//private:
	//these both need to be sent to gl every frame
	glm::mat4 matrix{};
	std::vector<float> vertices; //dim3 - TODO tidy this up!!!
	std::vector<float> uvCoords; //dim2
	std::vector<unsigned> indices; //TRIANGLE INDICES from vertices
	unsigned count{0};
	GLuint texture;
};