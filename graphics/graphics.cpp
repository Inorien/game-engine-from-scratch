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

	shader = std::make_unique<Shader>(
		Shader::fromFile("shaders/vertexshader.glsl", "shaders/fragmentshader.glsl"));

	//just some test data for now

	RenderData testData{
	glm::identity<glm::mat4>(),
	{-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f},
	{0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f},
	{0, 1, 2},
	3,
	0
	};

	RenderData playerData{
		glm::identity<glm::mat4>(),
		{0.0f, 1.0f, -0.1f,
		.5f, 1.0f, -0.1f,
		0.0f, 0.0f, -0.1f,
		.5f, 0.0f, -0.1f},
		{0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f},
		{0, 1, 2,
		1, 2, 3},
		4,
		1 };

	//TODO not hardcode this and put it on the interface properly

	const auto testTexture{ loadBMP("assets/bitmaps/triangle.bmp") };
	testData.texture = testTexture;
	testDataID = renderables.addRenderable(testData);

	const auto heroTexture{ loadBMP("assets/bitmaps/hero.bmp") };
	playerData.texture = heroTexture;
	playerDataID = renderables.addRenderable(playerData);

	camera->update();
	shader->setCamera(camera);
}


void Graphics::render() const noexcept {

	//can probably avoid this with mouse off, recalcs matrices that wont change
	//camera->update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//const auto mvp{ camera->getProjection() * camera->getView() * glm::mat4(1.0) };

	const auto& renderData{ renderables.getAllRenderData() };
	for (const auto& data : renderData) {
		shader->render(*data);
	}


	glfwSwapBuffers(window);
	glfwPollEvents();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

//this should probably not be here, we only need the window pointer
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
