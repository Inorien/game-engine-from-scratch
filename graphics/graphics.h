#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"

#include <vector>

class CallbackControl;

//own opengl
class Graphics {
public:

	explicit Graphics(float& dt) noexcept;
	~Graphics();

	Graphics() = delete;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator=(Graphics&&) = delete;

	//todo give user config options one day
	//bool configure(GLFWwindow* const window);

	void initialise();

	//call this every frame - ONE DAY, TICK
	void render() const noexcept;

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
	GLuint colourBufferID{0};
	GLuint matrixID;
	GLuint texture;
	GLuint textureID;

	GLuint programID {0};

	std::unique_ptr<Camera> camera;

	std::vector<GLfloat> vertexBufferData {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f
	};

	std::vector<GLfloat> uvData {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f
	};

};