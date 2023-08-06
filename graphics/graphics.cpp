#include "graphics.h"
#include "shader.h"
#include "texture.h"
#include <exception>
#include "../control/callbackControl.h"

Graphics::Graphics(float& dt) noexcept :
	camera(std::make_unique<Camera>(window, dt))
{}

Graphics::~Graphics() {
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(programID);

	glfwTerminate();
}

void Graphics::initialise() {
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

	window = glfwCreateWindow(800, 800, "openglstudy", nullptr, nullptr);

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

	matrixID = glGetUniformLocation(programID, "MVP");

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertexBufferData.size() * sizeof(GLfloat),
		vertexBufferData.data(),
		GL_STATIC_DRAW);

	glGenBuffers(1, &colourBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,
		uvData.size() * sizeof(GLfloat),
		uvData.data(),
		GL_STATIC_DRAW);

	texture = loadBMP("assets/bitmaps/triangle.bmp");
	textureID = glGetUniformLocation(programID, "texSampler");

	camera->update();
}


void Graphics::render() const noexcept {

	camera->update();

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programID);

	const auto mvp{ camera->getProjection() * camera->getView() * glm::mat4(1.0) };
	//const auto mvp{ glm::identity<glm::mat4>() };
	
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colourBufferID);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glfwSwapBuffers(window);
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Graphics::registerCallbackControl(CallbackControl* const control) const {
	glfwSetWindowUserPointer(window, control);

	auto func = [](GLFWwindow* _window, int key, int, int action, int) {
		if (action == GLFW_PRESS)
			static_cast<CallbackControl*>(glfwGetWindowUserPointer(_window))->enableCallback(key);
		if (action == GLFW_RELEASE)
			static_cast<CallbackControl*>(glfwGetWindowUserPointer(_window))->disableCallback(key);
	};
	glfwSetKeyCallback(window, func);
}

void Graphics::registerCameraCallbacks(CallbackControl* control) {
	//disgusting
	//there must be a better way

	static auto fwd = [this]() {
		return camera->moveForward();
	};
	control->registerKeyCallback(GLFW_KEY_W, fwd);

	static auto bck = [this]() {
		return camera->moveBackward();
	};
	control->registerKeyCallback(GLFW_KEY_S, bck);

	static auto lft = [this]() {
		return camera->moveLeft();
	};
	control->registerKeyCallback(GLFW_KEY_A, lft);

	static auto rgt = [this]() {
		return camera->moveRight();
	};
	control->registerKeyCallback(GLFW_KEY_D, rgt);
}
