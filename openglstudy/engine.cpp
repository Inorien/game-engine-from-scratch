#include "engine.h"
#include <chrono>

using namespace std::literals;


void Engine::start() {
	
	//TODO load config
	graphics.registerCallbackControl(&control);
	graphics.registerCameraCallbacks(&control);
}

void Engine::run() {
	auto currentTime{ std::chrono::system_clock::now() };
	while (!shouldExit) {
		if (graphics.checkInput(GLFW_KEY_ESCAPE)
		||  graphics.shouldClose()) { //seems like a bad function to have here
			shouldExit = true;
		}
		static auto lastTime{ std::chrono::system_clock::now() };
		currentTime = std::chrono::system_clock::now();
		deltaTime = (currentTime - lastTime) / 1ms / 1000.0f; //get in seconds to 3sf.

		//process all currently enabled callbacks
		control.update();


		graphics.render();
		lastTime = currentTime;
	}
}

void Engine::shutdown() noexcept {
	
}
