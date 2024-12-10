#pragma once

#include <string>

#include "Events/Event.h"
#include "Renderer/Renderer.h"
#include "Scene/CameraController.h"
#include "core/MainWindow.h"

struct ApplicationSpec {
    int width, height;
    std::string name;
};

class Application {
   public:
    Application(const ApplicationSpec& spec);
    void run();

   private:
    const int m_width, m_height;
    const std::string m_appName;
    MainWindow m_window;
    CameraController m_cameraController;
    bool m_isMenuOpen = false;

   private:
    void onEvent(Event& e);

    void keyPressCallback(KeyPressEvent& e);

    void lightingTest();

    // Legacy Test
    void fboTest();
};
