#include "engine.h"

void Engine::start() {
	//let graphics default initialise

}



void Engine::run() {
	while (!shouldExit) {
		if (graphics.checkInput(GLFW_KEY_ESCAPE)
		||  graphics.shouldClose()) { //seems like a bad function to have here
			shouldExit = true;
		}
		graphics.render();
	}
}

void Engine::shutdown() noexcept {
	
}
