#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//own opengl
class Graphics {
public:

	Graphics();
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator=(Graphics&&) = delete;

	//todo give user config options one day
	//bool configure(GLFWwindow* const window);

	//call this every frame
	void render() const noexcept;

	//call this every frame? seems really bad
	int checkInput(unsigned key) const noexcept {
		return glfwGetKey(window, key) == GLFW_PRESS;
		
	}

private:
	GLFWwindow* window {nullptr};
	GLuint vertexArrayID {0};
	GLuint vertexBufferID {0};
	//GLuint colourBufferID;

	GLuint programID {0};
};