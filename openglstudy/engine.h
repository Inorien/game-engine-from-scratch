#pragma once
//todo move these deeper in
#include "../graphics/graphics.h" //todo and make this a library
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine {
public:

	//get us to the "menu screen"
	void start();

	//move main thread into this class? just continue from start()?
	void run();
	  

	void shutdown() noexcept;

private:
	bool shouldExit{false};

	Graphics graphics;

};
	