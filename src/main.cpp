

#include "Application.h"
#include "Scene/Tests/LightingScene.h"
#include <algorithm>
#include <ranges>

/*
        Things to do:
        - [] create material class which stores a shader and its uniforms. This
   way I won't have to pass in raw shaders
        - [] create test class hooked up to ImGui debug menu to view different
   test screens
        - [] create an import for wavefront files, and render one
        - [] cleanup the code significantly
*/

static const ApplicationSpec APP_SPEC = { .width = 960,
                                          .height = 540,
                                          .name = "OpenGL Sandbox" };

void runApplication() {
    Application app(APP_SPEC);
    auto lightingScene = std::make_shared<LightingScene>(APP_SPEC);
    app.setScene(lightingScene);

    app.run();
}

int main(void) {
    // Core initializations
    Logger::init();
    // App initialization
    try {
        runApplication();
        LOG_CORE_INFO("Application Termination Success");
    } catch (std::runtime_error& e) {
        LOG_CORE_ERR("Runtime Error {}", e.what());
        return EXIT_FAILURE;
    } catch (std::exception& e) {
        LOG_CORE_ERR("Unknown error {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}