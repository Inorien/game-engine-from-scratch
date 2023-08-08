#include "graphics.h"
#include "texture.h"
#include <exception>
#include "../control/callbackControl.h"

Graphics::Graphics(float& dt) noexcept :
	camera(std::make_unique<Camera>(window, dt))
{}

Graphics::~Graphics() {
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vertexArrayID);

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

	shader = std::make_unique<Shader>(Shader::fromFile("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl"));

	//just some test data for now
	const auto testTexture{ loadBMP("assets/bitmaps/triangle.bmp") };
	testData.texture = testTexture;
	renderQueue.emplace_back(testData);


	camera->update();
}


void Graphics::render() const noexcept {

	//can probably avoid this with mouse off, recalcs matrices that wont change
	camera->update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//const auto mvp{ camera->getProjection() * camera->getView() * glm::mat4(1.0) };

	for (const auto& renderData : renderQueue) {
		shader->render(renderData);
	}

	//shader->render(testData);


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
