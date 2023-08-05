#pragma once

//interface class for controllable things (camera, icons, whatever)

struct GLFWwindow;

struct KeyboardControllable {
	virtual ~KeyboardControllable() = default;
	virtual void control_callback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

	void setDelta(float dt) noexcept { delta = dt; }

protected:
	float delta{0.0f}; //REAL time since last call
};