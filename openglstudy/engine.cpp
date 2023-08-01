#include "engine.h"
#include <chrono>

void Engine::start() {
	//let graphics default initialise

}



void Engine::run() {
	using namespace std::literals;
	auto currentTime{ std::chrono::system_clock::now() };
	while (!shouldExit) {
		static auto lastTime{std::chrono::system_clock::now()};
		currentTime = std::chrono::system_clock::now();
		auto dt{
			(currentTime - lastTime) / 1ms / 1000.0}; //get in seconds to 3sf.
		if (graphics.checkInput(GLFW_KEY_ESCAPE)
		||  graphics.shouldClose()) { //seems like a bad function to have here
			shouldExit = true;
		}
		graphics.render(dt);
		lastTime = currentTime;
	}
}

void Engine::shutdown() noexcept {
	
}
