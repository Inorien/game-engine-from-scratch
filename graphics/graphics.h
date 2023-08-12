#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "shader.h"

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


	//TEMPORARY HACK (i promise) until i add proper registering of renderdata
	auto getPlayerDataID() const { return playerDataID; }

private:
	GLFWwindow* window {nullptr};
	GLuint vertexArrayID {0};
	GLuint vertexBufferID {0};
	GLuint colourBufferID{0};
	GLuint texture;
	GLuint textureID;

	//should this class still be owning camera?
	std::shared_ptr<Camera> camera{nullptr};
	std::unique_ptr<Shader> shader{nullptr};

	//TODO: i want "non-temporary" stuff to just live on the card
	Renderables renderables;

	//dev testing
	unsigned testDataID;
	unsigned playerDataID;

};