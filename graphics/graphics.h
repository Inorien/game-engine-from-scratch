#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"

#include <vector>

class CallbackControl;

//own opengl
class Graphics {
public:

	Graphics(float& dt);
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
	int checkInput(const unsigned key) const noexcept {
		return glfwGetKey(window, key) == GLFW_PRESS;
		
	}

	bool shouldClose() const noexcept {
		return glfwWindowShouldClose(window);
	}

	void registerCallbackControl(CallbackControl* control) const;

	//bad function, shouldnt be here but its convenient
	//should be tidier once configs are added
	void registerCameraCallbacks(CallbackControl* control);

private:
	GLFWwindow* window {nullptr};
	GLuint vertexArrayID {0};
	GLuint vertexBufferID {0};
	//GLuint colourBufferID;
	GLuint matrixID;

	GLuint programID {0};

	std::unique_ptr<Camera> camera;

	std::vector<GLfloat> vertexBufferData {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};
};