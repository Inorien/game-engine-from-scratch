#include "camera.h"

using namespace glm;

Camera::Camera(GLFWwindow& window) :
	window(window) {
	glfwGetWindowSize(&window, &screenWidth, &screenHeight);
}


void Camera::update(const double dt) noexcept {

	double xpos;
	double ypos;
	glfwGetCursorPos(&window, &xpos, &ypos);
	glfwSetCursorPos(&window, screenWidth / 2, screenHeight / 2);

	horizontalAngle += mouseSens * static_cast<float>(screenWidth / 2.0 - xpos);
	verticalAngle   += mouseSens * static_cast<float>(screenHeight/ 2.0 - ypos);

	forward = vec3{
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle) };

	right = vec3(
		sin(horizontalAngle - glm::pi<float>() / 2.0f),
		0,
		cos(horizontalAngle - glm::pi<float>() / 2.0f)
	);

	projection = perspective(
		radians(fov),
		(float)screenWidth / (float)screenHeight,
		0.1f,
		100.0f);

	view = lookAt(
		position,
		position + forward,
		vec3(0,0,1)
	);
}
