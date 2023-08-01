#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <gl/glew.h>
#include <glfw/glfw3.h>

class Camera {
public:

	Camera() = delete;
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(Camera&&) = delete;

	Camera(GLFWwindow& window);


	//call every frame (with input?)
	void update(const double dt) noexcept;

	const auto& getProjection() const { return projection; }

	const auto& getView() const { return view; }
	
private:
	glm::vec3 position{0, 0, 0};
	glm::vec3 forward{0, 1, 0};
	glm::vec3 right{1, 0, 0};
	float speed { 5.0f };
	float mouseSens { 0.01f };
	float fov { 45.0f };
	float horizontalAngle { glm::pi<float>() };
	float verticalAngle { 0.0f };

	GLFWwindow& window; //no raw pointers allowed
	int screenWidth{800};
	int screenHeight{600};

	glm::mat4 projection;
	glm::mat4 view;
};