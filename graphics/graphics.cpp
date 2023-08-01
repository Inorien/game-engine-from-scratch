#include "graphics.h"
#include "shader.h"
#include <exception>

Graphics::Graphics() {
	glewExperimental = true;
	if (!glfwInit()) {
		throw std::exception("Failed to initialise GLFW");
	}

	//loosely based on http://www.opengl-tutorial.org/ to start with
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "openglstudy", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		throw std::exception("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		throw std::exception("Failed to initialise GLEW");
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	programID = loadShaders("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl");

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertexBufferData.size() * sizeof(GLfloat),
		vertexBufferData.data(),
		GL_STATIC_DRAW);
}

Graphics::~Graphics() {
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(programID);

	glfwTerminate();
}


void Graphics::render() const noexcept {
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}
