#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "../control/controllable.h"

class Camera : public KeyboardControllable {
public:

	Camera() = delete;
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;

	Camera(GLFWwindow*& window, float& dt);

	

	const auto& getProjection() const { return projection; }

	const auto& getView() const { return view; }

	void moveForward() noexcept {
		std::cout << "forward" << std::endl;
		position += delta * forward * speed;
	}

	void moveBackward() noexcept {
		std::cout << "backward" << std::endl;
		position -= delta * forward * speed;
		update();
	}

	void moveLeft() noexcept {
		std::cout << "left" << std::endl;
		position -= delta * right * speed;
		update();
	}

	void moveRight() noexcept {
		std::cout << "right" << std::endl;
		position += delta * right * speed;
		update();
	}

	void update() noexcept;

private:
	//arbitrary values, better than garbage
	glm::vec3 position{4, 3, 3};
	glm::vec3 forward{0, 0, 0};
	glm::vec3 right{0, 1, 0};
	float speed { 1.0f };
	float mouseSens { 0.01f };
	float fov { 45.0f };
	float horizontalAngle { glm::pi<float>() };
	float verticalAngle { 0.0f };

	GLFWwindow*& window;
	int screenWidth{800};
	int screenHeight{600};

	glm::mat4 projection{glm::identity<glm::mat4>()};
	glm::mat4 view{glm::identity<glm::mat4>()};

};