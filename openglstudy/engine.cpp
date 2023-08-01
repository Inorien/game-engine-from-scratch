#include "engine.h"

void Engine::start() {
	//let graphics default initialise

}


void Engine::run() {
	while (!shouldExit) {
		if (graphics.checkInput(GLFW_KEY_ESCAPE)) {
			shouldExit = true;
		}
		graphics.render();
	}
}

void Engine::shutdown() noexcept {
	
}



