

#include "Application.h"

/*
	Things to do:
	- [x] create camera class using lookat
	- [-] add key events to move around and scroll screen
		- [x] make event system and dispatcher
		- make it better organized
	- [x] abstract main into application class
	- [] create material class which stores a shader and its uniforms. This way I won't have to pass in raw shaders
	- [] create test class hooked up to ImGui debug menu to view different test screens
	- [x] create better struct for index buffer data
	- [] create an import for wavefront files, and render one
	- [x] learn 3D coordinates and create a shader for it
	- [] implement skybox
*/

static const int WINDOW_HEIGHT = 540;
static const int WINDOW_WIDTH = 960;
static const std::string APP_NAME = "OpenGL Test";

int main(void)
{
	// Core initializations
	Logger::init();
	// App initialization
	try {
		Application
			::getInstance(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME)
			.run();
		LOG_CORE_INFO("Application Termination Success");
	}
	catch (std::runtime_error& e) {
		LOG_CORE_ERR("Runtime Error {}", e.what());
		return EXIT_FAILURE;
	}
	catch (std::exception& e) {
		LOG_CORE_ERR("Unknown error {}", e.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}